#include "ProgramFactory.h"
#include "FragmentProgram.h"

using namespace ci;

const static std::string SHADER_DIR = "shaders/";

void ProgramFactory::setup(std::shared_ptr<ProgramState> state)
{
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("sine", std::bind(&FragmentProgram::create, state, SHADER_DIR + "sine.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("line_down", std::bind(&FragmentProgram::create, state, SHADER_DIR + "line_down.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("scale", std::bind(&EffectProgram::create, state, SHADER_DIR + "scale.frag")));
}

ProgramRef ProgramFactory::createProgram(std::string name) const
{
	return mConstructorMap.at(name)();
}
