#ifndef mapa_h
#define mapa_h

#include "stdio.h"
#include "Vector2.h"

using namespace std;

class Mapa {
public:
	Vector2 *playerCords;
	Vector2 *mapSize;
	int** _Mapa;

	Mapa(char* src) {

		mapSize = new Vector2(20, 20);
		playerCords = new Vector2(5, 1);

		_Mapa = new int*[mapSize->y];
		for (int i = 0; i < mapSize->y; i++) {
			_Mapa[i] = new int[mapSize->x];
		}

		GetMap(src);
	};

	int Mapa::GetMap(char* src) {
		FILE *zrodlo;

		if ((zrodlo = fopen(src, "rb")) == NULL) {
			return 0;
		}

		int * bufor = new int[999];

		for (int i = 0; i < mapSize->y; i++) {
			for (int j = 0; j < mapSize->x; j++)
			{
				*bufor = 0;
				if (feof(zrodlo) == 0)
					fscanf(zrodlo, "%c", bufor);
				_Mapa[i][j] = *bufor;
			}
		}

		return 1;
	}

};

#endif