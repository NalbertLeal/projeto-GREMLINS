#ifndef _CLASSSPOOL_INL_
#define _CLASSSPOOL_INL_

#include <iostream>
#include <new>

/*
*	@brief
*	@param
*	@return
*/
SLPool::SLPool(size_t bytes) {
	this->mui_NumberOfBlocks = (bytes/Block::BlockSize) + 1;
	// creating the first block
	this->mp_Pool = new Block();
	this->mp_Pool->mui_Length = mui_NumberOfBlocks - 1;
	this->mp_Pool->mp_Next = nullptr;
	this->mr_Sentinel.mui_Length = 0;
	this->mr_Sentinel.mp_Next = mp_Pool;
}

/*
*	@brief
*	@param
*	@return
*/
SLPool::~SLPool() {

}

/*
*	@brief
*	@param
*	@return
*/
void * SLPool::Allocate (size_t bytes) {}

/*
*	@brief
*	@param
*	@return
*/
void SLPool::Free (void *p) {}

#endif
