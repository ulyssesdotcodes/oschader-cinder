#pragma once

#include "FragmentProgram.h"

class ProgramFactory {
public:
	ProgramFactory();
	BaseProgramRef createProgram(std::string);

private:
	std::map<std::string, std::function<BaseProgramRef()>> mConstructorMap;
};