#include "ProgramState.h"

void ProgramState::setProgram(std::string id, std::string name, std::function<std::shared_ptr<Program>()> createProgram)
{
	auto s = mState.find(id);
	if(s == mState.end() || s->second.first != name) {
		mState[id] = std::pair<std::string, std::shared_ptr<Program>>(name, createProgram());
	}
}

void ProgramState::clearProgram(std::string id)
{
	return;
}

std::shared_ptr<Program> ProgramState::getProgram(std::string id)
{
	auto p = mState.find(id);
	return p == mState.end() ? nullptr : mState.at(id).second;
}
