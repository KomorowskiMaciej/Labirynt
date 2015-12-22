#ifndef edytor_h
#define edytor_h

#include "stdio.h"
#include "Vector2.h"
#include <iostream>
#include "conio2.h"
#include "Mapa.h"

using namespace std;

class Edytor {

public:
	Vector2 * cursor;
	int** mapa;
	int** staryEkran;
	int** ekran;
	Vector2 * mapSize;
	Edytor(Mapa *mapa) {
		cursor = new Vector2(0, 0);
		system("cls");
		mapSize = new Vector2(mapa->mapSize->x, mapa->mapSize->y);
		this->mapa = new int*[mapa->mapSize->y];
		this->ekran = new int*[mapa->mapSize->y];
		this->staryEkran = new int*[mapa->mapSize->y];
		for (int i = 0; i < mapa->mapSize->y; i++)
		{
			this->mapa[i] = new int[mapa->mapSize->x];
			this->staryEkran[i] = new int[mapa->mapSize->x];
			this->ekran[i] = new int[mapa->mapSize->x];
			for (int j = 0; j < mapa->mapSize->y; j++)
			{
				this->mapa[i][j] = mapa->_Mapa[i][j];
				this->staryEkran[i][j] = '=';
				this->ekran[i][j] = 'g';
			}
		}
		Update();
		Render();
		loop();
	};

	int input;
	void loop() {
		input = 0;
		do
		{
			input = getch();
			if (input == 's')
				Save();
			Update();
			Render();
		} while (input != 'q');
	}

	void Render() {
		
		for (int y = 0; y < mapSize->y; y++) {
			for (int x = 0; x < mapSize->x; x++)
			{
				if (ekran[y][x] == staryEkran[y][x])
					continue;

				gotoxy(x + 5 , y + 5);
				switch (ekran[y][x])
				{
				case '0':
					cout << ' ';
					break;
				case '1':
					cout << char(176);
					break;
				case '2':
					cout << char(177);
					break;
				case '3':
					cout << char(178);
					break;
				case '4':
					cout << char(219);
					break;
				case '5':
					cout << '.';
					break;
				case '6':
					cout << char(206);
					break;
				case '7':
					cout << char(250);
					break;
				case 'X':
					cout << 'X';
					break;
				default:
					break;
				}
			}
		}
	}

	void Update() {
		for (int i = 0; i < mapSize->y; i++)
			for (int j = 0; j < mapSize->x; j++)
				staryEkran[i][j] = ekran[i][j];
		
		switch (input)
		{
		case '0':
			if (cursor->x != 0 && cursor->y != 0 && cursor->x + 1 != mapSize->x && cursor->y + 1 != mapSize->y)
				if (
					!((
					mapa[cursor->y + 1][cursor->x] == '0' &&
					mapa[cursor->y][cursor->x + 1] == '0' &&
					mapa[cursor->y + 1][cursor->x + 1] == '0'
					) || (
					mapa[cursor->y][cursor->x - 1] == '0' &&
					mapa[cursor->y + 1][cursor->x - 1] == '0' &&
					mapa[cursor->y + 1][cursor->x] == '0'
					) || (
					mapa[cursor->y - 1][cursor->x + 1] == '0' &&
					mapa[cursor->y][cursor->x + 1] == '0' &&
					mapa[cursor->y - 1][cursor->x] == '0'
					) || (
					mapa[cursor->y - 1][cursor->x] == '0' &&
					mapa[cursor->y][cursor->x - 1] == '0' &&
					mapa[cursor->y - 1][cursor->x - 1] == '0'
					))
				)
				mapa[cursor->y][cursor->x] = '0';
				break;
		case '1':
			mapa[cursor->y][cursor->x] = '1';
			break;
		case '2':
			mapa[cursor->y][cursor->x] = '2';
			break;
		case '3':
			mapa[cursor->y][cursor->x] = '3';
			break;
		case '4':
			mapa[cursor->y][cursor->x] = '4';
			break;
		case '5':
			mapa[cursor->y][cursor->x] = '5';
			break;
		case '6':
			mapa[cursor->y][cursor->x] = '6';
			break;
		case '7':
			mapa[cursor->y][cursor->x] = '7';
			break;


		case (char)72:{
			if (cursor->y > 0)
				cursor->y--;
			break;
		}
		case (char)80:{
			if (cursor->y + 1 < mapSize->y)
				cursor->y++;
			break;
		}
		case (char)75: {
			if (cursor->x > 0)
				cursor->x--;
			break;
		}
		case (char)77: {
			if (cursor->x + 1 < mapSize->x)
				cursor->x++;
			break;
		}
		default:
			break;
		}

		for (int i = 0; i < mapSize->y; i++)
			for (int j = 0; j < mapSize->x; j++)
				ekran[i][j] = mapa[i][j];

		ekran[cursor->y][cursor->x] = 'X';
	}

	void Save() {
		
		char * src;
		src = new char[999];
		gotoxy(20, 25);
		
		cout << "Podaj nazwe pliku: ";
		cin >> src;

		FILE * zrodlo = fopen(src, "wb");
		if (!zrodlo) {
			printf("Zla sciezka do pliku!");
			getch();
		}

		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 20; j++) {

				int liczba = 1;

				switch (mapa[i][j])
				{
				case '0':
					liczba = 0;
					break;
				case '1':
					liczba = 1;
					break;
				case '2':
					liczba = 2;
					break;
				case '3':
					liczba = 3;
					break;
				case '4':
					liczba = 4;
					break;
				case '5':
					liczba = 5;
					break;
				case '6':
					liczba = 6;
					break;
				case '7':
					liczba = 7;
					break;
				}

				fprintf(zrodlo, "%d", liczba);
			}
		fclose(zrodlo);
	}
};

#endif