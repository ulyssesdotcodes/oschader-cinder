#pragma once

#include "ProgramRect.h"

class FragmentProgram : public ProgramRect {
public:
	static BaseProgramRef create(const ci::fs::path);
};