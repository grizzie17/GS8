/*---------------------------------------------------------------------+\
|
|	CFactoryVehicleData.cpp  --  Load the VehicleData from XML
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	21-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for new standardized method of updating
		dictionary page.
    14-Dec-2009         R.Hosea			(Reviewed by: J.Griswold)
        Fixed gcc compile problem for omniscape
	10-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add a special "N:Alerts Active" variable that indicates
		that at least one "Alert" is active.
	31-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for Begin/EndUpdate on the active-page
	06-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Allow <?xml?> header to be optional
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Conversion to new hierarcy that uses the XMLParser as the
		base class
	18-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for Alerts
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	15-Sep-2009			M.Rose			(Reviewed by: J.Griswold)
		Manipulate code to satisfy linux gcc 4.2.1 compiler
	14-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <float.h>

#include "CFactoryVehicleData.h"

#include "UPlatform.h"
#include "CCharString.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CFactoryVehicleData - constructor

\+---------------------------------------------------------------------*/
CFactoryVehicleData::CFactoryVehicleData
		(
		void
		)
		: VFactory(),
		m_pActive( 0 ),
		m_pNotify( 0 ),
		m_sAAName()
{
	m_sAAName = "Alerts Active";
	::strcpy_s( m_sTrue, sizeof(m_sTrue), "Y" );
	::strcpy_s( m_sFalse,sizeof(m_sFalse), "N" );
}


/*---------------------------------------------------------------------+\

 * ~CFactoryVehicleData - destructor

\+---------------------------------------------------------------------*/
CFactoryVehicleData::~CFactoryVehicleData
		(
		void
		)
{
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * LoadData -

\+---------------------------------------------------------------------*/
bool	CFactoryVehicleData::LoadData
		(
		XMLLite::VReadCallBack*	pCallBack
		)
{
	bool	bResult = false;

	HeaderRequired( false );

	if ( ProcessCallBack( pCallBack ) )
	{
		CCharDescriptor	tName;
		XMLIterator		it( this );

		while ( it.NextChild() )
		{
			switch( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				tName = it.NodeName();
				if ( tName == "VehicleData" )
					bResult = VehicleData( &it );
				else
					it.Error( "Unexpected tag" );
				break;
            default:
                break;
			}
		}
		if ( 0 != NestDepth() )
			it.Error( "XML file is not well-formed" );

	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * SpecifyActivePage -

\+---------------------------------------------------------------------*/
bool	CFactoryVehicleData::SpecifyActivePage
		(
		VDictionaryPagePtr p
		)
{
	m_pActive = CDictPageActivePtr(p);
	return true;
}


/*---------------------------------------------------------------------+\

 * SpecifyNotifyPage -

\+---------------------------------------------------------------------*/
bool	CFactoryVehicleData::SpecifyNotifyPage
		(
		VDictionaryPagePtr	p
		)
{
	m_pNotify = CDictPageAlertsPtr(p);
	return true;
}





/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * VehicleData -

\+---------------------------------------------------------------------*/
bool	CFactoryVehicleData::VehicleData
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT_BEGIN:
			tName = it.NodeName();
			if ( tName == "Alerts" )
				bResult = Alerts( &it );
			else if ( tName == "Parameters" )
				bResult = Parameters( &it );
			else
				it.Error( "Unreconized tag in VehicleData node" );
			break;
		case XMLLite::NODE_ELEMENT:
			it.Error( "Malformed tags in VehicleData node" );
			break;
        default:
            break;
		}
	}


	return bResult;
}


/*---------------------------------------------------------------------+\

 * Alerts -

\+---------------------------------------------------------------------*/
bool	CFactoryVehicleData::Alerts
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = true;
	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	m_bNotifyActive = false;

	while ( it.NextChild() )
	{
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT:
			tName = it.NodeName();
			if ( tName == "Alert" )
				bResult = Alert( &it );
			else
				it.Error( "unrecognized tag within Alerts node" );
			break;
		case XMLLite::NODE_ELEMENT_BEGIN:
			it.Error( "malformed element within Alerts node" );
			break;
        default:
            break;
		}
	}


	CCharDescriptor	tAAValue;
	if ( m_bNotifyActive )
		tAAValue = CCharDescriptor( m_sTrue, 1 );
	else
		tAAValue = CCharDescriptor( m_sFalse, 1 );
	m_pNotify->Update( m_sAAName, tAAValue );

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Alert -

\+---------------------------------------------------------------------*/
bool	CFactoryVehicleData::Alert
		(
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;

	if ( pIt->NodeEmpty() )
	{
		CCharDescriptor	tName;
		CCharDescriptor	tValue;

		tName = pIt->AttributeValue( "ID" );
		if ( 0 < tName.Length() )
		{
			tValue = pIt->AttributeValue( "Value" );
			if ( 0 < tValue.Length() )
			{
				tValue.ConvertLowercase();
				char c = *tValue.Pointer();
				if ( ::strchr( "ty1", c ) )
					m_bNotifyActive = true;
				bResult = m_pNotify->Update( tName, tValue );
			}
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * Parameters -

\+---------------------------------------------------------------------*/
bool	CFactoryVehicleData::Parameters
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = true;
	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	if ( m_pActive )
		m_pActive->BeginUpdate();

	while ( it.NextChild() )
	{
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT:
			tName = it.NodeName();
			if ( tName == "Param" )
				bResult = Param( &it );
			else
				it.Error( "unrecognized tag within Parameters node" );
			break;
		case XMLLite::NODE_ELEMENT_BEGIN:
			it.Error( "malformed element within Parameters node" );
			break;
        default:
            break;
		}
	}

	if ( bResult )
	{
		if ( m_pActive )
			bResult = m_pActive->EndUpdate();
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * Param -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	CFactoryVehicleData::Param
		(
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = false;
	if ( pIt->NodeEmpty() )
	{
		CCharDescriptor	tName;

		tName = pIt->AttributeValue( "ID" );
		if ( 0 < tName.Length() )
		{
			bool			bValid = true;
			CCharDescriptor	tValue;

			tValue = pIt->AttributeValue( "Validity" );
			if ( 0 < tValue.Length() )
			{
				if ( tValue == "Valid"
					||	tValue == "ParmSpec"
					||	tValue == "Future" )
					bValid = true;
				else if ( tValue == "Error"
					||	tValue == "NA" )
					bValid = false;
				else
					bValid = false;
			}

			if ( bValid )
			{
				tValue = pIt->AttributeValue( "Value" );
				if ( 0 < tValue.Length() )
				{
					char	sValue[128];
					bResult = tValue.CopyTo( sValue, sizeof(sValue) );
					if ( bResult )
						bResult = m_pActive->Update( tName, sValue );
				}
			}
		}
	}
	return bResult;
}

//END_OVERRUN_WARNING















/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
