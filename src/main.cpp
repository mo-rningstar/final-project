#include "ofMain.h"
#include "ofApp.h"

using namespace pong;

#define DISPLAY_MODE OF_WINDOW 

int main() {
	ofSetupOpenGL(1024, 768, DISPLAY_MODE);

	ofRunApp(new ofApp());
}