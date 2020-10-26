#ifndef iglookludge_h
#define iglookludge_h

#include "gtest/gtest.h"


#define Context(s) \
	const char iglooContext[] = #s;


#define Spec(s) \
	TEST( igloo)




#endif // iglookludge_h
