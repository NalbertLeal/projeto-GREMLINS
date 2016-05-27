#ifndef _MEMPOOL_COMMON_HPP_
#define _MEMPOOL_COMMON_HPP_

/*
*	@brief		This is a operator overload of new and receive two parameter to now the bytes size to alocate and to know which GM manage this block.
*	@param    bytes   This parameter indicate the size of the block to be allocated
*	@param    p       this parameter indicate the GM that manage the block.
*	@return   Return a void pointer to a block of the block allocated by the GM.
*/
void *operator new (size_t bytes, StoragePool & p) {
	Tag* const tag = reinterpret_cast<Tag *> (p.Allocate(bytes + sizeof(Tag)) );
	tag -> pool = &p;
	// skip sizeof tag to get the raw data-block
	return (reinterpret_cast<void *> (tag + 1U));
}

/*
*	@brief    This is a operator overload of new and receive one parameter. This going to be used when the user don't specify the GM. So the new going to use the OS the allocate the block.
*	@param    bytes   This parameter indicate the size of the block to be allocated
*	@return   Return a pointer to the block. This block have a tag->pool = nullptr because the OS allocated this block.
*/
void *operator new(size_t bytes) {
	Tag* const tag = reinterpret_cast<Tag *> (std::malloc (bytes + sizeof(Tag)) );
	tag->pool = nullptr;
	// skip sizeof tag to get the raw data-block.
	return (reinterpret_cast<void *> (tag + 1U));
}


/*
*	@brief    This is a operator overload of delete. This operator overload receive the block and read the tag->pool to discover if it's a block allocated by the OS or in a GM to delete the block.
*	@param    arg     This parameter indicate the block to be delete.
*	@return   this operator overload doesn't return anything.
*/
void operator delete (void * arg) noexcept {
	// we need to subtract 1U (in fact, pointer arithmetics) because arg
	// points to the raw data (second block of information).
	// the pool id (tag) is located 'sizeof(tag)' bytes before.
	Tag * const tag = reinterpret_cast<Tag *> (arg) - 1U;
	if (nullptr != tag->pool) // Memory block belongs to a paricular GM.
		tag->pool->Release(tag);
	else
		std::free(tag); // Memory block belongs to the operational system.
}

#endif
