#pragma once

#include "ofMain.h"
#include "openni.h"
#include "OniManager.h"
#include "toggle.h"

class ofApp : public ofBaseApp{

	public:
		void parseArgs(int argc, char* argv[]);
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
		bool mirror = true;
		bool fullscreen = false;
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
		ofTrueTypeFont uiFont;
		ofTrueTypeFont statsFont;
		char statsString[30];
		float videoThreshold;
		float rainbowThreshold;
		Toggle* toggleBuffer;
		Toggle* toggleVideo;
		Toggle* toggleThreshold;
		Toggle* toggleRainbows;
		vector<Toggle*> ui;

		void updateUi();
		void drawUi();
};
