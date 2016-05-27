#ifndef _CLASSSTORAGEPOOL_HPP_
#define _CLASSSTORAGEPOOL_HPP_

#include <iostream>

/*
*	@brief		Class StoragePool is a abstract class. Using this class other class going to be created to use this methods and control the memory.
*	@param
*	@return
*/
class SPool: public StoragePool {
	public:

		//StoragePool public destructor
		~SomePool ();

		//StoragePool public methods
		void *Allocate (size_t);
		void Free (void *);

		//operator overload
		void *operator new (size_t, StoragePool);
		void operator delete(void * );

	private:
};

#include "classSPool.inl"

#endif
