#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OschaderCinderApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void OschaderCinderApp::setup()
{
}

void OschaderCinderApp::mouseDown( MouseEvent event )
{
}

void OschaderCinderApp::update()
{
}

void OschaderCinderApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( OschaderCinderApp, RendererGl )
