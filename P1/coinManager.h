#pragma once

typedef struct coin {
	int x;
	int y;
} tcoin;

class CoinManager{
public:
	CoinManager(const int& rows, const int& cols);
	void removeCoin(const int &x, const int &y);
	int getCoinData(const tcoin* p);

private:

	void initCoinData(const int & rows, const int & cols);

	tcoin* coinData;
	int coinAmount;
	int mapRows, mapCols;
};