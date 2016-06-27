#
# Copyright (C) 2016 Florin Petriuc. All rights reserved.
# Initial release: Florin Petriuc <petriuc.florin@gmail.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License version
# 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#

CFLAGS = -c -Wall -Werror -fpic
LDFLAGS = -shared -o
FILES = ./core/build/obj/heap.o ./core/build/obj/mem.o ./core/build/obj/libpthreadpool.o

all:$(FILES)
	$(CC) $(LDFLAGS) ./core/build/lib/libpthreadpool.so $(FILES) -lpthread
	
./core/build/obj/heap.o:			./core/heap/heap.c
	$(CC) $(CFLAGS)					./core/heap/heap.c			-o 	./core/build/obj/heap.o
	
./core/build/obj/mem.o:				./core/misc/mem.c
	$(CC) $(CFLAGS)					./core/misc/mem.c			-o 	./core/build/obj/mem.o
	
./core/build/obj/libpthreadpool.o:	./core/libpthreadpool.c
	$(CC) $(CFLAGS)					./core/libpthreadpool.c		-o 	./core/build/obj/libpthreadpool.o
