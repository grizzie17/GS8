/*---------------------------------------------------------------------+\
|
|	VGDI.h  --  brief description of what VGDI.h is for
|
|	Purpose:
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
	29-Jun-2012			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VGDI
#define _H_VGDI
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "UPlatform.h"
#if defined( GL_GDI )		// brackets entire file


namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/
typedef class VGDI*			VGDIPtr;
typedef class VGDI&			VGDIRef;
typedef const class VGDI&	ConstVGDIRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class VGDI
{
//	class lifecycle  ----------------------------------------------------
public:
				VGDI();
				VGDI( VGDIRef r );	// copy constructor
	virtual		~VGDI();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VGDIRef		operator=( VGDIRef r );		// assignment

	virtual
	bool		Select( HDC h );

	virtual
	bool		Deselect( void );

	virtual
	uintmax_t	GetHash( void ) const;

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	uintmax_t	m_nHash;
	HGDIOBJ		m_hPrev;
	HDC			m_hdc;		// DC on which the GDI object is selected

private:
//	private types  ------------------------------------------------------

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

};

/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/

}}

#endif	// GL_GDI



#endif /* _H_VGDI */
