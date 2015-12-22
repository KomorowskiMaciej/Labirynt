#ifndef Player_h
#define Player_h

#include "Vector2.h"
#include "Mapa.h"

using namespace std;

class Player {
public:
	int PlayerX, PlayerY, direction;

	Player(int x, int y) {
		this->PlayerX = x;
		this->PlayerY = y;
		direction = 0;
	};

	void doAction(int input, Mapa *mapa);
	int getDirection();
	Vector2 getPosition();
	Vector2 getCordInFrontOfCharacter();

private:
	void turn(int dir);
	void move(int move, Vector2 mapSize, Mapa *mapa);
	
	Vector2 getCordBehindCharacter();
};
#endif