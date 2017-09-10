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

	//ofSetFullscreen(true);
	needsResize = true;
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

	if (needsResize) {
		sizeCanvasSpace();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	// Draw the color frame, optionally masked and thresholded
	usermask.begin();
	usermask.setUniformTexture("usermask", userFrame.getTextureReference(), 1);
	usermask.setUniform1f("threshold", 0.35);
	colorFrame.draw(canvasSpace);
	usermask.end();

	// Draw the glitch!
	beglitch.begin();
	beglitch.setUniform1f("threshold", 0.6);
	ofFloatColor color;
	color.setHsb(ofRandom(1.0), 1.0, 1.0);
	beglitch.setUniform3f("color", color.r, color.g, color.b);
	glitchBuffer.draw(canvasSpace);
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
	needsResize = true;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::sizeCanvasSpace() {
	// Figure out where to draw the image on screen
	float scaleWidthRatio = (float)ofGetWidth() / (float)WIDTH;
	float scaleHeightRatio = (float)ofGetHeight() / (float)HEIGHT;
	float posX, posY, scaleHeight, scaleWidth;
	if (HEIGHT * scaleWidthRatio <= ofGetHeight()) {
		// if scaling to max still fits the height
		scaleWidth = ofGetWidth();
		scaleHeight = HEIGHT * scaleWidthRatio;
		posX = 0;
		posY = (ofGetHeight() - scaleHeight) / 2;
	}
	else {
		scaleWidth = WIDTH * scaleHeightRatio;
		scaleHeight = ofGetHeight();
		posX = (ofGetWidth() - scaleWidth) / 2;
		posY = 0;
	}
	canvasSpace.x = posX;
	canvasSpace.y = posY;
	canvasSpace.width = scaleWidth;
	canvasSpace.height = scaleHeight;
	printf("Drawing at (%.2f, %.2f): %.2f x %.2f\n", canvasSpace.x, canvasSpace.y, canvasSpace.width, canvasSpace.height);
	needsResize = false;
}