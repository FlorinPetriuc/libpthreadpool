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
 
#ifndef _HEAP_H_
#define _HEAP_H_

#include "pthread.h"

struct libpthreadpool_task_t;

struct libpthreadpool_heap_t
{
	struct libpthreadpool_task_t *arr;
	
	unsigned int len;
	unsigned int occ;
	
	pthread_mutex_t mtx;
	pthread_cond_t cond;
};

struct libpthreadpool_heap_t *libpthreadpool_create_heap();

void libpthreadpool_add_to_heap(struct libpthreadpool_heap_t *heap, struct libpthreadpool_task_t task);
struct libpthreadpool_task_t *libpthreadpool_remove_from_heap(struct libpthreadpool_heap_t *heap);

#endif