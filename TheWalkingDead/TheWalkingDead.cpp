
//1

#include <iostream>
#include<string>
#include<ctime>

using namespace std;

//2

enum class Weapon : int { FISTS, GUN, SHOTGUN, REVOLVER, SNIPER, MACHINE_GUN, MAX };
Weapon arma;

//3

ostream& operator<<(ostream&os, const Weapon &arma) {

	switch (arma) {
	case 0:
		Weapon{ 0 } = "fists";
		break;
	case 1:
		Weapon{ 1 } = "gun";
		break;
	case 2:
		Weapon{ 2 } = "shotgun";
		break;
	case 3:
		Weapon{ 3 } = "revolver";
		break;
	case 4:
		Weapon{ 4 } = "sniper";
		break;
	case 5:
		Weapon{ 5 } = "machine gun";
		break;
	}
}

//4,5
//a

//forward declaration
class Zombie;


class Player {
public:
	Weapon arma;
	float precision;
	float precision_min = 0.f;
	float precision_max = 1.f;
	int life;

	Player() {
		int index = rand() % 6;
		arma = Weapon(index);

		precision = rand() % precision_max;
		precision += precision_min;
		life = 100;
	}

	Player(Weapon t_weapon, float t_precision, int t_life) {
		arma = t_weapon;
		precision = t_precision;
		life = t_life;
	}

	void attack(Zombie &z) {
		z.life = z.life - arma;
	}

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
	float speed_min = 0.f;
	float speed_max = 20.f;

	float damage;
	float damage_min = 0.f;
	float damage_max = 20.f;

	Zombie() {
		float speed = speed_min + (rand() % speed_max + 1);
		float damage = damage_min + (rand() % damage_max + 1);


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