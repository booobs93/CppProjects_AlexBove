#include "coinManager.h"
#include <string>
#include <ctime>

CoinManager::CoinManager(const int& rows, const int& cols) {
	mapRows = rows;
	mapCols = cols;
	initCoinData(mapRows, mapCols);
}

void CoinManager::removeCoin(const int &x, const int &y) {
	int pos = -1;
	for (int i = 0; i < coinAmount && pos == -1; i++) {
		if (coinData[i].x == x && coinData[i].y == y) {
			pos = i;
		}
	}
	if (pos >= 0 && pos < coinAmount) {
		for (int i = pos; i < coinAmount - 1; i++) {
			coinData[i] = coinData[i + 1];
		}
		coinAmount--;
		if (coinAmount > 0) {
			coinData = static_cast<tcoin*>(realloc(coinData, coinAmount * sizeof(tcoin)));
		}
		else {
			// User got all the cpins, regenerate the coins again
			initCoinData(mapRows, mapCols);
		}
	}
}

int CoinManager::getCoinData(const tcoin** p) const{
	*p = coinData;
	return coinAmount;
}

void CoinManager::initCoinData(const int & rows, const int & cols) {
	// rand value between  3% and  13 %
	srand(time(NULL));
	coinAmount = (rand() % (rows*cols / 10)) + rows*cols*0.03;
	coinData = static_cast<tcoin*>(malloc(coinAmount * sizeof(tcoin)));
	int rndX, rndY;
	bool repeated;
	// Generate all the coin amount
	for (int i = 0; i < coinAmount; i++) {
		// Generate a coin in a random position
		do {
			repeated = false;
			rndX = rand() % rows;
			rndY = rand() % cols;
			// Check if the new generated position is repeated among the 
			// coins generated before this one
			for (int j = 0; j < i && !repeated; j++) {
				if (coinData[j].x == rndX && coinData[j].y == rndY) {
					repeated = true;
				}
			}
			// Loop again if the generated position is repeated
		} while (repeated);
		coinData[i].x = rndX;
		coinData[i].y = rndY;
	}
}