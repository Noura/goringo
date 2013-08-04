#include "wovenrings.h"

#define NUM_VERTICES 128
#define CENTER1_X 400
#define CENTER1_Y 300
#define CENTER2_X 600
#define CENTER2_Y 300
#define RING_WIDTH 26
#define RING_PERIOD 32
#define COLOR1 0x0088ff
#define COLOR2 0xff0000
#define COLOR3 0x0000ff
#define COLOR4 0xff8800
#define MAX_RADIUS 700

const int testApp::sizes_[NUM_SIZES] = {15, 25};
const int testApp::colors_[NUM_COLORS] = {0xff0000, 0xff8800, 0xeeee00, 0x00ff11, 0x0088ff, 0xee00ee};

//--------------------------------------------------------------
void testApp::setup() {
	radius_ = 0;
	ofBackground(220, 220, 255);
	ofSetFrameRate(40);
}

//--------------------------------------------------------------
void testApp::update() {
	radius_ += 0.7;
	if (radius_ >= MAX_RADIUS + NUM_COLORS * RING_PERIOD)
		radius_ -= NUM_COLORS * RING_PERIOD;
}

void testApp::createRing(float x, float y, float r1, float r2) {
	float angle = 0;
	float delta_angle = TWO_PI / NUM_VERTICES;
	
	ofNextContour(true);
	for (int i = 0; i < NUM_VERTICES; i++) {
		float vertex_x = x + r1 * cos(angle);
		float vertex_y = y + r1 * sin(angle);
		ofVertex(vertex_x, vertex_y);
		angle += delta_angle;
	}

	if (r2 > 0) {
		ofNextContour(true);
		for (int i = 0; i < NUM_VERTICES; i++) {
			float vertex_x = x + r2 * cos(angle);
			float vertex_y = y - r2 * sin(angle);
			ofVertex(vertex_x, vertex_y);
			angle += delta_angle;
		}
	}
}

void testApp::createRingGroup(float x, float y, float r) {
    int s = 0;
    int c = 0;
	for (int i = r; i > 0; i -= 2 * RING_PERIOD) {
        s = (s + 1) % NUM_SIZES;
        c = (c + 1) % NUM_COLORS;
		createRing(x, y, i, i - sizes_[s]);
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
