CC=gcc

all:\
	./build/obj/engine.o		\
	./build/obj/heap.o			\
	./build/obj/mem.o			\
	./build/obj/libpthreadpool.o\
	
	$(CC) $(LDFLAGS)	\
	\
	./build/obj/engine.o			\
	./build/obj/heap.o				\
	./build/obj/mem.o				\
	./build/obj/libpthreadpool.o	\
	\
	-o\
	\
	./build/bin/libpthreadpool -lpthread
	
./build/obj/engine.o:			./engine/engine.c
	$(CC) $(CFLAGS) -c -Werror	./engine/engine.c	-o 	./build/obj/engine.o
	
./build/obj/heap.o:				./heap/heap.c
	$(CC) $(CFLAGS) -c -Werror	./heap/heap.c		-o 	./build/obj/heap.o
	
./build/obj/mem.o:				./misc/mem.c
	$(CC) $(CFLAGS) -c -Werror	./misc/mem.c		-o 	./build/obj/mem.o
	
./build/obj/libpthreadpool.o:	./libpthreadpool.c
	$(CC) $(CFLAGS) -c -Werror	./libpthreadpool.c	-o 	./build/obj/libpthreadpool.o
	
clean:
	rm ./build/obj/*
	rm ./build/bin/*