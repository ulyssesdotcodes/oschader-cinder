#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

typedef std::shared_ptr<class Program> ProgramRef;

class Program {
public:
	virtual std::shared_ptr<ci::Camera> camera() = 0;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() = 0;
	ci::gl::BatchRef batch();

	virtual void updateUniform(std::string name, float val);
	virtual void updateUniform(std::string name, int val);

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef, ci::gl::FboRef);
	virtual void draw(ci::gl::FboRef, ci::gl::FboRef);
	virtual void draw();

	virtual void setBase(std::string);

protected:
	Program(ci::gl::BatchRef);


private:
	ci::gl::BatchRef mBatch;
};