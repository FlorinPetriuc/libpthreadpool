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
#include <pthreadpool.h>

void *function_test_1(void *arg)
{
	int *ret;
	
	ret = malloc(sizeof(int));
	
	*ret = (int)random();
	
	printf("[INFO] function_test_1 is running on thread %u; argument is %p %d; will return %p %d\r\n", 
								(unsigned int)pthread_self(), arg, *(int *)arg, (void *)ret, *(int *)ret);
	
	sleep(1);
	
	free(arg);
	
	return (void *)ret;
}

void *function_test_2(void *arg)
{
	int *ret;
	
	ret = malloc(sizeof(int));
	
	*ret = (int)random();
	
	printf("[INFO] function_test_2 is running on thread %u; argument is %p %d; will return %p %d\r\n", (unsigned int)pthread_self(), arg, *(int *)arg, (void *)ret, *(int *)ret);
	
	sleep(1);
	
	free(arg);
	
	return (void *)ret;
}

void complete_cb(const unsigned int seq, void *retV)
{
	printf("[INFO] Task with sequence number %u was completed; return value is %p\r\n", seq, retV);
	
	free(retV);
}

int main(void)
{
	int i;
	int *arg;
	
	struct pthreadpool_t *pool;
	
	pool = create_pthreadpool(1);
		
	for(i = 0; i < 16; ++i)
	{
		arg = malloc(sizeof(int));
		
		*arg = i;
	
		if(i & 1)
		{
			libpthreadpool_add_task(pool, function_test_1, complete_cb, arg, 16 - i, i);
		}
		else
		{
			libpthreadpool_add_task(pool, function_test_2, complete_cb, arg, 16 - i, i);
		}
		
		printf("[INFO] Added task %d\r\n", i);
	}
	
	while(1)
	{
		sleep(10);
	}

	return 0;
}