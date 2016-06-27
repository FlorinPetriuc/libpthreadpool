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

#include "mem.h"

void *xmalloc(const unsigned int size)
{
	void *ret;
	
	ret = malloc(size);
	
	if(ret == NULL)
	{
		perror("[FATAL] Out of memory");
		
		exit(EXIT_FAILURE);
	}
	
	return ret;
}