#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

#include "InputState.h"
#include "ProgramState.h"

typedef std::shared_ptr<class Program> ProgramRef;

class Program {
public:
	virtual std::shared_ptr<ci::Camera> camera() = 0;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() = 0;
	ci::gl::BatchRef batch();

	virtual void updateUniform(std::string name, float val);
	virtual void updateUniform(std::string name, std::string, float modifier);
	virtual void updateUniform(std::string name, std::string);
	virtual void updateUniform(std::string name, int val);

	virtual void onUpdateUniform(std::string name, float val);

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra);

	virtual void setEffect(std::string);
	virtual void clearEffect();
	virtual void addLayer(std::string);
	virtual void clearLayers();

	virtual void update(input::InputState);

protected:
	ProgramStateRef mState;
	ci::gl::BatchRef mBatch;
	Program(ci::gl::BatchRef, ProgramStateRef);
	virtual void draw();
	ProgramRef getEffect();
	ProgramRef getProgram(std::string);

private:
	std::map<std::string, std::pair<input::InputType, float>> mInputUniforms;
	std::shared_ptr<std::string> mEffect;
	input::InputState mLastInputState;

	std::pair<int, int> mOverflowCheck;
};