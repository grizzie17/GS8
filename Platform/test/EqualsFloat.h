#ifndef _H_EqualsFloat
#define _H_EqualsFloat
#pragma once

#include <float.h>


#define EqualsFloat(x, ...)	Fulfills(EqualsFloating(x, ## __VA_ARGS__ ))


struct EqualsFloating
{
	double	m_expected;
	double	m_tolerance;

	EqualsFloating( const double expect ) 
		: m_expected(expect)
		, m_tolerance(0.000075)
	{
	}

	EqualsFloating( const double expect, const double tol )
		: m_expected(expect)
		, m_tolerance(tol)
	{
	}
	bool	Matches( const double actual ) const
	{
		if ( m_expected + m_tolerance < actual )
			return false;

		if ( actual < m_expected - m_tolerance )
			return false;

		return true;
	}

	friend std::ostream& operator<<(std::ostream& stm, const EqualsFloating& );
};

inline
std::ostream& operator<<
		(
		std::ostream& stm, 
		const EqualsFloating& rEq
		)
{
	stm << rEq.m_expected;
	return stm;
}




#endif
