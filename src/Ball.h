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
	Point current_position_; //current position of ball
	std::vector<double> velocity = { ofRandom(-5, 5), ofRandom(-5, 5) };
	int kmax_bounce_angle_ = 90;
	int kball_speed_ = 10;
public:
	ofRectangle getRectangle(); //rectangle getter
	void setRectangle(int x, int y, int width, int height); //rectangle setters
	Ball(int radius); //create ball
	ofColor getColor(); //get ball color
	Point getPosition(); //position getter
	void setPosition(int x, int y); //position setter
	void setVelocity(int xVelocity, int yVelocity); //velocity setting for collisions and stuff
	int getRadius(); //size getter
	void move(); //updates position of ball
	void collision(Paddle paddle, int intersection_point); //moves ball based on where it hits paddle
	void resize(int w, int h); //resizes objects when window is resized
};