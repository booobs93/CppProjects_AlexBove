
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
	int life;
	int distanceToPlayer;
	float speed;
	float damage;

	Zombie() {
		speed = ((float)rand() / (RAND_MAX)) * 20;
		damage = ((float)rand() / (RAND_MAX)) * 20;
		life = 100;
		distanceToPlayer = rand() % 200 + 20;
	}

	Zombie(int t_distanceToPlayer, float t_speed, float t_damage, int t_life) {
		distanceToPlayer = t_distanceToPlayer;
		speed = t_speed;
		damage = t_damage;
		life = t_life;
	}

	void attack(Player &p) {

		if (distanceToPlayer <= 0) {
			if (p.life - damage > 0) {
				p.life -= damage;
			}
			else {
				p.life = 0;
			}
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
	int damage = static_cast<int>(arma);
	if(z.life - damage > 0){
		z.life -= damage;
	}
	else {
		z.life = 0;
	}
}
//6


int main() {

	srand(time(nullptr));
	Player player = Player();
	Zombie zombies[10];
	bool zombiesAreAlive = true;
	int deadZombies = 0;

	while (player.isAlive() && zombiesAreAlive) {
		deadZombies = 0;
		cout << "Player" << endl << "life: " << player.life << ", " << player.arma << ", precision: " << player.precision << endl;
		for (int i = 0;i < 10;i++) {
			if (zombies[i].isAlive()) {
				player.attack(zombies[i]);
			}
			if (zombies[i].isAlive()) {
				zombies[i].attack(player);
			}
			else {
				deadZombies++;
			}
			if (deadZombies == 10) {
				zombiesAreAlive = false;
			}
			cout << "zombie " << i << ": life ---> " << zombies[i].life << "." << endl;
		}
		cout << "----------------------------------------------------" << endl;
	}
	if (player.isAlive()) {
		cout << "GAME OVER: Player killed all the zombies" << endl;
	}
	else {
		cout << "GAME OVER: Zombies ate the player's brain" << endl;
	}
	system("PAUSE");
	return 0;
}