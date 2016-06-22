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

typedef void* (*libpthreadpool_function_t)(void *arg);

struct libpthreadpool_task_t
{
	libpthreadpool_function_t fct;
	
	void *fct_prm;
	
	unsigned int seq;
	
	unsigned int prio;
};

#endif