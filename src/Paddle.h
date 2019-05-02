#pragma once
#include <string>
#include "ofMain.h"

typedef enum {
	NONE = 0,
	UP,
	DOWN,
	RIGHT,
	LEFT
} PongDirection;

class Paddle
{
private:
	ofRectangle paddle_rect_;
	ofColor color_;
	int kpaddle_height_ = 80;; //height of paddle
	int kpaddle_width_ = 10; //width of paddle
	int kspeed = 3; //paddle speed
	ofVec2f current_position_; //current position of paddle
	int score_; //player score
	PongDirection current_direction_; //current direction by keypress
public:
	Paddle(int height, int width); //create a paddle at the origin
	Paddle(int height, int width, int x, int y); //create a paddle at location
	Paddle(int height, int width, int x, int y, ofColor color); //create a paddle at the location with the given color
	ofRectangle getRectangle(); //rectangle getter
	void setRectangle(int x, int y, int width, int height); //rectangle setter
	ofColor getColor(); //get paddle color
	int getHeight(); //height getter
	int getWidth(); //width getter
	int getScore(); //score getter
	void incScore(); //adds to score
	PongDirection getCurrentDirection(); //direction getter
	void setCurrentDirection(PongDirection new_direction); //direction setter
	ofVec2f getPosition(); //position getter
	void setPosition(int x, int y); //position setter
	void move(); //moves paddle based on direction
	void resize(int w, int h); //resizes objects when window is resized
};