#pragma once

#include "EffectProgram.h"

#include "ProgramState.h"

class ProgramFactory {
public:
	void setup(std::shared_ptr<ProgramState>);
	ProgramRef createProgram(std::string) const;

private:
	std::map<std::string, std::function<ProgramRef()>> mConstructorMap;
};