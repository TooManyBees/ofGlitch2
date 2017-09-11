#pragma once

#include "ofMain.h"
#include "openni.h"
#include "OniManager.h"
#include "toggle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		int WIDTH = 640;
		int HEIGHT = 480;
		int FPS = 30;

	private:
		OniManager oni_manager;

		ofRectangle canvasSpace;

		ofImage colorFrame;
		ofImage depthFrame;
		ofImage userFrame;
		ofImage glitchBuffer;

		ofShader beglitch;
		ofShader usermask;

		bool needsResize;
		void sizeCanvasSpace();

		bool displayUi = false;
		Toggle toggleBuffer = Toggle("B", 'b', "draw buffer", ofPoint(10, 10));
		Toggle toggleVideo = Toggle("V", 'v', "draw video", ofPoint(10, 35), true);
		Toggle toggleThreshold = Toggle("T", 't', "threshold video", ofPoint(10, 60), true);
		Toggle toggleRainbows = Toggle("R", 'r', "rainbows", ofPoint(10, 85), true);
		vector<Toggle*> ui;
};
