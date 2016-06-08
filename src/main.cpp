#include <iostream>

#include "drive_gremlins.cpp"

/**
 \mainpage
 \author Nalbert Gabriel
 \date 06 de junho de 2016
 \brief This code is the implementation of a memory manager for C++
*/

/**
*	@brief		The main is were the code run. The function simulation() is the only code called in the main.
*	@return		The main return EXIT_SUCCESS if the program finished without problem.
*/
main(int argc, char const *argv[]) {

	// simulate a code using the GM
	simulation();

	return EXIT_SUCCESS;
}
