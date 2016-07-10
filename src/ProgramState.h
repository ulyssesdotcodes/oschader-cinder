#pragma once

#include "Program.h"


class ProgramFactory;

class ProgramState {
public:
	void setProgram(std::string id, std::string name, const ProgramFactory&);
	void setUniform(std::string id, std::string name, float uniform);
	void clearProgram(std::string id);
	ProgramRef getProgram(std::string id);
	
private:
	std::map<std::string, std::pair<std::string, ProgramRef>> mState;
};