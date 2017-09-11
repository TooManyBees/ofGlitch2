#include "ofMain.h"

class Toggle {
public:
	Toggle(const std::string l, const char c, std::string d, ofPoint p, bool startOn = false) :
		hotkey(c), on(startOn), enabled(true), rect(p, 20, 20)
	{
		label.assign(l);
		description.assign(d);
		path.lineTo(rect.getTopLeft());
		path.lineTo(rect.getTopRight());
		path.lineTo(rect.getBottomRight());
		path.lineTo(rect.getBottomLeft());
		path.close();
	}

	void enableThisFrame(bool e);
	bool wasClicked(int mx, int my);
	bool wasPressed(char key);
	bool isOn();
	void click();
	void draw();

private:
	bool on;
	bool enabled;
	std::string label;
	char hotkey;
	std::string description;
	ofRectangle rect;
	ofPath path;
};