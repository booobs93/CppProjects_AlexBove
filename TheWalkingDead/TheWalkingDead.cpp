
//1

#include <iostream>
#include<string>
#include<ctime>

using namespace std;

//2

enum class Weapon : int { FISTS, GUN, SHOTGUN, REVOLVER, SNIPER, MACHINE_GUN, MAX };
Weapon arma;

//3

ostream& operator<<(ostream& os, const Weapon &arma) {

	switch (arma) {
	case Weapon::FISTS:
		os << "fists";
		break;
	case Weapon::GUN:
		os << "gun";
		break;
	case Weapon::SHOTGUN:
		os << "shotgun";
		break;
	case Weapon::REVOLVER:
		os << "revolver";
		break;
	case Weapon::SNIPER:
		os << "sniper";
		break;
	case Weapon::MACHINE_GUN:
		os << "machine gun";
		break;
	}
	return os;
}

//4,5
//a

//forward declaration
class Zombie;

class Player {
public:
	Weapon arma;
	float precision;
	int life;

	Player() {
		int index = rand() % 6;
		arma = Weapon(index);

		precision = ((float)rand() / (RAND_MAX));
		life = 100;
	}

	Player(Weapon t_weapon, float t_precision, int t_life) {
		arma = t_weapon;
		precision = t_precision;
		life = t_life;
	}

	void attack(Zombie &z);

	bool isAlive() {
		return life > 0;
	}
};

class Zombie {
public:
	int life = 100;

	int distanceToPlayer;
	int distToPlayer_min = 20;
	int distToPlayer_max = 200;

	float speed;
	float damage;

	Zombie() {
		float  speed = ((double)rand() / (RAND_MAX)) * 20;
		float  damage = ((double)rand() / (RAND_MAX)) * 20;
		life = 100;
	}

	Zombie(int t_distanceToPlayer, float t_speed, float t_damage, int t_life) {
		distanceToPlayer = t_distanceToPlayer;
		speed = t_speed;
		damage = t_damage;
		life = t_life;
	}

	void attack(Player &p) {

		if (distanceToPlayer <= 0) {
			p.life = p.life - damage;
		}
		else {
			distanceToPlayer--;
		}
	}

	bool isAlive() {
		return life > 0;
	}

};

void Player::attack(Zombie &z) {
	z.life = z.life - static_cast<int>(arma);
}
//6


int main() {

	srand(time(nullptr));
	Player player = Player();
	Zombie zombies[10];
	bool zombiesAreAlive = true;
	int deadZombies = 0;

	for (int i = 0;i < 10;i++) {
		zombies[i] = Zombie();
	}

	while (player.isAlive() && zombiesAreAlive) {
		for (int i = 0;i < 10;i++) {
			if (!zombies[i].isAlive()) {
				deadZombies++;
			}
			if (deadZombies == 10) {
				zombiesAreAlive = false;
			}
			else {
				deadZombies = 0;
			}
			cout << "zombie " << i << ": life --->" << zombies[i].life << " .";
		}
	}




	return 0;
}