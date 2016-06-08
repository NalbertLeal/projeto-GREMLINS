#ifndef _CLASSSPOOL_INL_
#define _CLASSSPOOL_INL_

#include <iostream>
#include <cmath>

#include "classSPool.hpp"

/**
*	@brief		The constructor of the class SLPool configure the memory manager.
*	@return		The constructor doesn't have a return.
*/
SLPool::SLPool(size_t bytes) {
	// mui_NumberOfBlocks going to have 1 more block than the necessary
	this->mui_NumberOfBlocks = (bytes/Block::BlockSize) + 2;
	// allocate the blocks alling in the memory.
	this->mp_Pool = new Block[this->mui_NumberOfBlocks];
	// determinate the zise of the pool
	this->mp_Pool->mui_Length = mui_NumberOfBlocks - 1;
	// the block is complety free, so the mp_Next is nullptr
	this->mp_Pool->mp_Next = nullptr;
	// indicate the number of free frre area in blocks
	this->mr_Sentinel.mui_Length = this->mui_NumberOfBlocks;
	// point to the mp_pool
	this->mr_Sentinel.mp_Next = this->mp_Pool;
}

/**
*	@brief		the destructor of the SLPool desalocate the memory manager of the RAM.
*	@return		The destructor doen't have a return.
*/
SLPool::~SLPool() {
	delete[] this->mp_Pool;
}

/**
*	@brief		This function prepare a number of blocks required to be used. Use the first fit strategy.
*	@param		bytes	Receive the number os bytes necessary.
*	@return		This function doesn't have a return.
*/
void *SLPool::Allocate (size_t bytes) {
	unsigned long int Nblocks = std::ceil(bytes / Block::BlockSize) + 1;
	Block *work = this->mr_Sentinel.mp_Next;
	Block *work2 = &this->mr_Sentinel;

	for(/* Empty */;
		work != nullptr && work->mui_Length < Nblocks;
		work = work->mp_Next, work2 = work2->mp_Next
		) 
	{/* Empty */}

	// if the work is igual to nullptr launch bad_alloc() because don't have enough size.
	if(work == nullptr) {
		throw(std::bad_alloc());
	}

	// if the exact size necessary was found.
	if(work->mui_Length == Nblocks) {
		/*when they have the same sizej ust need to 
		point the work2->mp_Next to work->mp_Next.
		*/
		work2->mp_Next = work->mp_Next;
	}
	// if the size founded is bigger.
	else {
		/* the work2->mp_Next going to receive the work plus 
		the number of the blocks that the user need because 
		we want the exactly number of blocks to allocate.
		*/
		work2->mp_Next = work + Nblocks;
        /* work2->mp_Next->mui_Length going to be iqual to work->mui_Length - Nblocks
        because we need to put the new size of blocks of this free space.
		*/
        work2->mp_Next->mui_Length = work->mui_Length - Nblocks;
        /* the mp_next of work2 going to be the mp_next of work 
		because this is the other free space after the next.
		*/
        work2->mp_Next->mp_Next = work->mp_Next;
        // work->mui_Length have the size of allocated blocks.
        work->mui_Length = Nblocks;
	}

	return reinterpret_cast<Header*>(work)+1U;
}

/**
*	@brief		This function prepare a number of blocks required to be used. Use the best fit strategy.
*	@param		bytes	Receive the number os bytes necessary.
*	@return		This function doesn't have a return.
*/
void *SLPool::AllocateBestFit (size_t bytes) {
	unsigned long int Nblocks = std::ceil(bytes / Block::BlockSize) + 1;
	Block *work = this->mr_Sentinel.mp_Next;
	Block *work2 = &this->mr_Sentinel;
	unsigned long int auxLength;
	unsigned long int auxAreaPosition = 0;
	for(unsigned long int count = 1;
		work != nullptr;
		work = work->mp_Next, work2 = work2->mp_Next, count++
		) 
	{
		if(count == 1 || (auxAreaPosition == 0 && auxLength == 0)) {
			if(Nblocks < work->mui_Length) {
				auxLength = work->mui_Length;
				auxAreaPosition = count;
			}
		}
		else {
			if(Nblocks < work->mui_Length && work->mui_Length < auxLength) {
				auxLength = work->mui_Length;
				auxAreaPosition = count;
			}
		}
	}

	// if the work is igual to nullptr launch bad_alloc() because don't have enough size.
	if(work == nullptr) {
		throw(std::bad_alloc());
	}

	work = this->mr_Sentinel.mp_Next;
	work2 = &this->mr_Sentinel;

	for(unsigned long int count = 1; count < auxAreaPosition; count++) {
		work = work->mp_Next;
		work2 = work2->mp_Next;
	}

	if(work->mui_Length == Nblocks) {
		/*when they have the same sizej ust need to 
		point the work2->mp_Next to work->mp_Next.
		*/
		work2->mp_Next = work->mp_Next;
	}
	// if the size founded is bigger.
	else {
		/* the work2->mp_Next going to receive the work plus 
		the number of the blocks that the user need because 
		we want the exactly number of blocks to allocate.
		*/
		work2->mp_Next = work + Nblocks;
        /* work2->mp_Next->mui_Length going to be iqual to work->mui_Length - Nblocks
        because we need to put the new size of blocks of this free space.
		*/
        work2->mp_Next->mui_Length = work->mui_Length - Nblocks;
        /* the mp_next of work2 going to be the mp_next of work 
		because this is the other free space after the next.
		*/
        work2->mp_Next->mp_Next = work->mp_Next;
        // work->mui_Length have the size of allocated blocks.
        work->mui_Length = Nblocks;
	}

	return reinterpret_cast<Header*>(work)+1U;
}

/**
*	@brief		This function released the area in use.
*	@param		*p 		This parameter receive the pointer to the area to be released.
*	@return		This function doesn't have a return.
*/
void SLPool::Free (void *p) {
	Block *ptReserved = reinterpret_cast <Block*>(reinterpret_cast <Header*>(p)-1U); // reinterpret as Header* - 1U and after as Block
	Block *ptPostReserved = this->mr_Sentinel.mp_Next;
	Block *ptPrevReserved = &this->mr_Sentinel;

	for( /* Empty */; 
		ptPostReserved < ptReserved && ptPostReserved != nullptr;
		ptPrevReserved = ptPrevReserved->mp_Next, ptPostReserved = ptPostReserved->mp_Next
		) 
	{/* Empty */}

	if( (ptReserved == ptPrevReserved + ptPrevReserved->mui_Length) && 
		(ptPostReserved == (ptReserved + ptReserved->mui_Length)) ) 
	{
		ptPrevReserved->mp_Next = ptPostReserved->mp_Next;
		ptPrevReserved->mui_Length = ptPrevReserved->mui_Length + ptReserved->mui_Length + ptPostReserved->mui_Length;
	}
	else if( !(ptReserved == ptPrevReserved + ptPrevReserved->mui_Length) && 
		!(ptPostReserved == (ptReserved + ptReserved->mui_Length)) )
	{
		ptPrevReserved->mp_Next = ptReserved;
		ptReserved->mp_Next = ptPostReserved;
	}
	else if( !(ptReserved == ptPrevReserved + ptPrevReserved->mui_Length) && 
		(ptPostReserved == (ptReserved + ptReserved->mui_Length)) )
	{
		ptPrevReserved->mp_Next = ptReserved;
		ptReserved->mp_Next = ptPrevReserved->mp_Next;
		ptReserved->mui_Length = ptReserved->mui_Length + ptPrevReserved->mui_Length;
	}
	else if( (ptReserved == ptPrevReserved + ptPrevReserved->mui_Length) && 
		!(ptPostReserved == (ptReserved + ptReserved->mui_Length)) )
	{
		ptPrevReserved->mui_Length = ptPrevReserved->mui_Length + ptReserved->mui_Length;
	}

}

/**
*	@brief		This function show on the console a brief of the atual situation on the manager.
*	@return		This function doesn't have a return.
*/
void SLPool::showPool() {
	Block *work = &this->mr_Sentinel;
	unsigned long int count = 1;
	std::cout << "\n\n.......................................................................\n";
	std::cout << "########################  Print of the memory  #######################\n";
	std::cout << ">>> The memory pool have: " << work->mui_Length << " blocks; \n";
	std::cout << ">>> Free areas on the memory manager (areas not allocated): \n";
	for( unsigned long int counter = 0; work != nullptr; work = work->mp_Next) {
		if(counter != 0) {
			std::cout << ">>>>>>> The " << count << " free area have " << work->mui_Length <<
		" blocks and the memory address is " << work << "\n";
		count++;
		}
		else {
			counter++;
		}
	}
	std::cout << ".......................................................................\n\n\n";
}

#endif
