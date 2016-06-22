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
 
#include "./heap/heap.h"
#include "./engine/engine.h"
 
void *f_test(void *arg)
{
	return NULL;
}
 
int main(void)
{
	struct heap_t *heap;
	
	struct libpthreadpool_task_t task;
	struct libpthreadpool_task_t *rem_task;
	
	unsigned int i;

	heap = libpthreadpool_create_heap();
	
	printf("[INFO] Created heap %p\r\n", heap);
	fflush(stdout);
	
	libpthreadpool_print_heap(heap);
	
	for(i = 0; i < 16; ++i)
	{
		printf("[INFO] Iteration %u\r\n", i);
		fflush(stdout);
	
		task.fct = f_test;
		task.fct_prm = (void *)i;
		task.seq = 16 - i;
		task.prio = i;
	
		libpthreadpool_add_to_heap(heap, task);
		
		libpthreadpool_print_heap(heap);
	}
	
	for(i = 0; i < 16; ++i)
	{
		printf("[INFO] Remove iteration %u\r\n", i);
		fflush(stdout);
		
		rem_task = libpthreadpool_remove_from_heap(heap);
		
		if(rem_task == NULL)
		{
			printf("[ERROR] rem_task is null");
			
			return 1;
		}
		
		printf("Element %u: %p %p %u %u\r\n", i, rem_task->fct, rem_task->fct_prm, rem_task->seq, rem_task->prio);
	}
	
	rem_task = libpthreadpool_remove_from_heap(heap);
	
	if(rem_task)
	{
		printf("[ERROR] rem_task should be null");
			
		return 1;
	}

	return 0;
}
 
