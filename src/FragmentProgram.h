#pragma once

#include "ProgramRect.h"

class FragmentProgram : public ProgramRect {
public:
	static ProgramRef create(const ci::fs::path);
};