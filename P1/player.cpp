#include "player.h"

Player::Player(const int & xPos, const int & yPos) {
	x = xPos;
	y = yPos;
	score = 0;
}

int Player::getX() const {
	return x;
}

int Player::getY() const {
	return y;
}

void Player::setScore(const int &s) {
	score = s;
}

int Player::getScore() const {
	return score;
}

void Player::updatePosition(Key k) {
	switch (k) {
	case Key::W:
		x--;
		break;
	case Key::A:
		y--;
		break;
	case Key::S:
		x++;
		break;
	case Key::D:
		y++;
		break;
	}
}