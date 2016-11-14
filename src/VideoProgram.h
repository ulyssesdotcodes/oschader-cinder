#pragma once

#include "Program.h"

#include "cinder/gl/gl.h"
//#include "ciWMFVideoPlayer.h"

class VideoProgram : public virtual Program {
public:
	static ProgramRef create(ProgramStateRef state);

	virtual std::shared_ptr<ci::Camera> camera() override;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() override;

	virtual void update(input::InputState) override;

	virtual void updateUniform(std::string name, std::string val) override;
	virtual void onUpdateUniform(std::string name, float val) override;

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra) override;

protected:
	VideoProgram(ProgramStateRef);

private:
	bool mLoaded;
	std::string mPath;
	//ciWMFVideoPlayer mVideo;
	float      mVideoPos;
	float      mVideoDuration;
};

