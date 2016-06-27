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
 
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <pthread.h>

typedef void* (*libpthreadpool_function_t)(void *arg);
typedef void (*libpthreadpool_cb_function_t)(const unsigned int seq, void *fct_ret);

struct libpthreadpool_task_t
{
	libpthreadpool_function_t fct;
	libpthreadpool_cb_function_t cb;
	
	void *fct_prm;
	
	unsigned int seq;
	
	unsigned int prio;
};

struct pthreadpool_t
{
	struct libpthreadpool_heap_t *queue;
	
	pthread_t *workers;
};

struct pthreadpool_t *create_pthreadpool(const unsigned int number_of_workers);
void libpthreadpool_add_task(struct pthreadpool_t *pool, libpthreadpool_function_t fct, libpthreadpool_cb_function_t cb, 
															void *fct_prm, const unsigned int seq, const unsigned int prio);

#endif