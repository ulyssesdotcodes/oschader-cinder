#pragma once

#include "FragmentProgram.h"

class ProgramFactory {
public:
	ProgramFactory();
	ProgramRef createProgram(std::string);

private:
	std::map<std::string, std::function<ProgramRef()>> mConstructorMap;
};