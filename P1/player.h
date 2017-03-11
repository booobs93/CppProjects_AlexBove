#pragma once
#include "input.h"

using namespace Input;

class Player {
public:
	Player(const int & x, const int & y);

	int getX() const;
	int getY() const;
	void setScore(const int &score);
	int getScore() const;
	void updatePosition(Key k);

private:
	int x;
	int y;
	int score;
};