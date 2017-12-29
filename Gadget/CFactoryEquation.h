/*---------------------------------------------------------------------+\
|
|	CFactoryEquation.h  --  make an equation object
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
	08-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a warning that was caused by the deprecated operation
		of passing a string literal to a 'char*' it should be
		'const char*'
	08-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Allow meaningful error messages to be returned to the caller
	18-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix a problem where we might run-off the end of memory
		if we did not correctly balance the quotes.
	14-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for inline comments within equations
	30-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Very nice optimization that recognizes when an operator
		is acting on constants and as a result the result will be
		a constant.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		If a variable is identified as a constant value (locked)
		generate a 'constant' node instead of a 'variable'.
		Change behavior so we will mark the equation as bad if the
		'variable' does not exist in the dictionary.
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fixed a bug where we were not correctly setting the 'm_bConstant'
		member to true.  This was flagged by the GCC++ 'warning' message.
		This proves that it is important to resolve ALL warnings.
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for special constant types that are read directly
		from the gauge or other object
	06-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryEquation
#define _H_CFactoryEquation
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VEquation.h"
#include "VPanelChild.h"
#include "CColor.h"
#include "VDictionary.h"
#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CFactoryEquation*		CFactoryEquationPtr;
typedef class CFactoryEquation&		CFactoryEquationRef;

class VFactoryEquationToken;

typedef enum EquationTokenType
{
	T_UNDEFINED = 0,
	T_CONSTANT,
	T_VARIABLE,
	T_OPERATOR
} EquationTokenType;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryEquation
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryEquation();
	virtual			~CFactoryEquation();

public:
//	public types  -------------------------------------------------------

	typedef enum FEquationTargets
	{
		E_UNDEFINED,
		E_BOOLEAN,
		E_COORDINATE,
		E_LENGTH,
		E_COLOR,
		E_STRING
	} FEquationTargets;

	typedef struct MapToken
	{
		const char*				sToken;		// +, /, abs ...
		VFactoryEquationToken*	pFactory;
		const char*				sValue;

	} MapToken;

//	public functions  ---------------------------------------------------

	VEquationPtr	MakeEquation
					(
					FEquationTargets eTarget,
					const char*	sString,
					int			nLength = -1
					);

	void			Push( VEquationPtr p, EquationTokenType eType );
	VEquationPtr	Pop( EquationTokenType* pType );

	void			SetDictionary( VDictionaryPtr pDict );

	VEquationPtr	EqFromNumber( const char* s, size_t n );

	bool			HasGVariables( void );
	bool			IsConstant( void );
	void			SetConstant( void );
	void			SetError( const char* s );
	char*			GetError( void );

	// cleared at end of MakeEquation call
	void			SetGauge( VPanelChildPtr p );
	VPanelChildPtr	GetGauge( void );


protected:
//	protected types  ----------------------------------------------------


	typedef struct StackEntry
	{
		VEquationPtr		pNode;
		EquationTokenType	eType;
	} StackEntry;

//	protected functions  ------------------------------------------------

	VEquationPtr	EqFromString( const char* s, size_t n );
	VEquationPtr	EqFromVariable( EquationTokenType* pType,
									const char* s, size_t n );
	VEquationPtr	EqFromNumberHex( const char* s, size_t n );
	VEquationPtr	EqFromNumberInteger( const char* s, size_t n );
	VEquationPtr	EqFromNumberFloat( const char* s, size_t n );
	VEquationPtr	EqFromRegister( const char* s, size_t n );

	bool			IsBlank( char c );
	const char*		SkipBlanks( const char* s );
	int				TokenComment( const char* s, const char* sEnd );
	int				TokenString( const char* s, const char* sEnd );
	bool			TokenNumberHex( const char* s, size_t n );
	bool			TokenNumberInteger( const char* s, size_t n );
	bool			TokenNumberFloat( const char* s, size_t n );
	bool			TokenRegister( const char* s, size_t n );
	int				TokenVariable( const char* s, const char* sEnd );
	int				TokenNonBlank( const char* s, const char* sEnd );

	MapToken*		FindMapEntry( const char* sToken, int nToken );
	bool			FindColorEntry( const char* sToken, size_t nToken, CColorPtr pColor );

	// returns	0 for no entry
	//			1 for valid entry
	//			-1 for valid entry and locked
	int				VariableValid( char* sName );

//	protected data  -----------------------------------------------------

	FEquationTargets	m_eTarget;
	StackEntry			m_aStack[40];
	int					m_nStack;

	char*				m_sString;
	int					m_nString;
	char*				m_sToken;
	int					m_nToken;

	bool				m_bGVariables;
	bool				m_bConstant;
	int					m_nNodeCount;
	bool				m_bError;
	char				m_sErrorString[128];

	VPanelChildPtr		m_pGauge;
	VDictionaryPtr		m_pDictionary;

	static MapToken*	g_pMap;
	static long			g_nMap;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};

class VFactoryEquationToken
{
public:
	virtual VEquationPtr
				MakeToken
				(
				EquationTokenType*	pTokenType,		// OUT
				CFactoryEquation::MapToken*	pMap,
				const char*			sToken,
				int					n,
				CFactoryEquationPtr	pFactory
				) = 0;
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


inline
void	CFactoryEquation::SetConstant
		(
		void
		)
{
	m_bConstant = true;
}



NAMESPACE_GADGET_END



#endif /* _H_CFactoryEquation */

