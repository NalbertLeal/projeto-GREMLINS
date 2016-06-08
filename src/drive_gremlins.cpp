#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <chrono>

#include "classSPool.hpp"
#include "classEvents.hpp"
#include "mempool_common.hpp"
#include "classStoragePool.hpp"

/**
*	@brief		This function is used to test the performace of memory manager or the OS.
*	@return		This function doesn't have a return.
*/
void StoragePoolTest(SLPool *thePool, std::time_t timeLimit) {
	std::priority_queue<Event> pq;
	Event event;
	for ( std::time_t t = 0; t < timeLimit; ++t ) {
		while ( ! pq.empty() ) { 
			event = pq.top();
			if ( t < event.getTime() ) break ;
			pq.pop ();
			delete ((int*)(event.getPtr()));
		}
		int randomic = ((rand() % 2100) + 1) + 100;

		int *aux;

		// this is the test of the memory manager
		if(thePool != nullptr) {
			aux = new (thePool)int[randomic];
		}
		// this is the test of the OS
		else {
			aux = new int[randomic];
		}

		if(thePool != nullptr){
            std::time_t lifeTime = t + ((rand() % 100) + 1) ;
            pq.push(Event(reinterpret_cast<void*> (aux), lifeTime));
        }
	}
	while(!pq.empty()) {
        event = pq.top();
        pq.pop();
        delete ((int*)(event.getPtr()));
    }
}

/**
*	@brief		This function test the memory manager implemented on the class SLPool.
*	@return		This function doesn't have a return.
*/
void simulation() {
	
	std::cout << "\n>>> Test with new and delete starting ... \n";

	std::cout << "\n\n>>> Creating a memory manager with 10MB ... \n";
	SLPool gm(1024*1024*10); // creating a memory manager with 10MB, much more than the necessary to the follow test.

	gm.showPool();	// print on the console the memory menager.

	std::cout << "\n>>> creating the space on the memory manager to allocate variables with primitive types and a std::string ... \n";
	
	std::cout << "\n>>> Allocanting space on the memory manager: \n";

	std::cout << ">>> int *k = new (gm)int \n";
	std::cout << ">>> int *o = new (gm)int \n";
	std::cout << ">>> char *p = new (gm)char \n";
	std::cout << ">>> char *u = new (gm)char \n";
	std::cout << ">>> std::string *s = new (gm)std::string \n";

	int *k = new (gm)int;	// using the new with operator overload.
	int *o = new (gm)int;	// using the new with operator overload.
	char *p = new (gm)char;
	char *u = new (gm)char;
	std::string *s = new (gm)std::string;

	gm.showPool();	// print on the console the memory menager.
	
	*p = 'n';
	*u = 'a';
	*k = 1;
	*o = 2;
	*s = "Nalbert";

	std::cout << "\n>>> Showing values of variables on the memory manager ... \n";
	std::cout << ">>> K = " << *k << std::endl;
	std::cout << ">>> o = " << *o << std::endl;
	std::cout << ">>> p = " << *p << std::endl;
	std::cout << ">>> u = " << *u << std::endl;
	std::cout << ">>> s = " << *s << std::endl;

	std::cout << "\n>>> Deleting allocated space to variable k to show what hapen with the memory manager ... \n";
	delete k;	// using the delete with operator overload.
	
	gm.showPool();	// print on the console the memory menager.

	std::cout << "\n>>> Deleting allocated space with values on the memory manager ... \n";
	delete o;	// using the delete with operator overload.
	delete p;	// using the delete with operator overload.
	delete u;	// using the delete with operator overload.
	delete s;	// using the delete with operator overload.

	gm.showPool();	// print on the console the memory menager.

	std::cout << ">>> Test with primitive types finished. \n\n\n";

	std::cout << ".......................................................................\n";

	std::cout << ">>> Testing the memory manager with array: \n\n\n";

	std::cout << ">>> Creating pointer to int: \n";
	std::cout << ">>> int *Alloc[7]; \n\n";

	int *Alloc[7];

	// Allocating 40 integers 4 times to test allocation
    for (int i = 0; i < 4; i++) {
        Alloc[i] = new(gm) int[10];
        std::cout << "[" << i << "] <<< Allocating 40 integers\n"
                  << std::string(8, ' ');
        gm.showPool();
    }

    for (int i = 0; i < 10; i++) {
        Alloc[0][i] = i;
        Alloc[1][i] = i;
        Alloc[2][i] = i;
    	std::cout << ">>> Alloc[0][" << i << "] = " << i << std::endl;
    	std::cout << ">>> Alloc[1][" << i << "] = " << i << std::endl;
    	std::cout << ">>> Alloc[2][" << i << "] = " << i << "\n\n";
    }

    gm.showPool();

    std::cout << ">>> Deleting Alloc[0]" << "\n";
    delete Alloc[0];
    std::cout << ">>> Deleting Alloc[1]" << "\n";
    delete Alloc[1];
    std::cout << ">>> Deleting Alloc[2]" << "\n";
    delete Alloc[2];

    gm.showPool();

	std::cout << "\n\n>>> Test OS vs SLPoll: \n\n\n";

	for(int count = 0; count < 2; count++){
		
		std::chrono::duration<double>  SLPoolTime;
		std::chrono::duration<double>  OSTime;

		if(count == 1) {
			SLPool *auxGM = new SLPool;

			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			StoragePoolTest(auxGM, 1);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    		std::cout << "SLPool was " << time_span.count() << " seconds.\n\n";
		}
		else{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			StoragePoolTest(nullptr, 1);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    		std::cout << "OS was " << time_span.count() << " seconds.\n\n";
		}
	
		if((count == 1) && (SLPoolTime > OSTime)) {
			std::cout << ">>> the memory manager is faster.\n";
		}
		else if((count == 1) && (OSTime < SLPoolTime)) {
			std::cout << ">>> the OS is faster.\n";
		}
	}
}