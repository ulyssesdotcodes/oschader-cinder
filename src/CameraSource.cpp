#include "CameraSource.h"

using namespace ci;

CameraSource::CameraSource() : mCapture(Capture::create(1280, 720)), mCaptureTex(gl::Texture2d::create(1280, 720))
{
}

ci::gl::TextureRef CameraSource::getTexture()
{
	update();
	return mCaptureTex;
}

void CameraSource::update()
{
	if (mCapture->checkNewFrame()) {
		mCaptureTex->update(*mCapture->getSurface());
	}
}
