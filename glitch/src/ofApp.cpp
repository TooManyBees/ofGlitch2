#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(FPS);
	ofSetVerticalSync(true);
	if (oni_manager.setup(WIDTH, HEIGHT, FPS)) {
		printf("Setup device and streams.\n");
	}
	else {
		printf("Error: %s\n", openni::OpenNI::getExtendedError());
		exit();
		return;
	}
	colorFrame.allocate(WIDTH, HEIGHT, OF_IMAGE_COLOR);
	depthFrame.allocate(WIDTH, HEIGHT, OF_IMAGE_GRAYSCALE);
	depthFrame.setColor(0);

	glitchBuffer.allocate(WIDTH, HEIGHT, OF_IMAGE_GRAYSCALE);
	glitchBuffer.setColor(0);

	userFrame.allocate(WIDTH, HEIGHT, OF_IMAGE_GRAYSCALE);
	userFrame.setColor(0);

	usermask.load("identity.vert", "usermask.frag");
	beglitch.load("identity.vert", "beglitch.frag");
}

unsigned char mysteryDiff(unsigned char a, unsigned char b) {
	unsigned char c = a > b ? a - b : b - a;
	return c > (b / 2) ? c - 1 : c;
}

unsigned char funDiff(int a, int b) {
	int c = a > b ? a - b : b - a;
	c = a - (((c - a) * 255) >> 8);
	return c;
}

unsigned char underflowDiff(unsigned char a, unsigned char b) {
	unsigned int c = a > b ? a - b : b - a;
	return c - 1; // underflow intended
}

//--------------------------------------------------------------
void ofApp::update(){
	oni_manager.getColorFrame(&colorFrame);
	oni_manager.getDepthFrame(&depthFrame);

	ofPixels & pGlitch = glitchBuffer.getPixelsRef();
	const ofPixels pDepth = depthFrame.getPixels();
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		unsigned char dd = mysteryDiff(pGlitch[i], pDepth[i]);
		pGlitch[i] = dd;
	}
	glitchBuffer.update();
	oni_manager.getUserFrame(&userFrame);
}

//--------------------------------------------------------------
void ofApp::draw(){
	userFrame.draw(0, 0);

	usermask.begin();
	usermask.setUniformTexture("usermask", userFrame.getTextureReference(), 1);
	usermask.setUniform1f("threshold", 0.35);
	colorFrame.draw(0, 0);
	usermask.end();

	beglitch.begin();
	beglitch.setUniform1f("threshold", 0.6);
	ofFloatColor color;
	color.setHsb(ofRandom(1.0), 1.0, 1.0);
	beglitch.setUniform3f("color", color.r, color.g, color.b);
	glitchBuffer.draw(0, 0);
	beglitch.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}