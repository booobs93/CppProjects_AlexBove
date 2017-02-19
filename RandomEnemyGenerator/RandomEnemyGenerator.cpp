#include <iostream>
#include <string>
#include <ctime>

#define NUM_ENEMIES 5

using namespace std;

enum class EnemyType : int { zombie, vampire, ghost, witch };

static string Names[] = { "Gork", "Ness", "Gandalf", "Sauron", "Casper", "Jackson", "Dracula", "Killer", "Mouse", "Golem" };

struct Enemy {
	EnemyType type;
	string name;
	int health;
};

bool operator==(const Enemy &e1, const Enemy &e2) {
	return e1.name == e2.name && e1.type == e2.type;
}

Enemy CreateRandomEnemy() {

	Enemy e;
	// Assign the enemy type
	switch (rand() % 4) {
	case 0:
		e.type = EnemyType::zombie;
		break;
	case 1:
		e.type = EnemyType::vampire;
		break;
	case 2:
		e.type = EnemyType::ghost;
		break;
	case 3:
		e.type = EnemyType::witch;
		break;
	}
	// Initialize health
	e.health = rand() % 600;
	// Initialize name
	e.name = Names[rand() % 10];

	return e;
}

string CreateEnemyTypeString(EnemyType e) {
	string res;
	switch (e) {
	case EnemyType::ghost:
		res = "ghost";
		break;
	case EnemyType::vampire:
		res = "vampire";
		break;
	case EnemyType::witch:
		res = "witch";
		break;
	case EnemyType::zombie:
		res = "zombie";
		break;
	}
	return res;
}

int main() {
	Enemy arr[NUM_ENEMIES];
	Enemy aux;
	bool esRepetit;

	srand(time(NULL));

	cout << "List of enemies:" << endl;

	for (int i = 0;i < NUM_ENEMIES;i++) {
		do {
			aux = CreateRandomEnemy();
			esRepetit = false;
			for (int j = 0; j < i && !esRepetit; j++) {
				esRepetit = arr[j] == aux;
			}
		} while (esRepetit);
		cout << aux.name << " is a " << CreateEnemyTypeString(aux.type) << " whose life is " << aux.health << endl;
	}

	system("PAUSE");
	return 0;
}
