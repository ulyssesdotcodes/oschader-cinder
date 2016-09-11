#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Capture.h"

class CameraSource {
public:
	CameraSource();
	ci::gl::TextureRef getTexture();
	void update();

private:
	ci::CaptureRef mCapture;
	ci::gl::Texture2dRef mCaptureTex;
};