/*---------------------------------------------------------------------+\
|
|	XMLLite.h  --  Light weight XML Parser
|
|	Purpose:

		A very simple XML Parser that has an extemely small and constant
		memory foot print.

|
|	Restrictions/Warnings:

		This NOT a generalized DOM parser.  It is a single pass
		readonly parser.  You cannot backup and process a node twice.

		This parser depends upon a well-formed XML definition.
		No validation is done with regard to a DTD or XSD,
		however, an error is logged if the XML is not well formed.

		This parser does NOT support "preserve spaces", which means that
		leading spaces within a text/data node are dropped.

		We also do not support having tags that are nested within
		a text/data node.

		An Element that has a value (text) must be of the form:
		<element>Text String</element>
		The text string may be either simple text or a CDATA section.
		The text string is retrieved by using the NodeValue function.

|	Formats:
|	References:	http://www.w3.org/TR/REC-xml/
|	Notes:

		In normal usage TTokenizer is used to setup the connection/open
		the XML stream/file via the VReadCallBack.  Once that is done
		a pointer to TTokenizer is passed to TIterator.  The TIterator
		is used to access the nodes and attributes thereafter.

|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change to using UFloat.h to identify if we are building
		with fixed-point or not
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	06-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add HeaderRequired function that identifies whether the
		<?xml?> header is required or not.  The default should be
		required.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Change VIterator template class to have two arguments.
		The first is the data type and the second is the type
		of the Tokenizer.
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add ProcessCallBack function to VTokenizer which allows us
		to have a standardized method of processing input.
	10-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add GetName to VReadCallBack interface
		Add ErrorStreamName and ErrorToken functions
	03-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for NodeValueAsInt and NodeValueAsFloat
		Add NodeEmpty function
	26-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_XMLLite
#define _H_XMLLite
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "TCharDescriptor.h"
#include "TArray.h"
#include "fixed_t.h"
#include "UFloat.h"


/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

namespace Yogi { namespace XMLLite {

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef enum ETEXT_FORMAT
{
	ETF_ASCII,		// ASCII - file without byte order mark (or not a text file
	ETF_UTF8,		// UTF-8 format
	ETF_UTF16,		// UTF-16 format (Unicode wide-character)
} ETEXT_FORMAT ;


typedef char			CharASCII;
typedef unsigned char	CharUTF8;
typedef unsigned short	CharUTF16;


/*
	In the normal processing the only types that you should have to
	check on are the three ELEMENT types.  TEXT and CDATA are handled
	by the NodeValue() function.  Most people ignore the rest.
*/
typedef enum ENODETYPE
{
	NODE_NONE = 0,		// starting state

	NODE_ELEMENT,		// empty element "<tagname/>" or "<tagname>text</tagname>"
	NODE_ELEMENT_BEGIN,	// begining element "<tagname>" when it contains nested tags
	NODE_ELEMENT_END,	// ending element "</tagname>"

	NODE_TEXT,
	NODE_CDATA,

	NODE_COMMENT,

	NODE_HEADER,		// <?xml ...?>
	//NODE_ENTITY,
	NODE_PROCESSING_INSTRUCTION,
	//NODE_DOCTYPE,
	NODE_NOTATION,

	NODE_UNKNOWN,		// other
	NODE_BLANKS			// spaces between nodes (currently never returned)
} ENODETYPE;





/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/








/*---------------------------------------------------------------------+\
|	VReadCallBack														|
\+---------------------------------------------------------------------*/

class VReadCallBack
{
public:
//	public functions  ---------------------------------------------------

	/*
		Reads up to the specified bytes from the file (stream).

		In the future we will actually implement the 'eFmt' argument
		which will mean that this function will also be responsible
		for returning the data in the requested format.
	*/
	virtual
	size_t	Read					// RTN:	returns number of bytes actually read
			(
			void*			pBuffer,		// OUT: buffer to receive data
			size_t			nBytesToRead,	// IN:	number of bytes to read
			ETEXT_FORMAT	eFmt			// IN:	target format
			) = 0;

	/*
		Gets the size of the file (stream)
	*/
	virtual
	size_t	GetSize		// RTN:	return file (stream) size in bytes
			(
			void
			) = 0;

	/*
		Get a name associated with the call-back stream.
		For files this should be name of the file or
		at least a partial path with name.
	*/
	virtual
	size_t	GetName					// RTN:	string length of name
			(
			char*			sTarget,	// OUT:	buffer to receive name
			size_t			nSizeTarget	// IN:	size of target
			) = 0;
};





/*---------------------------------------------------------------------+\
|	template VTokenizer													|
\+---------------------------------------------------------------------*/


template < class T >
class VTokenizer
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			~VTokenizer() {};

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual
	bool	HeaderRequired
			(
			bool	bRequired	// indicates <?xml?> header is required
			) = 0;

	virtual
	bool	ProcessCallBack
			(
			VReadCallBack* pCallBack
			) = 0;

	virtual
	bool	Read( void ) = 0;

	// The Error method sets the error condition as well as the message
	virtual
	void	Error( const char* s ) = 0;

	// retrieves information about the error
	virtual
	index_t	ErrorLineNumber( void ) = 0;

	virtual
	Yogi::Core::TCharDescriptor<char>
			ErrorString( void ) = 0;

	virtual
	Yogi::Core::TCharDescriptor<T>
			ErrorToken( void ) = 0;
	virtual
	Yogi::Core::TCharDescriptor<char>
			ErrorStreamName( void ) = 0;


	/*
		returns the current nesting depth.
		a value of zero indicates that we are processing the XML
		"overhead" tags such as <?xml?> or <!DOCTYPE> etc.
	*/
	virtual
	int		NestDepth( void ) = 0;


	/*
		see the ENODETYPE description above
	*/
	virtual
	ENODETYPE
			NodeType( void ) = 0;
	
	virtual
	Yogi::Core::TCharDescriptor<T>
			NodeName( void ) = 0;


	/*
		returns whether the current node is empty.  Empty is defined
		as either <tag/> or <tag></tag>
	*/
	virtual
	bool	NodeEmpty( void ) = 0;
	
	virtual
	Yogi::Core::TCharDescriptor<T>
			NodeValue( void ) = 0;


	virtual
	long	NodeValueAsInt( void ) = 0;
	
	virtual
	GFLOAT
			NodeValueAsFloat( void ) = 0;


	virtual
	int		AttributeCount( void ) = 0;
	
	virtual
	Yogi::Core::TCharDescriptor<T>
			AttributeName( int idx ) = 0;
	
	virtual
	Yogi::Core::TCharDescriptor<T>
			AttributeValue( int idx ) = 0;
	
	virtual
	Yogi::Core::TCharDescriptor<T>
			AttributeValue( const T* sName ) = 0;

	
	virtual
	long	AttributeValueAsInt( const char* sName ) = 0;
	
	virtual
	long	AttributeValueAsInt( int idx ) = 0;
	
	virtual
	GFLOAT
			AttributeValueAsFloat( const char* sName ) = 0;
	
	virtual
	GFLOAT
			AttributeValueAsFloat( int idx ) = 0;


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


};








/*---------------------------------------------------------------------+\
|	template VIterator													|
\+---------------------------------------------------------------------*/


/*
	The Iterator class processes the direct child nodes
	of the node that was active when the Iterator was initialized.

	When the file is first opened the "active" node is empty, so the 
	first child is the <?xml?> node.
*/
template < class T, class TTok >
class VIterator
{
public:
	//VIterator( TTok* pTokenizer );
	//VIterator( VIterator<T>* p );
	//VIterator( VIterator<T>& r );
	virtual		~VIterator() {};

public:

	virtual bool				NextChild( void ) = 0;

	virtual ENODETYPE			NodeType( void ) = 0;
	virtual Yogi::Core::TCharDescriptor<T>	NodeName( void ) = 0;
	virtual bool				NodeEmpty( void ) = 0;

	virtual Yogi::Core::TCharDescriptor<T>	NodeValue( void ) = 0;

	virtual long				NodeValueAsInt( void ) = 0;
	virtual GFLOAT				NodeValueAsFloat( void ) = 0;

	virtual int					AttributeCount( void ) = 0;
	virtual Yogi::Core::TCharDescriptor<T>	AttributeName( int idx ) = 0;
	virtual Yogi::Core::TCharDescriptor<T>	AttributeValue( int idx ) = 0;
	virtual Yogi::Core::TCharDescriptor<T>	AttributeValue( const char* sName ) = 0;

	virtual long				AttributeValueAsInt( const char* sName ) = 0;
	virtual long				AttributeValueAsInt( int idx ) = 0;
	virtual GFLOAT				AttributeValueAsFloat( const char* sName ) = 0;
	virtual GFLOAT				AttributeValueAsFloat( int idx ) = 0;

	virtual void				Error( const char* s ) = 0;


	virtual TTok*				Tokenizer( void ) = 0;
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



#endif /* _H_XMLLite */

