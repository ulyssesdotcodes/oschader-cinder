#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Osc.h"

#include "ProgramFactory.h"

#include "AdditiveProgram.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OschaderCinderApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

private:
	ProgramRef mProg;

	std::array<BaseProgramRef, 8> mPrograms;
};

void OschaderCinderApp::setup()
{
	ProgramFactory factory;
	mPrograms[0] = factory.createProgram("sine");
	mPrograms[1] = factory.createProgram("line_down");
	AdditiveProgramRef prog = AdditiveProgram::create(mPrograms[0]);
	prog->mappend(mPrograms[1]);
	mProg = prog;
}

void OschaderCinderApp::mouseDown( MouseEvent event )
{
}

void OschaderCinderApp::update()
{
	float time = app::getElapsedSeconds();
	std::for_each(mPrograms.begin(), mPrograms.end(), [time](ProgramRef prog) {
		if (prog) {
			prog->updateUniform("time", time);
		}
	});
}

void OschaderCinderApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 

	mProg->draw();
}

CINDER_APP(OschaderCinderApp, RendererGl(), [&](App::Settings *settings) {
	//FullScreenOptions options;
	//std::vector<DisplayRef> displays = Display::getDisplays();
	//settings->setConsoleWindowEnabled();
	//settings->setFullScreen(true, options);	
	//if (displays.size() > 1) {
	//	settings->setDisplay(displays[1]);
	//}
	//settings->setFrameRate(60.0f);
})
