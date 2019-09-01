/*---------------------------------------------------------------------+\
|
|	VInterface.h  --  brief description of what VInterface.h is for
|
|	Purpose:
|	File Custodian:		J.Griswold
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VInterface
#define _H_VInterface
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Common {


#define DYNAMIC_INTERFACE_NAME( sInterface )	\
	public:								\
		virtual const char* GetInterfaceName( void ) const throw() \
		{								\
			return #sInterface;			\
		}

#define DYNAMIC_CLASS_NAME( sClass )	\
	public:								\
		virtual const char* GetClassName( void ) const throw() \
		{								\
			return #sClass;				\
		}



/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class VInterface*		VInterfacePtr;
typedef class VInterface&		VInterfaceRef;
typedef const class VInterface&	ConstVInterfaceRef;

typedef struct IID
{
	long	n[4];
} IID;

typedef const IID&		ConstIIDRef;

typedef unsigned long	RefCount;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VInterface
{
//	class lifecycle  ----------------------------------------------------
public:
	//	an interface does not necessarily define an object

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual
	void*		QueryInterface( ConstIIDRef rIID, long* pResult = 0 );

	virtual
	RefCount	AddRef( void ) = 0;

	virtual
	RefCount	Release( void ) = 0;

	virtual
	long		GetRefCount( void ) = 0;

	virtual
	void*		QueryInterfaceByName( const char* sName ) = 0;

	virtual
	const char*	GetInterfaceName( void ) const throw() = 0;


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


};

/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

}}



#endif /* _H_VInterface */
