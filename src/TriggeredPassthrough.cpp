#include "TriggeredPassthrough.h"

#include <boost/algorithm/string.hpp>

ProgramRef TriggeredPassthrough::create(ProgramStateRef state)
{
	return ProgramRef(new TriggeredPassthrough(state));
}

void TriggeredPassthrough::onUpdateUniform(std::string name, float val)
{
	if (name.compare("trigger") == 0 && val > 0.95) {
		++mProgramIter;
		if (mProgramIter == mPrograms.end()) {
			mProgramIter = mPrograms.begin();
		}

		PassthroughProgram::updateUniform("program", *mProgramIter);
	}
}

void TriggeredPassthrough::updateUniform(std::string name, std::string val)
{
	if (name.compare("program") == 0) {
		auto currentIndex = mProgramIter == mPrograms.end() ? 0 : mProgramIter - mPrograms.begin();
		boost::trim(val);
		mPrograms = boost::algorithm::split(mPrograms, val, boost::is_any_of(" "));
		mProgramIter = mPrograms.begin() + currentIndex;
	}
}

TriggeredPassthrough::TriggeredPassthrough(ProgramStateRef state) : PassthroughProgram(state), Program(nullptr, state)
{
	mProgramIter = mPrograms.end();
}