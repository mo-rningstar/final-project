#pragma once
#include <vector>
#include "Paddle.h"
#include <math.h>
#include "ofMain.h"

class Ball
{
private:
	ofRectangle ball_square_;
	ofColor color_ = ofColor(255, 255, 255);
	int radius_; //radius of the ball
	ofVec2f current_position_; //current position of ball
	ofVec2f velocity_;
	int kmax_bounce_angle_ = 90;
	int kball_speed_ = 10;
public:
	Ball(int radius); //create ball
	ofRectangle getRectangle(); //rectangle getter
	void setRectangle(int x, int y, int width, int height); //rectangle setters
	ofColor getColor(); //get ball color
	ofVec2f getPosition(); //position getter
	void setPosition(int x, int y); //position setter
	ofVec2f getVelocity();
	void setVelocity(int xVelocity, int yVelocity); //velocity setting for collisions and stuff
	int getRadius(); //size getter
	void move(); //updates position of ball
	void collision(int length, int intersection_point); //moves ball based on where it hits paddle
	void resize(int w, int h); //resizes objects when window is resized
};