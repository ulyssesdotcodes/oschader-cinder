#include "TriggeredPassthrough.h"

#include <boost/algorithm/string.hpp>

ProgramRef TriggeredPassthrough::create(ProgramStateRef state)
{
	return ProgramRef(new TriggeredPassthrough(state));
}

void TriggeredPassthrough::onUpdateUniform(std::string name, float val)
{
	float thresh = 0.5;
	if (name.compare("trigger") == 0 && !mTriggered && val > thresh) {
		mTriggered = true;
		++mProgramIter;
		if (mProgramIter == mPrograms.end()) {
			mProgramIter = mPrograms.begin();
		}

		PassthroughProgram::updateUniform("program", *mProgramIter);
	}
	else if(name.compare("trigger") == 0 && mTriggered && val < thresh){
		mTriggered = false;
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

TriggeredPassthrough::TriggeredPassthrough(ProgramStateRef state) : PassthroughProgram(state), Program(nullptr, state), mTriggered(false)
{
	mProgramIter = mPrograms.end();
}