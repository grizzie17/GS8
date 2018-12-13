/*---------------------------------------------------------------------+\
|
|	VPluginFactory.h  --  brief description of what VPluginFactory.h is for
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
	12-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		add pseudo singleton class and macro
	18-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VPluginFactory
#define _H_VPluginFactory
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"
#include "VSupports.h"

#include "CCharString.h"
#include "CCharDescriptor.h"

#include "UDeclSpec.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/



#define	PLUGIN_CREATE_FACTORY( sClass )		\
	typedef TPluginFactory<sClass>	sClass##PluginFactory;	\
extern "C"											\
SHLIB_EXPORT											\
	VPluginFactoryPtr								\
	CreatePluginFactory								\
	(												\
	void											\
	)												\
{													\
	VPluginFactoryPtr	p = new sClass##PluginFactory( #sClass );	\
	return p;										\
}



#define	PLUGIN_SSINGLETON_FACTORY( sClass )		\
typedef TPluginSSingletonFactory<sClass>	sClass##PluginFactory;	\
extern "C"												\
SHLIB_EXPORT												\
VPluginFactoryPtr										\
		CreatePluginFactory								\
		(												\
		void											\
		)												\
{														\
	VPluginFactoryPtr	p = new sClass##PluginFactory( #sClass );	\
	return p;											\
}

namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class VPluginFactory*		VPluginFactoryPtr;
typedef class VPluginFactory&		VPluginFactoryRef;
typedef const class VPluginFactory&	ConstVPluginFactoryRef;


/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

class VPluginFactory
{
public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual
	ISupportsPtr	Make
					(
					ISupportsPtr	pOwner
					) = 0;

	virtual
	void			DestroyFactory( void ) = 0;

protected:

	virtual			~VPluginFactory(){};

};

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/


template < class T >
class TPluginFactory : public VPluginFactory
{
public:

	TPluginFactory() : m_sName() {};
	TPluginFactory( const char* sName ) : m_sName( sName ) {};

	virtual
	ISupportsPtr	Make( ISupportsPtr pOwner )
	{
		T*	p = new T( m_sName.Pointer(), (ISupportsPtr)( pOwner ) );
		return ROOT_ISUPPORTS(p);
	};

	virtual
	void			DestroyFactory( void )
	{
		delete this;
	};

protected:
	virtual		~TPluginFactory() {};

	Yogi::Core::CCharString	m_sName;

};


template < class T >
class TPluginSSingletonFactory : public VPluginFactory
{
public:
	TPluginSSingletonFactory() : inherited(), g_pSingle(0) {};
	TPluginSSingletonFactory( const char* sName ) : inherited( sName ), g_pSingle(0) {};

	virtual
	ISupportsPtr	Make( ISupportsPtr pOwner )
	{
		if ( g_pSingle )
		{
			g_pSingle->AddRef();
			return g_pSingle;
		}
		else
		{
			T*	p = new T( this->m_sName, (ISupportsPtr)( pOwner ) );
			if ( p )
				g_pSingle = p;
			return ROOT_ISUPPORTS(p);
		}
	};

	virtual
	void			DestroyFactory( void )
	{
		if ( g_pSingle )
		{
			NRefCount	n;
			do
			{
				n = g_pSingle->Release();
			} while ( 0 < n );
		}
		delete this;
	};

protected:
	virtual	~TPluginSSingletonFactory(){};

	T*	g_pSingle;

private:

	typedef TPluginFactory<T>	inherited;


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



#endif /* _H_VPluginFactory */
