#include "ofApp.h"
#include <iostream>

using namespace pong;

//Setup method
void ofApp::setup()
{
	screen_dims_.set(window_width_, window_height_);
	ofSetFrameRate(60);

	ofSetWindowTitle("Pong");
	srand(static_cast<unsigned>(time(0)));

	ball_.setPosition(window_width_ / 2, window_width_ / 2);
}

void ofApp::update()
{
	if (should_update_)
	{
		if (current_state_ == IN_PROGRESS)
		{
			player1_.move();
			player2_.move();
			ball_.move();

			//if ball hits player1
			if (ball_.getPosition().x > player1_.getPosition.x &&
				ball_.getPosition().x < player1_.getPosition.x + player1_.getWidth() &&
				ball_.getPosition().y > player1_.getPosition.y &&
				ball_.getPosition().y < player1_.getPosition.y + player1_.getHeight())
			{
				//find collision point for calculation
				int collisionPoint = ball_.getPosition().y - player1_.getPosition.y;
				ball_.collision(player1_, collisionPoint);
			}
			else if (ball_.getPosition().x > player2_.getPosition.x &&
				ball_.getPosition().x < player2_.getPosition.x + player2_.getWidth() &&
				ball_.getPosition().y > player2_.getPosition.y &&
				ball_.getPosition().y < player2_.getPosition.y + player2_.getHeight())
			{
				//find collision point for calculation
				int collisionPoint = ball_.getPosition().y - player2_.getPosition.y;
				ball_.collision(player2_, collisionPoint);
			}

			//goal scored
			if (ball_.getPosition().x < 0) {
				ball_.setPosition(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
				player2_.incScore();
			}
			else if (ball_.getPosition().x > ofGetWindowWidth()) {
				ball_.setPosition(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
				player1_.incScore();
			}

			//bounce off bottom and top walls
			if (ball_.getPosition().y < 0) {
				ball_.setPosition(ball_.getPosition().x, 0);
				ball_.setVelocity(0, 1);
			}
			else if (ball_.getPosition().y > ofGetWindowHeight()) {
				ball_.setPosition(ball_.getPosition().x, ofGetWindowHeight());
				ball_.setVelocity(0, -1);
			}

			player1_.setRectangle(player1_.getPosition().x, player1_.getPosition().y, player1_.getWidth(), player1_.getHeight());
			player2_.setRectangle(player2_.getPosition().x, player2_.getPosition().y, player2_.getWidth(), player2_.getHeight());
			ball_.setRectangle(ball_.getPosition().x, ball_.getPosition().y, ball_.getRadius(), ball_.getRadius());
		}
	}

	should_update_ = true;
}


void ofApp::draw()
{
	ofBackground(0);
	string player1_score = std::to_string(player1_.getScore());
	string player2_score = std::to_string(player2_.getScore());
	ofSetColor(0, 0, 0);

	ofDrawBitmapString(player1_score, 0, window_height_);
	ofDrawBitmapString(player1_score, window_width_, window_height_);

	if (current_state_ == PAUSED)
	{
		drawGamePaused();
	}
	else if (current_state_ == FINISHED)
	{
		drawGameOver();
	}

	drawPaddles();
	drawBall();
}

/*
Function that handles actions based on user key presses
1. if key == F4, toggle fullscreen
2. if key == p and game is not over, toggle pause
3. if game is in progress handle WASD action and arrow key action
4. if key == space and game is over reset it
*/
void ofApp::keyPressed(int key)
{
	if (key == OF_KEY_F4)
	{
		ofToggleFullscreen();
		return;
	}

	int upper_key = toupper(key); // Standardize on upper case

	if (upper_key == 'P' && current_state_ != FINISHED)
	{
		// Pause or unpause
		current_state_ = (current_state_ == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
	}
	else if (current_state_ == IN_PROGRESS)
	{
		PongDirection p1_current_direction = player1_.getCurrentDirection();
		PongDirection p2_current_direction = player2_.getCurrentDirection();

		// If current direction has changed to a valid new one, force an immediate update and skip the next frame update
		//if nothing of WASD or the arrow keys are pressed, that player does not move
		if (upper_key == 'W' && p1_current_direction != UP)
		{
			player1_.setCurrentDirection(UP);
			update();
			should_update_ = false;
		}
		else if (upper_key == 'A' && p1_current_direction != LEFT)
		{
			player1_.setCurrentDirection(LEFT);
			update();
			should_update_ = false;
		}
		else if (upper_key == 'S' && p1_current_direction != DOWN)
		{
			player1_.setCurrentDirection(DOWN);
			update();
			should_update_ = false;
		}
		else if (upper_key == 'D' && p1_current_direction != RIGHT)
		{
			player1_.setCurrentDirection(RIGHT);
			update();
			should_update_ = false;
		}
		else if (upper_key != 'W' && upper_key != 'A' && upper_key != 'S' && upper_key != 'D')
		{
			player1_.setCurrentDirection(NONE);
			should_update_ = true;
		}
		else
		{
			should_update_ = true;
		}

		if (upper_key == OF_KEY_UP && p2_current_direction != UP)
		{
			player2_.setCurrentDirection(UP);
			update();
			should_update_ = false;
		}
		else if (upper_key == OF_KEY_LEFT && p2_current_direction != LEFT)
		{
			player2_.setCurrentDirection(LEFT);
			update();
			should_update_ = false;
		}
		else if (upper_key == OF_KEY_DOWN && p2_current_direction != DOWN)
		{
			player2_.setCurrentDirection(DOWN);
			update();
			should_update_ = false;
		}
		else if (upper_key == OF_KEY_RIGHT && p2_current_direction != RIGHT)
		{
			player2_.setCurrentDirection(RIGHT);
			update();
			should_update_ = false;
		}
		else if (upper_key != OF_KEY_UP && upper_key != OF_KEY_LEFT && upper_key != OF_KEY_DOWN && upper_key != OF_KEY_RIGHT)
		{
			player2_.setCurrentDirection(NONE);
			should_update_ = true;
		}
		else
		{
			should_update_ = true;
		}
	}
	else if (upper_key == 'R' && current_state_ == FINISHED)
	{
		reset();
	}
}

void ofApp::reset()
{
	current_state_ = IN_PROGRESS;
}

void ofApp::windowResized(int w, int h)
{
	float new_x = (screen_dims_.x * w);
	float new_y = (screen_dims_.y * h);

	screen_dims_.set(new_x, new_y);

	ball_.resize(w, h);
	player1_.resize(w, h);
	player2_.resize(w, h);
}

void ofApp::drawPaddles()
{
	ofSetColor(player1_.getColor());
	ofDrawRectangle(player1_.getRectangle());

	ofSetColor(player2_.getColor());
	ofDrawRectangle(player2_.getRectangle());
}

void ofApp::drawBall()
{
	ofSetColor(ball_.getColor());
	ofDrawRectangle(ball_.getRectangle());
}

bool ofApp::isGameOver()
{
	if (player1_.getScore() == 7 || player2_.getScore() == 7)
	{
		return true;
	}

	return false;
}

void ofApp::drawGameOver()
{
	string score_line = "Player 1: " + std::to_string(player1_.getScore()) + "\n \n Player 2: " + std::to_string(player2_.getScore());
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(score_line, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void ofApp::drawGamePaused()
{
	string pause_message = "P to Unpause!";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}