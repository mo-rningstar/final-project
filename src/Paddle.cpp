#include "Paddle.h"

Paddle::Paddle(int height, int width)
{
	kpaddle_height_ = height;
	kpaddle_width_ = width;
	score_ = 0;
	current_position_.set(0, 0);
}

Paddle::Paddle(int height, int width, int x, int y)
{
	kpaddle_height_ = height;
	kpaddle_width_ = width;
	score_ = 0;
	current_position_.set(x, y);
}

Paddle::Paddle(int height, int width, int x, int y, ofColor color)
{
	kpaddle_height_ = height;
	kpaddle_width_ = width;
	score_ = 0;
	current_position_.set(x, y);
	color_ = color;
}

ofRectangle Paddle::getRectangle()
{
	return paddle_rect_;
}

void Paddle::setRectangle(int x, int y, int width, int height)
{
	paddle_rect_.set(x, y, width, height);
}

ofColor Paddle::getColor()
{
	return color_;
}

int Paddle::getHeight()
{
	return kpaddle_height_;
}

int Paddle::getWidth()
{
	return kpaddle_width_;
}

int Paddle::getScore()
{
	return score_;
}

void Paddle::incScore()
{
	score_++;
}

PongDirection Paddle::getCurrentDirection()
{
	return current_direction_;
}

void Paddle::setCurrentDirection(PongDirection new_direction)
{
	current_direction_ = new_direction;
}

Point Paddle::getPosition()
{
	return current_position_;
}

void Paddle::setPosition(int x, int y)
{
	current_position_.x = x;
	current_position_.y = y;
}

void Paddle::move()
{
	switch (current_direction_) {
	case UP:
		current_position_.set(current_position_.x, current_position_.y - kspeed);
		break;
	case DOWN:
		current_position_.set(current_position_.x, current_position_.y + kspeed);
		break;
	case LEFT:
		current_position_.set(current_position_.x - kspeed, current_position_.y);
		break;
	case RIGHT:
		current_position_.set(current_position_.x + kspeed, current_position_.y);
		break;
	case NONE:
		break;
	}
}

void Paddle::resize(int w, int h)
{
	float new_x = ((current_position_.x / ofGetWindowWidth()) * w);
	float new_y = ((current_position_.y / ofGetWindowHeight()) * h);
	current_position_.set(new_x, new_y);
}