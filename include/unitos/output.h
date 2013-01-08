/* Copyright (C) Ville Ruusutie, 2010 */

#pragma once
#ifndef unitos_output_h
#define unitos_output_h

#include "unitos/ustring.h"

namespace unitos {

class Output
{
public:
	Output() {}
	virtual ~Output() {}
	virtual void operator<<(unitos::String const& text) = 0;
};

}; // end of unitos

#endif
