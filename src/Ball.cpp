#include "Ball.h"

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

Ball::Ball(int radius)
{
	radius_ = radius;
}

Point Ball::getPosition()
{
	return current_position_;
}

void Ball::setPosition(int x, int y)
{
	current_position_.set(x, y);
}

void Ball::setVelocity(int xVelocity, int yVelocity)
{
	velocity[0] = xVelocity;
	velocity[1] = yVelocity;
}

int Ball::getRadius()
{
	return radius_;
}

void Ball::move()
{
	current_position_.set(current_position_.x + velocity[0], current_position_.y + velocity[1]);
}

void Ball::collision(Paddle paddle, int intersection_point)
{
	double relativeIntersectY = (paddle.getHeight() / 2) - intersection_point;
	double normalizedRelativeIntersectionY = (relativeIntersectY / (paddle.getHeight() / 2));
	double bounceAngle = normalizedRelativeIntersectionY * kmax_bounce_angle_;
	velocity[0] = kball_speed_ * cos(bounceAngle);
	velocity[1] = kball_speed_ * -sin(bounceAngle);
}

void Ball::resize(int w, int h)
{
	float new_x = ((current_position_.x / ofGetWindowWidth()) * w);
	float new_y = ((current_position_.y / ofGetWindowHeight()) * h);
	current_position_.set(new_x, new_y);
}