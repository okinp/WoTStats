#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class WoTStatsApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void WoTStatsApp::setup()
{
}

void WoTStatsApp::mouseDown( MouseEvent event )
{
}

void WoTStatsApp::update()
{
}

void WoTStatsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( WoTStatsApp, RendererGl )
