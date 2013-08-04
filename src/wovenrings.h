#pragma once

#include "ofMain.h"
#define GUI_WIDTH 1000
#define GUI_HEIGHT 600
#define NUM_SIZES 2
#define NUM_COLORS 6

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
    const static int sizes_[NUM_SIZES];
    const static int colors_[NUM_COLORS];

private:
	void createRing(float x, float y, float r1, float r2);
	void createRingGroup(float x, float y, float r);
	void drawRingGroup(float x, float y, float r);

	float radius_;
};

	
