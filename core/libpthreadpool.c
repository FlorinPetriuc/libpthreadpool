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

#include "engine.h"
#include "./heap/heap.h"
#include "./misc/mem.h"

const unsigned int libpthreadpool_version = 100;

static void *pthread_pool_fct(void *arg)
{
	struct libpthreadpool_heap_t *queue;
	
	struct libpthreadpool_task_t *task;
	
	void *ret;
	
	queue = arg;
	
	while(1)
	{
		task = libpthreadpool_remove_from_heap(queue);
				
		ret = task->fct(task->fct_prm);
		
		if(task->cb)
		{
			task->cb(task->seq, ret);
		}
		
		free(task);
	}
	
	return NULL;
}

struct pthreadpool_t *create_pthreadpool(const unsigned int number_of_workers)
{
	unsigned int i;

	struct pthreadpool_t *ret;
	
	ret = xmalloc(sizeof(struct pthreadpool_t));
	
	ret->queue = libpthreadpool_create_heap();
	ret->workers = xmalloc(number_of_workers * sizeof(pthread_t));
	
	for(i = 0; i < number_of_workers; ++i)
	{
		if(pthread_create(&ret->workers[i], NULL, pthread_pool_fct, ret->queue))
		{
			perror("[FATAL] can not create pthread pool");
			
			exit(EXIT_FAILURE);
		}
	}
	
	return ret;
}

void libpthreadpool_add_task(struct pthreadpool_t *pool, libpthreadpool_function_t fct, libpthreadpool_cb_function_t cb, 
															void *fct_prm, const unsigned int seq, const unsigned int prio)
{
	struct libpthreadpool_task_t to_add;
	
	to_add.fct = fct;
	to_add.cb = cb;
	
	to_add.fct_prm = fct_prm;
	
	to_add.seq = seq;
	to_add.prio = prio;
	
	libpthreadpool_add_to_heap(pool->queue, to_add);
}