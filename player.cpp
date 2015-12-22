#include "Vector2.h"
#include "Player.h"
#include "Mapa.h"

using namespace std;

void Player::doAction(int input, Mapa *mapa) {
	if (input == (char)72)
		this->move(1, *mapa->mapSize, mapa);
	else if (input == (char)80)
		this->move(-1, *mapa->mapSize, mapa);
	if (input == (char)75)
		this->turn(-1);
	else if (input == (char)77)
		this->turn(1);
}

void Player::turn(int dir) {
	if (dir < 0)
		dir = 2 - dir;
	direction = (direction + dir) % 4;
}

void Player::move(int move_, Vector2 mapSize, Mapa *mapa) {

	if (
		move_ == 1
		&& getCordInFrontOfCharacter().y - 1 >= 0
		&& getCordInFrontOfCharacter().x - 1 >= 0
		&& getCordInFrontOfCharacter().y - 1 < mapSize.y
		&& getCordInFrontOfCharacter().x - 1 < mapSize.x
		&& (mapa->_Mapa[getCordInFrontOfCharacter().y - 1][getCordInFrontOfCharacter().x - 1] == '0' || mapa->_Mapa[getCordInFrontOfCharacter().y - 1][getCordInFrontOfCharacter().x - 1] == '7')) {

		if (this->direction == 0)
			this->PlayerY -= move_;
		else if (this->direction == 2)
			this->PlayerY += move_;
		else if (this->direction == 1)
			this->PlayerX += move_;
		else if (this->direction == 3)
			this->PlayerX -= move_;

		if (this->PlayerY < 1)
			this->PlayerY = 1;
		if (this->PlayerX < 1)
			this->PlayerX = 1;
		if (this->PlayerY > mapSize.y)
			this->PlayerY = mapSize.y;
		if (this->PlayerX > mapSize.x)
			this->PlayerX = mapSize.x;
	}
	else if (	
		move_ == -1
		&& this->getCordBehindCharacter().y - 1 >= 0
		&& this->getCordBehindCharacter().x - 1 >= 0
		&& this->getCordBehindCharacter().y - 1 < mapSize.y
		&& this->getCordBehindCharacter().x - 1 < mapSize.x
		&& (mapa->_Mapa[this->getCordBehindCharacter().y - 1][this->getCordBehindCharacter().x - 1] == '0' || mapa->_Mapa[this->getCordBehindCharacter().y - 1][this->getCordBehindCharacter().x - 1] == '7')) {

		if (this->direction == 0)
			this->PlayerY -= move_;
		else if (this->direction == 2)
			this->PlayerY += move_;
		else if (this->direction == 1)
			this->PlayerX += move_;
		else if (this->direction == 3)
			this->PlayerX -= move_;

		if (this->PlayerY < 1)
			this->PlayerY = 1;
		if (this->PlayerX < 1)
			this->PlayerX = 1;
		if (this->PlayerY > mapSize.y)
			this->PlayerY = mapSize.y;
		if (this->PlayerX > mapSize.x)
			this->PlayerX = mapSize.x;
	}
}

int Player::getDirection() {
	return this->direction;
}

Vector2 Player::getPosition() {
	return Vector2(this->PlayerX, this->PlayerY);
}

Vector2 Player::getCordInFrontOfCharacter() {
	switch (this->direction)
	{
		case 0:
			return Vector2(this->PlayerX, this->PlayerY - 1);
			break;
		case 2:
			return Vector2(this->PlayerX, this->PlayerY + 1);
			break;

		case 1:
			return Vector2(this->PlayerX + 1, this->PlayerY);
			break;
		case 3:
			return Vector2(this->PlayerX - 1, this->PlayerY);
			break;
	}	
	return Vector2(0, 0);
}

Vector2 Player::getCordBehindCharacter() {
	if (direction == 2)
		return Vector2(this->PlayerX, this->PlayerY - 1);
	else if (this->direction == 0)
		return Vector2(this->PlayerX, this->PlayerY + 1);
	else if (this->direction == 3)
		return Vector2(this->PlayerX + 1, this->PlayerY);
	else if (this->direction == 1)
		return Vector2(this->PlayerX - 1, this->PlayerY);
	return Vector2(0, 0);
}