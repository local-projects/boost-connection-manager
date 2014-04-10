#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "BoostConnectionManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderSignalTestsApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    void badApproach();
    void goodApproach();
};

void CinderSignalTestsApp::setup()
{
    console() << "**The bad way." << endl;
    badApproach();
    
    console() << "\n** And the good way." << endl;
    goodApproach();
}

void CinderSignalTestsApp::badApproach()
{
    signals::connection connections;
    signals::signal<void()> signal1;
    signals::signal<void()> signal2;
    
    // THE WRONG WAY
    // long story short we make orphan connections which are never disconnected
    
    console() << connections.connected() << endl;
    connections = signal1.connect([this]{ console() << "Signal1" << endl; });
    console() << connections.connected() << endl;
    signal1();
    
    console() << "now two signals." << endl;
    connections = signal2.connect([this]{ console() << "Signal2" << endl; });
    console() << connections.connected() << endl;
    signal1();
    signal2();
    
    console() << connections.connected() << endl;
    connections.disconnect();
    console() << connections.connected() << endl;
    
    console() << "I'd expect there to be no reaction." << endl;
    signal1();
    signal2();
    
    connections.disconnect();
    console() << "should be no reaction." << endl;
    signal1();
    signal2();
    
}

void CinderSignalTestsApp::goodApproach()
{
    // and now with the connection manager
    BoostConnectionManager bcm;
    signals::signal<void()> signal1;
    signals::signal<void()> signal2;
    
    console() << bcm.connected() << endl;
    bcm = signal1.connect([this]{ console() << "Signal1" << endl; });
    console() << bcm.connected() << endl;
    signal1();
    
    console() << "now two signals." << endl;
    bcm += signal2.connect([this]{ console() << "Signal2" << endl; });
    console() << bcm.connected() << endl;
    signal1();
    signal2();
    
    console() << bcm.connected() << endl;
    bcm.disconnect();
    console() << bcm.connected() << endl;

    bcm.disconnect();
    console() << "should be no reaction." << endl;
    signal1();
    signal2();
    
    bcm = signal1.connect([this]{ console() << "Signal1" << endl; });
    bcm = signal2.connect([this]{ console() << "Signal2" << endl; });
    
    console() << "should only be signal 2." << endl;
    signal1();
    signal2();
    
}

void CinderSignalTestsApp::mouseDown( MouseEvent event )
{
}

void CinderSignalTestsApp::update()
{
}

void CinderSignalTestsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( CinderSignalTestsApp, RendererGl )
