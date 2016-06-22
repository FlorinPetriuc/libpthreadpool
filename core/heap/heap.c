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
#include "../engine/engine.h"
 
struct heap_t *libpthreadpool_create_heap()
{
	struct heap_t *ret;
	
	ret = xmalloc(sizeof(struct heap_t));
		
	ret->arr = xmalloc(8 * sizeof(struct libpthreadpool_task_t));
	ret->len = 8;
	ret->occ = 0;
		
	if(pthread_mutex_init(&ret->mtx, NULL))
	{
		perror("[FATAL] unable to initialize heap mtx");
		
		exit(EXIT_FAILURE);
	}
	
	return ret;
}

static void swim_up(struct heap_t *heap)
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

static void sink_down(struct heap_t *heap)
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

void libpthreadpool_add_to_heap(struct heap_t *heap, struct libpthreadpool_task_t task)
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
}

struct libpthreadpool_task_t *libpthreadpool_remove_from_heap(struct heap_t *heap)
{
	struct libpthreadpool_task_t *ret;

	pthread_mutex_lock(&heap->mtx);
	
	if(heap->occ == 0)
	{
		pthread_mutex_unlock(&heap->mtx);
	
		return NULL;
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

void libpthreadpool_print_heap(struct heap_t *heap)
{
	unsigned int i;

	pthread_mutex_lock(&heap->mtx);

	printf("Heap %p\r\n", heap);
	printf("Heap len: %u\r\n", heap->len);
	printf("Heap occ: %u\r\n", heap->occ);
	
	for(i = 0; i < heap->occ; ++i)
	{
		printf("Element %u: %p %p %u %u\r\n", i, heap->arr[i].fct, heap->arr[i].fct_prm, heap->arr[i].seq, heap->arr[i].prio);
	}

	printf("\r\n");
	fflush(stdout);

	pthread_mutex_unlock(&heap->mtx);
}