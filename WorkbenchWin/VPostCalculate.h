
#ifndef _H_VPostCalculate
#define _H_VPostCalculate
#pragma once



namespace Yogi { namespace Gadget {

class VPostCalculate
{
public:
	virtual
	void	PostCalculateNeeded( void ) = 0;

	virtual
	void	SetWindowTitle( const char* sName ) = 0;
};

}}

#endif
