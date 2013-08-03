#include "ofMain.h"
#include "wovenrings.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	window.setGlutDisplayString("rgba double samples>=4");
	ofSetupOpenGL(&window, GUI_WIDTH, GUI_HEIGHT, OF_WINDOW);

	ofRunApp(new testApp());
}
