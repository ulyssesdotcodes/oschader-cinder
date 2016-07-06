#pragma once

#include "FragmentProgram.h"

typedef std::shared_ptr<class AdditiveProgram> AdditiveProgramRef;

class AdditiveProgram : public BaseProgram {
public:
	static AdditiveProgramRef create(BaseProgramRef a);
	virtual void mappend(BaseProgramRef b) override;
	virtual std::shared_ptr<ci::Camera> camera();
	virtual std::shared_ptr<ci::ivec2> matrixWindow();
	virtual ci::gl::TextureRef getColorTexture();
	virtual void updateUniform(std::string name, float val);

	virtual void draw();

private:
	AdditiveProgram(BaseProgramRef, BaseProgramRef);
	BaseProgramRef mBlendProg;

	BaseProgramRef mA;
	BaseProgramRef mB;
};