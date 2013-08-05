#include "wovenrings.h"

#define NUM_VERTICES 128
#define CENTER1_X 100
#define CENTER1_Y 600
#define CENTER2_X 500
#define CENTER2_Y 600
#define WOBBLE_PERIOD 50
#define RING_WIDTH 26
#define RING_PERIOD 40
#define COLOR1 0x0088ff
#define COLOR2 0xff0000
#define COLOR3 0x0000ff
#define COLOR4 0xff8800
#define MAX_RADIUS 1300

//--------------------------------------------------------------
void testApp::setup() {
	radius_ = 0;
    time_ = 0;
	ofBackground(20, 20, 20);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update() {
    time_ += 1;

	radius_ += 0.5;
	if (radius_ >= MAX_RADIUS + 2 * RING_PERIOD)
		radius_ -= 2 * RING_PERIOD;
}

void testApp::createRing(float x, float y, float xr1, float yr1, float xr2, float yr2) {
	float angle = 0;
	float delta_angle = TWO_PI / NUM_VERTICES;
	    
	ofNextContour(true);
	for (int i = 0; i < NUM_VERTICES; i++) {
		float vertex_x = x + xr1 * cos(angle);
		float vertex_y = y + yr1 * sin(angle);
		ofVertex(vertex_x, vertex_y);
		angle += delta_angle;
	}

	if (xr2 > 0 || yr2 > 0) {
		ofNextContour(true);
		for (int i = 0; i < NUM_VERTICES; i++) {
			float vertex_x = x + xr2 * cos(angle);
			float vertex_y = y - yr2 * sin(angle);
			ofVertex(vertex_x, vertex_y);
			angle += delta_angle;
		}
	}
}

void testApp::createRingGroup(float x, float y, float r, float wobble) {

	for (int i = r; i > 0; i -= 2 * RING_PERIOD) {
		createRing(x, y, i * wobble, i / wobble, (i - RING_WIDTH) * wobble, (i - RING_WIDTH) / wobble);
	}
}

void testApp::drawRingGroup(float x, float y, float r, float wobble) {
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
	createRingGroup(x, y, r, wobble);
	ofEndShape();
}

//--------------------------------------------------------------
void testApp::draw() {
	ofFill();

    int red1 = 255 * (0.5 + 0.5 * sin(time_ / 507.0));
    int green1 = 255 * (0.5 + 0.5 * (sin(time_ / 619.0)));
    int blue1 = 255 * (0.5 + 0.5 * (sin(time_ / 190.0)));
    
    int red2 = 255 * (0.5 + 0.5 * sin(time_ / 200.0));
    int green2 = 200 * (0.5 + 0.5 * (sin(time_ / 750.0)));
    int blue2 = 200 * (0.5 + 0.5 * (sin(time_ / 317.0)));

    int red3 = 200 * (0.5 + 0.5 * sin(time_ / 190.0));
    int green3 = 200 * (0.5 + 0.5 * (sin(time_ / 210.0)));
    int blue3 = 255 * (0.5 + 0.5 * (sin(time_ / 190.0)));

    int red4 = 200 * (0.5 + 0.5 * sin(time_ / 200.0));
    int green4 = 200 * (0.5 + 0.5 * (sin(time_ / 413.0)));
    int blue4 = 255 * (0.5 + 0.5 * (sin(time_ / 762.0)));
    
    float wobble1 = .2 * sin(time_ / (float)WOBBLE_PERIOD) + 1;
    float wobble2 = 1 / wobble1;
    
 	// center 1 evens
	ofSetColor(red1, green1, blue1);
	drawRingGroup(CENTER1_X, CENTER1_Y, radius_, wobble1);

	// center 2 evens
	ofSetColor(red2, green2, blue2);
	drawRingGroup(CENTER2_X, CENTER2_Y, radius_, wobble2);

	// center 1 odds
	ofSetColor(red3, green3, blue3);
	drawRingGroup(CENTER1_X, CENTER1_Y, radius_ - RING_PERIOD, wobble1);

	// center 2 odds
	ofSetColor(red4, green4, blue4);
	drawRingGroup(CENTER2_X, CENTER2_Y, radius_ - RING_PERIOD, wobble2);

	// intersection of center 1 evens and center 2 odds
	ofSetPolyMode(OF_POLY_WINDING_ABS_GEQ_TWO);
	ofSetColor(red1, green1, blue1);
	ofBeginShape();
	createRingGroup(CENTER1_X, CENTER1_Y, radius_, wobble1);
	createRingGroup(CENTER2_X, CENTER2_Y, radius_ - RING_PERIOD, wobble2);
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
