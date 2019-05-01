#pragma once
#include <ctime>
#include <cstdlib>
#include <utility>

#include "ofMain.h"
#include "ofxGui.h"
#include "Ball.h"

namespace pong {

	//Enum to represent the current state of the game
	enum GameState {
		IN_PROGRESS = 0,
		PAUSED,
		FINISHED
	};

	class ofApp : public ofBaseApp {
	private:
		int window_width_ = ofGetWindowWidth();
		int window_height_ = ofGetWindowHeight();
		int kpaddle_width_ = 10;
		int kpaddle_height_ = 80;
		GameState current_state_ = IN_PROGRESS;
		Paddle player1_ = Paddle(kpaddle_height_, kpaddle_width_, 0, window_height_ / 2, ofColor(0, 0, ofRandom(128, 255)));
		Paddle player2_ = Paddle(kpaddle_height_, kpaddle_width_, window_width_, window_height_ / 2, ofColor(ofRandom(128, 255), 0, 0));
		Ball ball_ = Ball(2 * kpaddle_width_);

		ofxPanel gui;

		ofVec2f screen_dims_; //current screen dimensions

		bool should_update_ = true;

		void drawBall(); //draw ball
		void drawPaddles(); //draw player paddles
		void drawGameOver(); //display game over screen
		bool isGameOver(); //check scores for game over status
		void drawGamePaused(); //display pause screen

		void reset(); //reset finished game for a new game

	public:
		void setup(); //set up the app

		void update(); //updates positions of the ball and paddles
		void draw(); //draws the screen depending on the current game state

		void keyPressed(int key); //checks for both players' keypresses
		void windowResized(int w, int h); //resizing window

		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void gotMessage(ofMessage msg);
		void dragEvent(ofDragInfo dragInfo);
	};
}