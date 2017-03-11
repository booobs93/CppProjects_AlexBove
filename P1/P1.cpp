#include <iostream>
#include "map.h"
#include "player.h"
#include "coinManager.h"

using namespace std;

int main() {
	int difficulty, coinTarget;

	// Prompt the user for the difficulty level;
	cout << "Choose the defficulty level";
	cin >> difficulty;

	// Initialize all the elements
	Map m(difficulty);
	CoinManager(m.getRows(), m.getCols());
	// Set the player at the center of the map
	Player p(m.getRows()/2, m.getCols()/2);

	// Coin amount target [30*x, 30*x*2)
	srand(time(NULL));
	coinTarget = (rand() % difficulty * 30 + 1) + difficulty * 30;
}