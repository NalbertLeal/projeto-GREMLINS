#ifndef _CLASSSTORAGEPOOL_HPP_
#define _CLASSSTORAGEPOOL_HPP_

#include <iostream>

// char is 1byte so byte going to be declarade as char to have 1 bit of size.
//typedef char byte;

/*
*	@brief		Class StoragePool is a abstract class. Using this class other class going to be created to use this methods and control the memory.
*/
class StoragePool {
	public:

		//StoragePool public destructor
		virtual ~StoragePool() {};

		//StoragePool public methods
		virtual void *Allocate (size_t) = 0;
		virtual void Free (void *) = 0;
};

/*
*	@brief		Struct Tag define the tag that going to be used front of a memory block to define if it's a block of the OS or of a GM.
*/
struct Tag {
	StoragePool * pool;
};

#endif
