#pragma once

#include "ofMain.h"
#include "openni.h"
#include "OniManager.h"

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

		ofImage colorFrame;
		ofImage depthFrame;
		ofImage userFrame;
		ofImage glitchBuffer;

		ofShader beglitch;
		ofShader usermask;
};
