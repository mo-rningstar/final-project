#include "Ball.h"

Ball::Ball(int radius)
{
	radius_ = radius;
	velocity_.set(ofRandom(-5, 5), ofRandom(-5, 5));
}

ofRectangle Ball::getRectangle()
{
	return ball_square_;
}

void Ball::setRectangle(int x, int y, int width, int height)
{
	ball_square_.set(x, y, width, height);
}

ofColor Ball::getColor()
{
	return color_;
}

ofVec2f Ball::getPosition()
{
	return current_position_;
}

void Ball::setPosition(int x, int y)
{
	current_position_.set(x, y);
}

ofVec2f Ball::getVelocity()
{
	return velocity_;
}

void Ball::setVelocity(int xVelocity, int yVelocity)
{
	velocity_.set(xVelocity, yVelocity);
}

int Ball::getRadius()
{
	return radius_;
}

void Ball::move()
{
	current_position_.set(current_position_.x + velocity_.x, current_position_.y + velocity_.y);
}

void Ball::collision(int length, int intersection_point)
{
	double relativeIntersectY = (length / 2) - intersection_point;
	double normalizedRelativeIntersectionY = (relativeIntersectY / (length / 2));
	double bounceAngle = normalizedRelativeIntersectionY * kmax_bounce_angle_;
	velocity_.set(kball_speed_ * cos(bounceAngle), kball_speed_ * -sin(bounceAngle));
}

void Ball::resize(int w, int h)
{
	float new_x = ((current_position_.x / ofGetWindowWidth()) * w);
	float new_y = ((current_position_.y / ofGetWindowHeight()) * h);
	current_position_.set(new_x, new_y);
}