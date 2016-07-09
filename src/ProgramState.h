#pragma once

#include "Program.h"
#include "ProgramFactory.h"

class ProgramState {
public:
	void setProgram(std::string id, std::string name);
	void setUniform(std::string id, std::string name, float uniform);
	void clearProgram(std::string id);
	ProgramRef getProgram(std::string id);
	
private:
	ProgramFactory mFactory;
	std::map<std::string, ProgramRef> mState;
};