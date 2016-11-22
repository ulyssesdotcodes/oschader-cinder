#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

#include "InputResolver.h"
#include "ProgramState.h"

typedef std::shared_ptr<class Program> ProgramRef;

class Program {
public:
	virtual std::shared_ptr<ci::Camera> camera() = 0;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() = 0;
	ci::gl::BatchRef batch();

	virtual void updateUniform(std::string name, float val);
	virtual void updateUniform(std::string name, std::string);
	virtual void updateUniform(std::string name, int val);

	virtual void updateInputUniform(std::string name, std::string, std::vector<float> modifiers);

	virtual void onUpdateUniform(std::string name, float val);

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra);

	virtual void setEffect(std::string);
	virtual void clearEffect();
	virtual void addLayer(std::string);
	virtual void clearLayers();

	void update(std::shared_ptr<input::InputResolver>);

	virtual void onUpdate();

	virtual void bindInputTexes(ci::gl::GlslProgRef);

protected:
	ProgramStateRef mState;
	ci::gl::BatchRef mBatch;
	Program(ci::gl::BatchRef, ProgramStateRef);
	virtual void draw();
	ProgramRef getEffect();
	ProgramRef getProgram(std::string);
	ci::gl::TextureRef getInputTex(std::string str);

private:
	std::map<std::string, input::InputParameters> mInputUniforms;
	std::shared_ptr<std::string> mEffect;
	std::map<std::string, ci::gl::TextureRef> mLastInputTextures;

	std::pair<int, int> mOverflowCheck;
};