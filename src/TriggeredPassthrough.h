#pragma once

#include "PassthroughProgram.h"

class TriggeredPassthrough : public virtual PassthroughProgram {
public:
	static ProgramRef create(ProgramStateRef state);

	virtual void onUpdateUniform(std::string name, float val);
	virtual void updateUniform(std::string name, std::string val) override;

protected:
	TriggeredPassthrough(ProgramStateRef state);

private:
	std::vector<std::string> mPrograms;
	std::vector<std::string>::iterator mProgramIter;
};
