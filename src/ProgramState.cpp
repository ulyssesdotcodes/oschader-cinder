#include "ProgramState.h"


void ProgramState::setProgram(std::string id, std::string name)
{
	mState[id] = mFactory.createProgram(name);
}

void ProgramState::setUniform(std::string id, std::string name, float uniform)
{
	mState[id]->updateUniform(name, uniform);
}

void ProgramState::clearProgram(std::string id)
{
	return;
}

ProgramRef ProgramState::getProgram(std::string id)
{
	return mState[id];
}
