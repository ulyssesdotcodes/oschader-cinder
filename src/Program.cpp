#include "Program.h"

using namespace ci;
using namespace input;

Program::Program(gl::BatchRef batch, ProgramStateRef state) : mBatch(batch), mState(state)
{
}

ci::gl::BatchRef Program::batch()
{
	return mBatch;
}

void Program::updateUniform(std::string name, float val) {
	auto iter = mInputUniforms.find(name);
	if (iter != mInputUniforms.end()) {
		mInputUniforms.erase(name);
	}
	mBatch->getGlslProg()->uniform("i_" + name, val);
}

void Program::updateUniform(std::string name, std::string val, float modifier) {
	auto iter = mInputUniforms.find(name);
	InputType it = parseInputType(val);

	if (it == InputType::NULL_T) {
		throw Exception("Invalid input type"); // Can do because it's haskell and we'll constrain types
		return;
	}

	if (iter == mInputUniforms.end()) {
		mInputUniforms.insert(std::make_pair(name, std::make_pair(it, modifier)));
	}
	else {
		mInputUniforms[name] = std::make_pair(it, modifier);
	}
}

void Program::updateUniform(std::string name, int val) {
	mBatch->getGlslProg()->uniform("i_" + name, val);
}

// Note that it uses fbo a
gl::Texture2dRef Program::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef _)
{
	{
		gl::ScopedFramebuffer fbo(base);

		draw();
	}

	auto effect = getEffect();
	if (effect) {
		return effect->getColorTexture(base, _);
	}

	return base->getColorTexture();
}

void Program::draw() {
	int i = 1; // Leave room for effect
	for (std::pair<std::string, std::pair<InputType, float>> e : mInputUniforms) {
		if(isTexture(e.second.first)) {
			mBatch->getGlslProg()->uniform("i_" + e.first, i);
			getTexture(mLastInputState, e.second.first)->bind(i);
			mBatch->getGlslProg()->uniform("i_" + e.first + "_mod", e.second.second);
			++i;
		}
	}

	gl::pushViewport();
	gl::pushMatrices();

	auto cam = camera();
	std::shared_ptr<ci::ivec2> win = matrixWindow();
	if (cam) {
		gl::setMatrices(*cam);
	}
	else if (win) {
		gl::setMatricesWindow(*win);
	}

	mBatch->draw();

	gl::popMatrices();
	gl::popViewport();
}

ProgramRef Program::getEffect()
{
	if(mEffect) {
		return mState->getProgram(*mEffect);
	}

	return nullptr; 
}

ProgramRef Program::getProgram(std::string id)
{
	return mState->getProgram(id);
}

void Program::setEffect(std::string eff)
{
	mEffect = std::make_shared<std::string>(eff);
}

void Program::clearEffect()
{
	mEffect = nullptr;
}

void Program::setConnection(std::string)
{
	throw Exception("Can't set the combinator of a regular prog.");
}

void Program::update(input::InputState s)
{
	for (std::pair<std::string, std::pair<InputType, float>> e : mInputUniforms) {
		if(isFloat(e.second.first)) {
			mBatch->getGlslProg()->uniform("i_" + e.first, getFloat(s, e.second.first) * e.second.second);
		}
	}

	mLastInputState = s;
}
