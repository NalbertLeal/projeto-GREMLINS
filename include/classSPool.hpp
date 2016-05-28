#ifndef _CLASSSLPOOL_HPP_
#define _CLASSSLPOOL_HPP_

#include <iostream>

#include "classStoragePool.hpp"

/*
*	@brief		Class StoragePool is a abstract class. Using this class other class going to be created to use this methods and control the memory.
*/
class SLPool: public StoragePool {
	public:
		struct Header {
			unsigned int mui_Length;
			Header() : mui_Length(0u) {/* Empty */};
		};

		struct Block : public Header {
			enum { BlockSize = 16 }; // Each block has 16 bytes.
			union {
				Block *mp_Next;
				char mc_RawArea[BlockSize - sizeof(Header)];
			};
			Block() : Header(), mp_Next(nullptr) { /* Empty */ };
		};

		//SLPool public constructor
		explicit SLPool(size_t bytes = 1024);
		//StoragePool public destructor
		~SLPool();
		//StoragePool public methods
		void *Allocate (size_t);
		void Free (void *);

	private:
		unsigned int mui_NumberOfBlocks;
		Block *mp_Pool;				//!< Head of list.
		Block &mr_Sentinel;		//!< End of the list
};

#include "classSPool.inl"

#endif
