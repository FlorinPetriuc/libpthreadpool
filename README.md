# libpthreadpool

Libpthreadpool is a C library for handling tasks on a defined number of threads

## Dependencies

The library depends on libpthread.

## Installation

1. Download the source:<br />
	```bash
	$ git clone https://github.com/FlorinPetriuc/libpthreadpool.git
	```
	
2. Compile:<br />
	```bash
	$ make
	```
	
3. Install:<br />
	```bash
	$ sudo make install
	```
	
## Usage

Include <b>pthreadpool.h</b> in your aplication and link to <b>-lpthreadpool</b>.</br>
Initialize the library and submit tasks. Follow the examples.

## Examples

1. <b>pool_example</b>: Submits 16 tasks to a thread pool of 8 workers

	```bash
	$ cd examples
	$ make pool_example
	$ ./pool_example
	```
