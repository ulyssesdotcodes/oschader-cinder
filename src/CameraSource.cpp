#include "CameraSource.h"

using namespace ci;

CameraSource::CameraSource() : mCaptureTex(gl::Texture2d::create(1280, 720))
{
	if (Capture::getDevices().size() > 0) {
		mCapture = Capture::create(1280, 720);
	}
}

ci::gl::TextureRef CameraSource::getTexture()
{
	update();
	return mCaptureTex;
}

void CameraSource::update()
{
	if (mCapture && mCapture->checkNewFrame()) {
		mCaptureTex->update(*mCapture->getSurface());
	}
}
