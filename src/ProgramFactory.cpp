#include "ProgramFactory.h"

#include "EffectRect.h"
#include "FadeEffect.h"
#include "FragmentProgram.h"
#include "LayerProgram.h"
#include "PassthroughProgram.h"

using namespace ci;

const static std::string SHADER_DIR = "shaders/";

void ProgramFactory::setup(std::shared_ptr<ProgramState> state)
{
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("passthrough", std::bind(&PassthroughProgram::create, state)));

	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("add", std::bind(&LayerProgram::create, state, SHADER_DIR + "additive_blend.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("audio_data", std::bind(&FragmentProgram::create, state, SHADER_DIR + "audio_data.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("dots", std::bind(&FragmentProgram::create, state, SHADER_DIR + "dots.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("fade", std::bind(&FadeEffect::create, state)));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("line_down", std::bind(&FragmentProgram::create, state, SHADER_DIR + "line_down.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("scale", std::bind(&EffectRect::create, state, SHADER_DIR + "scale.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("sine", std::bind(&FragmentProgram::create, state, SHADER_DIR + "sine.frag")));
	mConstructorMap.insert(std::pair<std::string, std::function<ProgramRef()>>("repeat", std::bind(&EffectRect::create, state, SHADER_DIR + "repeat.frag")));
}

ProgramRef ProgramFactory::createProgram(std::string name) const
{
	return mConstructorMap.at(name)();
}
