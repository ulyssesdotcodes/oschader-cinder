#pragma once

#include "ProgramRect.h"

class FragmentProgram : public ProgramRect {
public:
	static ProgramRef create(ProgramStateRef, const ci::fs::path);
};