/*
 * Copyright (C) 2016 Florin Petriuc. All rights reserved.
 * Initial release: Florin Petriuc <petriuc.florin@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"
#include "../misc/mem.h"
#include "../engine.h"
 
struct libpthreadpool_heap_t *libpthreadpool_create_heap()
{
	struct libpthreadpool_heap_t *ret;
	
	ret = xmalloc(sizeof(struct libpthreadpool_heap_t));
		
	ret->arr = xmalloc(8 * sizeof(struct libpthreadpool_task_t));
	ret->len = 8;
	ret->occ = 0;
		
	if(pthread_mutex_init(&ret->mtx, NULL))
	{
		perror("[FATAL] unable to initialize heap mtx");
		
		exit(EXIT_FAILURE);
	}
	
	if(pthread_cond_init(&ret->cond, NULL))
	{
		perror("[FATAL] unable to initialize heap cond");
		
		exit(EXIT_FAILURE);
	}
	
	return ret;
}

static void swim_up(struct libpthreadpool_heap_t *heap)
{
	unsigned int i;
	unsigned int parent;
	
	struct libpthreadpool_task_t  temp;
	
	i = heap->occ - 1;
	
	while(i)
	{
		if(i & 1)
		{
			parent = i >> 1;
		}
		else
		{
			parent = (i >> 1) - 1;
		}
		
		if(heap->arr[i].prio <= heap->arr[parent].prio)
		{
			return;
		}
		
		temp = heap->arr[i];
		heap->arr[i] = heap->arr[parent];
		heap->arr[parent] = temp;
		
		i = parent;
	}
}

static void sink_down(struct libpthreadpool_heap_t *heap)
{
	unsigned int i;
	unsigned int l_child;
	unsigned int r_child;
	unsigned int swap_child;
	
	struct libpthreadpool_task_t  temp;
	
	i = 0;
	
	while(i < heap->occ)
	{
		l_child = (i << 1) + 1;
		r_child = (i << 1) + 2;
		
		if(l_child < heap->occ && r_child < heap->occ)
		{
			if(heap->arr[l_child].prio > heap->arr[r_child].prio)
			{
				swap_child = l_child;
			}
			else
			{
				swap_child = r_child;
			}
		}
		else if(l_child < heap->occ)
		{
			swap_child = l_child;
		}
		else if(r_child < heap->occ)
		{
			swap_child = r_child;
		}
		else
		{
			return;
		}
		
		if(heap->arr[i].prio >= heap->arr[swap_child].prio)
		{
			return;
		}
		
		temp = heap->arr[i];
		heap->arr[i] = heap->arr[swap_child];
		heap->arr[swap_child] = temp;
		
		i = swap_child;
	}
}

void libpthreadpool_add_to_heap(struct libpthreadpool_heap_t *heap, struct libpthreadpool_task_t task)
{
	pthread_mutex_lock(&heap->mtx);

	if(heap->len == heap->occ)
	{
		heap->len <<= 1;
		heap->arr = realloc(heap->arr, heap->len * sizeof(struct libpthreadpool_task_t));
	}
	
	heap->arr[heap->occ] = task;
	
	++heap->occ;
	
	swim_up(heap);
	
	pthread_mutex_unlock(&heap->mtx);
	pthread_cond_signal(&heap->cond);
}

struct libpthreadpool_task_t *libpthreadpool_remove_from_heap(struct libpthreadpool_heap_t *heap)
{
	struct libpthreadpool_task_t *ret;

	pthread_mutex_lock(&heap->mtx);
	
	while(heap->occ == 0)
	{
		pthread_cond_wait(&heap->cond, &heap->mtx);
	}
	
	ret = xmalloc(sizeof(struct libpthreadpool_task_t));
	memcpy(ret, &heap->arr[0], sizeof(struct libpthreadpool_task_t));
	
	--heap->occ;
	
	heap->arr[0] = heap->arr[heap->occ];
	
	if(heap->len > 8 && heap->occ <= (heap->len >> 2))
	{
		heap->len >>= 1;
		heap->arr = realloc(heap->arr, heap->len * sizeof(struct libpthreadpool_task_t));
	}
	
	sink_down(heap);
	
	pthread_mutex_unlock(&heap->mtx);
	
	return ret;
}