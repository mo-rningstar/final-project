#include "ofApp.h"
#include <iostream>

using namespace pong;

//Setup method
void ofApp::setup()
{
	screen_dims_.set(window_width_, window_height_);
	ofSetFrameRate(30);

	ofSetWindowTitle("Pong");
	srand(static_cast<unsigned>(time(0)));

	ball_.setPosition(window_width_ / 2, window_width_ / 2);

	goal.load("beep.mp3");
	goal.setMultiPlay(true);
	goal.setVolume(0.75f);
}

void ofApp::update()
{
	if (keyIsDown[OF_KEY_F4])
	{
		ofToggleFullscreen();
		return;
	}

	if ((keyIsDown['p'] || keyIsDown['P']) && current_state_ != FINISHED)
	{
		// Pause or unpause
		current_state_ = (current_state_ == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
	}
	else if ((keyIsDown['r'] || keyIsDown['R']) && current_state_ == FINISHED)
	{
		reset();
	}
	else if (current_state_ == IN_PROGRESS)
	{
		PongDirection p1_current_direction = player1_.getCurrentDirection();
		PongDirection p2_current_direction = player2_.getCurrentDirection();

		// If current direction has changed to a valid new one, force an immediate update and skip the next frame update
		//if nothing of WASD or the arrow keys are pressed, that player does not move
		if ((keyIsDown['w'] || keyIsDown['W']) && p1_current_direction != UP)
		{
			player1_.setCurrentDirection(UP);
			update();
			should_update_ = false;
		}
		else if ((keyIsDown['a'] || keyIsDown['A']) && p1_current_direction != LEFT)
		{
			player1_.setCurrentDirection(LEFT);
			update();
			should_update_ = false;
		}
		else if ((keyIsDown['s'] || keyIsDown['S']) && p1_current_direction != DOWN)
		{
			player1_.setCurrentDirection(DOWN);
			update();
			should_update_ = false;
		}
		else if ((keyIsDown['d'] || keyIsDown['D']) && p1_current_direction != RIGHT)
		{
			player1_.setCurrentDirection(RIGHT);
			update();
			should_update_ = false;
		}
		else if ((keyIsDown['w'] || keyIsDown['W']) && 
			(keyIsDown['a'] || keyIsDown['A']) &&
			(keyIsDown['s'] || keyIsDown['S']) &&
			(keyIsDown['d'] || keyIsDown['D']))
		{
			player1_.setCurrentDirection(NONE);
			should_update_ = true;
		}
		else
		{
			should_update_ = true;
		}

		if (keyIsDown[OF_KEY_UP] && p2_current_direction != UP)
		{
			player2_.setCurrentDirection(UP);
			update();
			should_update_ = false;
		}
		else if (keyIsDown[OF_KEY_LEFT] && p2_current_direction != LEFT)
		{
			player2_.setCurrentDirection(LEFT);
			update();
			should_update_ = false;
		}
		else if (keyIsDown[OF_KEY_DOWN] && p2_current_direction != DOWN)
		{
			player2_.setCurrentDirection(DOWN);
			update();
			should_update_ = false;
		}
		else if (keyIsDown[OF_KEY_RIGHT] && p2_current_direction != RIGHT)
		{
			player2_.setCurrentDirection(RIGHT);
			update();
			should_update_ = false;
		}
		else if (keyIsDown[OF_KEY_UP] && keyIsDown[OF_KEY_LEFT] && keyIsDown[OF_KEY_DOWN] && keyIsDown[OF_KEY_RIGHT])
		{
			player2_.setCurrentDirection(NONE);
			should_update_ = true;
		}
		else
		{
			should_update_ = true;
		}
	}

	if (should_update_)
	{
		if (current_state_ == IN_PROGRESS)
		{
			player1_.move();
			player2_.move();
			ball_.move();

			collisionCheck(player1_);
			collisionCheck(player2_);

			//goal scored
			if (ball_.getPosition().x < 0) {
				ball_.setPosition(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
				ball_.setVelocity(ofRandom(-5, 5), ofRandom(-5, 5));
				player2_.incScore();
				goal.play();
			}
			else if (ball_.getPosition().x > ofGetWindowWidth()) {
				ball_.setPosition(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
				ball_.setVelocity(ofRandom(-5, 5), ofRandom(-5, 5));
				player1_.incScore();
				goal.play();
			}

			//bounce off bottom and top walls
			if (ball_.getPosition().y < 0) {
				ball_.setPosition(ball_.getPosition().x, 0);
				ball_.setVelocity(0, ofRandom(-5, 5));
			}
			else if (ball_.getPosition().y > ofGetWindowHeight()) {
				ball_.setPosition(ball_.getPosition().x, ofGetWindowHeight());
				ball_.setVelocity(0, ofRandom(-5, 5));
			}

			player1_.setRectangle(player1_.getPosition().x, player1_.getPosition().y, player1_.getWidth(), player1_.getHeight());
			player2_.setRectangle(player2_.getPosition().x, player2_.getPosition().y, player2_.getWidth(), player2_.getHeight());
			ball_.setRectangle(ball_.getPosition().x, ball_.getPosition().y, ball_.getRadius(), ball_.getRadius());
		}
	}

	should_update_ = true;
}

void ofApp::collisionCheck(Paddle player)
{
	ofVec2f travelPath;
	ofVec2f paddleEndPoint;
	travelPath.set(ball_.getPosition().x + ball_.getVelocity().x, ball_.getPosition().y + ball_.getVelocity().y);
	paddleEndPoint.set(player.getPosition().x, player.getPosition().y + player.getHeight());

	//line 164-174 intersection math taken from : https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
	// Line AB represented as a1x + b1y = c1 
	double a1 = travelPath.y - ball_.getPosition().y;
	double b1 = ball_.getPosition().x - travelPath.x;
	double c1 = a1 * (ball_.getPosition().x) + b1 * (ball_.getPosition().y);

	// Line CD represented as a2x + b2y = c2 
	double a2 = paddleEndPoint.y - player.getPosition().y;
	double b2 = player.getPosition().x - paddleEndPoint.x;
	double c2 = a2 * (player.getPosition().x) + b2 * (player.getPosition().y);

	double determinant = a1 * b2 - a2 * b1;

	if (determinant != 0)
	{
		int collisionPoint = ball_.getPosition().y - player.getPosition.y;
		ball_.collision(player.getHeight(), collisionPoint);
	}
}


void ofApp::draw()
{
	ofBackground(0);
	string player1_score = std::to_string(player1_.getScore());
	string player2_score = std::to_string(player2_.getScore());
	
	ofSetColor(player1_.getColor());
	ofDrawBitmapString(player1_score, 0, window_height_);
	ofSetColor(player2_.getColor());
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

void ofApp::keyPressed(int key)
{
	keyIsDown[key] = true;
}

void ofApp::keyReleased(int key) {
	keyIsDown[key] = false;
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