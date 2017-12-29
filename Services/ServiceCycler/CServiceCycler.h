/*---------------------------------------------------------------------+\
|
|	CServiceCycler.h  --  brief description of what CServiceCycler.h is for
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
	08-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CServiceCycler
#define _H_CServiceCycler
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <time.h>

#include "VPluginService.h"

#include "IApplicationUser.h"
#include "IRepeater.h"

#include "CMutex.h"
#include "TArray.h"
#include "UPlatformThreads.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


const int NUM_DISPLAYS = 4;

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CServiceCycler*		CServiceCyclerPtr;
typedef class CServiceCycler&		CServiceCyclerRef;
typedef const class CServiceCycler&	ConstCServiceCyclerRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CServiceCycler : public VPluginService,
							implements_ IApplicationUser
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CServiceCycler );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IApplicationUser
	virtual
	bool	SetApplication
			(
			CApplicationGaugePtr	p	// IN:	application pointer
			);



public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

	typedef struct NPage
	{
		CCharString	sID;
		GFLOAT		fFrequency;
		IRepeater*	pIRepeater;

		NPage()
			: sID()
			, fFrequency(200.0f)
			, pIRepeater( 0 )
		{
		};

		NPage( const NPage& r )
			: sID( r.sID )
			, fFrequency( r.fFrequency )
			, pIRepeater( QI_( r.pIRepeater, IRepeater ) )
		{
		};

		~NPage()
		{
			if ( pIRepeater )
				pIRepeater->Release();
		};

		NPage&	operator = ( const NPage& r )
		{
			sID = r.sID;
			fFrequency = r.fFrequency;
			pIRepeater = r.pIRepeater;
			if ( pIRepeater )
				pIRepeater->AddRef();
			return *this;
		}
	} NPage;


//	protected functions  ------------------------------------------------


	static
	UThreadRtn
			RunGlue
			(
			void*	pVoid
			);

	UThreadRtn
			Run( void );

	bool	CycleRepeaters
			(
			void
			);

	bool	LoadRepeaters( void );


	void	CalculateMilliTime();




//	protected data  -----------------------------------------------------

	CApplicationGaugePtr	m_pApplication;

	TArray<NPage>			m_aNPage;

	CMutex					m_oMutex;
	long					m_nFrequency;	// milliseconds
	CCharString				m_sRepeaterList;

	UThreadHdl				m_hThread;

	bool					m_bInitDone;


	long					m_nMilliStart;
	long					m_nMilli;
	time_t					m_nTime;


private:
//	private types  ------------------------------------------------------

	typedef	VPluginService	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr pConfig,
			VPluginLibraryPtr		pLib
			);

	//	IService
public:
	virtual
	NResult	Start
			(
			void
			);

	virtual
	NResult	Stop
			(
			void
			);
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


NAMESPACE_GADGET_END


#endif /* _H_CServiceCycler */

