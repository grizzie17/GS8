// Gadget_specs.cpp : Defines the entry point for the console application.
//

#include "CheckLeaks.h"
#include "MyTestRunner.h"




int main(int argc, const char* argv[])
{
	CHECK_LEAKS
	int	nResult = Runner(argc, argv);
	return nResult != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
