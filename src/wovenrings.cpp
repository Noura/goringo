#include "wovenrings.h"

#define NUM_VERTICES 128
#define CENTER1_X 500
#define CENTER1_Y 100
#define CENTER2_X 500
#define CENTER2_Y 340
#define WOBBLE_PERIOD1 1000
#define WOBBLE_PERIOD2 500
#define RING_WIDTH 26
#define RING_PERIOD 32
#define COLOR1 0x0088ff
#define COLOR2 0xff0000
#define COLOR3 0x0000ff
#define COLOR4 0xff8800
#define MAX_RADIUS 700

//--------------------------------------------------------------
void testApp::setup() {
	radius_ = 0;
    time_ = 0;
	ofBackground(220, 220, 255);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update() {
    time_ += 1;

	radius_ += 0.5;
	if (radius_ >= MAX_RADIUS + 2 * RING_PERIOD)
		radius_ -= 2 * RING_PERIOD;
}

void testApp::createRing(float x, float y, float r1, float r2) {
	float angle = 0;
	float delta_angle = TWO_PI / NUM_VERTICES;
	
    float wobble = .5 * sin(time_ / (float)WOBBLE_PERIOD1) + 1;
    
	ofNextContour(true);
	for (int i = 0; i < NUM_VERTICES; i++) {
		float vertex_x = x + r1 * cos(angle) * wobble;
		float vertex_y = y + r1 * sin(angle) / wobble;
		ofVertex(vertex_x, vertex_y);
		angle += delta_angle;
	}

	if (r2 > 0) {
		ofNextContour(true);
		for (int i = 0; i < NUM_VERTICES; i++) {
			float vertex_x = x + r2 * cos(angle) * wobble;
			float vertex_y = y - r2 * sin(angle) / wobble;
			ofVertex(vertex_x, vertex_y);
			angle += delta_angle;
		}
	}
}

void testApp::createRingGroup(float x, float y, float r) {
	for (int i = r; i > 0; i -= 2 * RING_PERIOD) {
		createRing(x, y, i, i - RING_WIDTH);
	}
}

void testApp::drawRingGroup(float x, float y, float r) {
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
	createRingGroup(x, y, r);
	ofEndShape();
}

//--------------------------------------------------------------
void testApp::draw() {
	ofFill();

	// center 1 evens
	ofSetHexColor(COLOR1);
	drawRingGroup(CENTER1_X, CENTER1_Y, radius_);

	// center 2 evens
	ofSetHexColor(COLOR2);
	drawRingGroup(CENTER2_X, CENTER2_Y, radius_);

	// center 1 odds
	ofSetHexColor(COLOR3);
	drawRingGroup(CENTER1_X, CENTER1_Y, radius_ - RING_PERIOD);

	// center 2 odds
	ofSetHexColor(COLOR4);
	drawRingGroup(CENTER2_X, CENTER2_Y, radius_ - RING_PERIOD);

	// intersection of center 1 evens and center 2 odds
	ofSetPolyMode(OF_POLY_WINDING_ABS_GEQ_TWO);
	ofSetHexColor(COLOR1);
	ofBeginShape();
	createRingGroup(CENTER1_X, CENTER1_Y, radius_);
	createRingGroup(CENTER2_X, CENTER2_Y, radius_ - RING_PERIOD);
	ofEndShape();



	/*

	 //------(i)--------------------------------------
	 //
	 // 		CSG / ofNextContour
	 //
	 // 		with different winding rules, you can even use ofNextContour to
	 // 		perform constructive solid geometry
	 //
	 // 		be careful, the clockwiseness or counter clockwisenss of your multiple
	 // 		contours matters with these winding rules.
	 //
	 // 		for csg ideas, see : http://glprogramming.com/red/chapter11.html
	 //
	 // 		info about the winding rules is here:
	 //		http://glprogramming.com/red/images/Image128.gif
	 //
	 ofNoFill();
	 float radius = 0;
	 float radiusAdder 	= 0.5f;

	 glPushMatrix();

	 ofSetPolyMode(OF_POLY_WINDING_ODD);

	 ofBeginShape();

	 ofVertex(300,500);
	 ofVertex(380,550);
	 ofVertex(300,600);

	 ofNextContour(true);

	 for (int i = 0; i < 20; i++){
	 float anglef = ((float)i / 19.0f) * TWO_PI;
	 float x = 340 + 30 * cos(anglef);
	 float y = 550 + 30 * sin(anglef);
	 ofVertex(x,y);
	 radius 	+= radiusAdder;
	 }


	 ofEndShape(true);

	 glTranslatef(100,0,0);

	 ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	 ofBeginShape();

	 ofVertex(300,500);
	 ofVertex(380,550);
	 ofVertex(300,600);

	 ofNextContour(true);

	 for (int i = 0; i < 20; i++){
	 float anglef = ((float)i / 19.0f) * TWO_PI;
	 float x = 340 + 30 * cos(anglef);
	 float y = 550 + 30 * sin(anglef);
	 ofVertex(x,y);
	 radius 	+= radiusAdder;
	 }

	 ofEndShape(true);

	 glTranslatef(100,0,0);
	 ofSetPolyMode(OF_POLY_WINDING_ABS_GEQ_TWO);
	 ofBeginShape();
	 ofVertex(300,500);
	 ofVertex(380,550);
	 ofVertex(300,600);
	 ofNextContour(true);

	 for (int i = 0; i < 20; i++){
	 float anglef = ((float)i / 19.0f) * TWO_PI;
	 float x = 340 + 30 * cos(anglef);
	 float y = 550 + 30 * sin(anglef);
	 ofVertex(x,y);
	 radius 	+= radiusAdder;
	 }
	 
	 
	 ofEndShape(true);
	 */
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	
}

//------------- -------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) { 
}
