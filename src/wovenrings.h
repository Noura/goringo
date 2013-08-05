#pragma once

#include "ofMain.h"
#define GUI_WIDTH 600
#define GUI_HEIGHT 800

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

private:
	void createRing(float x, float y, float xr1, float yr1, float xr2, float yr2);
	void createRingGroup(float x, float y, float r, float wobble);
	void drawRingGroup(float x, float y, float r, float wobble);

	float radius_;
    int time_;
};

	
