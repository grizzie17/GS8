#include "stdafx.h"
#include "igloo/igloo.h"

#include "CKeyNames.h"
#include "UKeys.h"

using namespace igloo;

using namespace Yogi::Gadget;

Context(KeyNames_class)
{
	CKeyNames	m_keys;

	Spec(it_should_translate_keyname_into_charcode)
	{
		unsigned char	c = m_keys.GetKey("COMMA");

		AssertThat( c, Equals(UKEY_COMMA) );
	}

	Spec(keynames_should_be_caseless)
	{
		unsigned char	c = m_keys.GetKey("Comma");
		AssertThat( c, Equals(UKEY_COMMA) );

		c = m_keys.GetKey("PeRiOd");
		AssertThat( c, Equals(UKEY_PERIOD) );

		c = m_keys.GetKey("numpad0");
		unsigned char kNP0 = UKEY_NUMPAD0;
		AssertThat( (unsigned int)c, Equals((unsigned int)kNP0) );
	}

	Spec(it_should_return_zero_for_bad_keyname)
	{
		unsigned char	c = m_keys.GetKey("george");

		AssertThat( c, Equals(0u) );
	}

	Spec(it_should_translate_charcode_into_keyname)
	{
		CCharString	s = m_keys.GetName(UKEY_COMMA);

		AssertThat( (s == "COMMA"), IsTrue() );
	}

	Spec(it_should_retun_number_string_for_unknown_charcode)
	{
		CCharString	s = m_keys.GetName(999);

		AssertThat( (s == "#999"), IsTrue() );
	}
};
