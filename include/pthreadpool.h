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
 
#ifndef _LIBPTHREAD_POOL_H_
#define _LIBPTHREAD_POOL_H_

#include <pthread.h>

/*
 * The version of the running library
 */
extern const unsigned int libpthreadpool_version;

struct libpthreadpool_heap_t;

/*
 * Task that will be handled by the threadpool
 *
 * Params:
 * - arg: provided by the user via libpthreadpool_add_task
 */

typedef void* (*libpthreadpool_function_t)(void *arg);

/*
 * Callback that is called when the task is finished
 *
 * Params:
 * - seq: task sequence number provided via libpthreadpool_add_task
 * - fct_ret: the returns value from the task
 */

typedef void (*libpthreadpool_cb_function_t)(const unsigned int seq, void *fct_ret);

/*
 * Pthread pool data structure
 */

struct pthreadpool_t
{
	struct libpthreadpool_heap_t *queue;
	
	pthread_t *workers;
};

/*
 * Initializes the internal data structures required by the library
 *
 * Params:
 * - number_of_workers: the number of threads that will process the tasks
 *
 * Returns:
 * - pointer to the thread pool data structure
 */

struct pthreadpool_t *create_pthreadpool(const unsigned int number_of_workers);

/*
 * Adds a task to be processed by the thread pool
 *
 * Params:
 * - pool: the pthreadpool_t returned by create_pthreadpool
 * - fct: the task to be processed by the thread pool
 * - cb: the callback that is called when the task is finished
 * - fct_prm: the parameters that is passed to the "fct" function call
 * - seq: the sequence number of the task. A the sequence number in the priority queue
 *		  should be unique at any given time. This way, you can distinguish between tasks
 *		  that call the same function. The functionality is not affected if they are not unique.
 * - prio: the task priority 
 */

void libpthreadpool_add_task(struct pthreadpool_t *pool, libpthreadpool_function_t fct, libpthreadpool_cb_function_t cb, 
															void *fct_prm, const unsigned int seq, const unsigned int prio);

#endif