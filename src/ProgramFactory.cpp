#include "ProgramFactory.h"

using namespace ci;

const static std::string SHADER_DIR = "shaders/";

ProgramFactory::ProgramFactory()
{
	mConstructorMap = std::map<std::string, std::function<BaseProgramRef()>>();

	mConstructorMap.insert(std::pair<std::string, std::function<BaseProgramRef()>>("sine", std::bind(&FragmentProgram::create, SHADER_DIR + "sine.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<BaseProgramRef()>>("line_down", std::bind(&FragmentProgram::create, SHADER_DIR + "line_down.frag")));
}

BaseProgramRef ProgramFactory::createProgram(std::string name)
{
	return mConstructorMap.at(name)();
}
