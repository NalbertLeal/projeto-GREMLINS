#ifndef _CLASSSTORAGEPOOL_HPP_
#define _CLASSSTORAGEPOOL_HPP_

#include <iostream>

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

#endif
