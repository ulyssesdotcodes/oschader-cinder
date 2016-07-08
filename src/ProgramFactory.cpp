#include "ProgramFactory.h"

using namespace ci;

const static std::string SHADER_DIR = "shaders/";

ProgramFactory::ProgramFactory()
{
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("sine", std::bind(&FragmentProgram::create, SHADER_DIR + "sine.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("line_down", std::bind(&FragmentProgram::create, SHADER_DIR + "line_down.frag")));
}

ProgramRef ProgramFactory::createProgram(std::string name)
{
	return mConstructorMap.at(name)();
}
