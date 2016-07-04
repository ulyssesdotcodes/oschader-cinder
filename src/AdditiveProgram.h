#pragma once

#include "FragmentProgram.h"

typedef std::shared_ptr<class AdditiveProgram> AdditiveProgramRef;

class AdditiveProgram : public BaseProgram {
public:
	static AdditiveProgramRef create(BaseProgramRef a);
	void mappend(BaseProgramRef b);
	virtual std::shared_ptr<ci::Camera> camera();
	virtual std::shared_ptr<ci::ivec2> matrixWindow();
	virtual ci::gl::TextureRef getColorTexture();

	virtual void draw();

private:
	AdditiveProgram(BaseProgramRef, BaseProgramRef);
	BaseProgramRef mBlendProg;

	BaseProgramRef mA;
	BaseProgramRef mB;
};