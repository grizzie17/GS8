
#ifndef _H_VPostCalculate
#define _H_VPostCalculate
#pragma once

#include "NamespaceGadget.h"

NAMESPACE_GADGET_BEGIN

class VPostCalculate
{
public:
	virtual
	void	PostCalculateNeeded( void ) = 0;

	virtual
	void	SetWindowTitle( const char* sName ) = 0;
};

NAMESPACE_GADGET_END

#endif
