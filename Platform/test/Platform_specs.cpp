// Common_tests.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include "stdafx.h"
#include "CheckLeaks.h"
#include "MyTestRunner.h"





int main(int argc, const char* argv[])
{
	CHECK_LEAKS
	int	nResult = Runner(argc, argv);
	exit( nResult );
}
