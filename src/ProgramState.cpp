#include "ProgramState.h"

#include "ProgramFactory.h"

void ProgramState::setProgram(std::string id, std::string name, const ProgramFactory &factory)
{
	auto s = mState.find(id);
	if(s == mState.end() || s->second.first != name) {
		mState[id] = std::pair<std::string, ProgramRef>(name, factory.createProgram(name));
	}
}

void ProgramState::setUniform(std::string id, std::string name, float uniform)
{
	mState[id].second->updateUniform(name, uniform);
}

void ProgramState::clearProgram(std::string id)
{
	return;
}

ProgramRef ProgramState::getProgram(std::string id)
{
	auto p = mState.find(id);
	return p == mState.end() ? nullptr : mState.at(id).second;
}
