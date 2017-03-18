#include <iostream>
#include <ctime>
#include "map.h"
#include "player.h"
#include "coinManager.h"
#include "P1.h"
#include <Windows.h>

using namespace std;

extern ostream& operator<<(ostream& os, const Map &map);

void updateMap(HANDLE hConsole, Map map, const Player &p, const CoinManager & coin_manager, int coin_target) {
	system("cls");
	const tcoin *coin_data;
	int coin_amount;
	// Get the current coin data and set the coins inside the map1
	coin_amount = coin_manager.getCoinData(&coin_data);
	for (int i = 0; i < coin_amount; ++i) {
		map.setCell(coin_data[i].x, coin_data[i].y, '$');
	}

	// Print the user
	map.setCell(p.getX(), p.getY(), '@');
	// Print the map
	cout << map << endl;
	// Print the score
	SetConsoleTextAttribute(hConsole, 13);
	cout << "Score: ";
	SetConsoleTextAttribute(hConsole, 11); 
	cout << p.getScore() << " / " << coin_target << endl;
	SetConsoleTextAttribute(hConsole, 15);
}

bool checkNextPosition(const Map& map, const Player &p, const Key& k) {
	switch (k) {
	case Key::A:
		return p.getY() > 0;
	case Key::W:
		return p.getX() > 0;
	case Key::S:
		return p.getX() < map.getRows() - 1;
	case Key::D:
		return p.getY() < map.getCols() - 1;
	}
}

int printMenu(HANDLE hConsole) {
	int difficulty;
	// Draw menu title
	SetConsoleTextAttribute(hConsole, 14); 
	cout << "////////////////////////////////////////////////" << endl;
	cout << "\t\tCOIN RACE" << endl;
	cout << "////////////////////////////////////////////////" << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << endl;
	cout << "Controls: Use WASD to move the player" << endl << endl;
	cout << "Choose a difficulty:" << endl;
	cout << "1 - EASY" << endl;
	cout << "2 - MEDIUM" << endl;
	cout << "3 - HARD" << endl;
	cin >> difficulty;
	return difficulty;
}

int main() {
	int difficulty, coinTarget;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Prompt the user for the difficulty level
	difficulty = printMenu(hConsole);
	
	// Initialize all the elements
	Map map(difficulty);
	CoinManager coin_manager(map.getRows(), map.getCols());
	// Set the player at the center of the map
	Player p(map.getRows()/2, map.getCols()/2);

	// Coin amount target [30*x, 30*x*2)
	srand(time(NULL));
	coinTarget = (rand() % difficulty * 30 + 1) + difficulty * 30;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Objective: You have to pick up ";
	SetConsoleTextAttribute(hConsole, 11);
	cout << coinTarget;
	SetConsoleTextAttribute(hConsole, 15);
	cout << " coins" << endl;
	_getch();
	const tcoin *coin_data;
	int coin_amount;

	updateMap(hConsole, map, p, coin_manager, coinTarget);

	clock_t start_time = clock();

	while (p.getScore() < coinTarget) {
		// Input
		Key k = getKey();
		if (k == Key::ESC) {
			return 0;
		}
		else if (k == Key::NONE) {
			continue;
		}
		else {
			map.setCell(p.getX(), p.getY(), '.');

			if (checkNextPosition(map, p, k)) {
				p.updatePosition(k);

				// Calculations
				coin_amount = coin_manager.getCoinData(&coin_data);
				for (int i = 0; i < coin_amount; ++i) {
					if (coin_data[i].x == p.getX() && coin_data[i].y == p.getY()) {
						p.setScore(p.getScore() + 1);
						coin_manager.removeCoin(p.getX(), p.getY());
						break;
					}
				}
				// Print
				updateMap(hConsole, map, p, coin_manager, coinTarget);
			}
		}
	}
	clock_t end_time = clock();
	cout << endl << "You've picked up ";
	SetConsoleTextAttribute(hConsole, 11);
	cout << coinTarget;
	SetConsoleTextAttribute(hConsole, 15);
	cout << " coins in ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << (end_time - start_time) / 1000;
	SetConsoleTextAttribute(hConsole, 15);
	cout << " seconds" << endl;
	_getch();
}