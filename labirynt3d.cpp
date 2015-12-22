#include "Labirynt3d.h"
#include "Vector2.h"
#include <iostream>
#include "conio2.h"
#include "Edytor.h"

/*menu***************************************************************************************************/

void Labirynt3d::drawMenu() {
	system("cls");
	cout << "                                            \n";
	cout << "               Labirynt 3D!                 \n";
	cout << "                                            \n";
	cout << "           /=====================================\\              \n";
	cout << "           |                 MENU                |     \n";
	cout << "           |                                     |     \n";
	cout << "           | S. START GRY                        |     \n";
	cout << "           | I. DOMYSLNY LABIRYNT                |    \n";
	cout << "           | O. MAPA Z PLIKU                     |               \n";
	cout << "           | Q. OPUSZCZENIE PROGRAMY             |  \n";
	cout << "           | E. WEJSCIE DO EDYTORA               |               \n";
	cout << "           |                                     |     \n";
	cout << "           | A. AKRYWACJA ANIMACJI (PODCZAS GRY) |   \n";
	cout << "           | H. POMOC (PODCZAS GRY)              |   \n";
	cout << "           | R. RESTART GRY (PODCZAS GRY)        |               \n";
	cout << "           \\====================================/              \n";
	cout << "                                            \n";
	cout << "                 S160822                    \n";
	cout << "                                            \n";
}  

void Labirynt3d::menu() {
	int input = 0;
	drawMenu();
	mapa = new Mapa("Standardowa_mapa.txt");
	do {
		input = getch();
		if (input == 's') {
			start();
			drawMenu();
		}
		if (input == 'i') {
			gotoxy(20, 20);
			if (mapa->GetMap("Standardowa_mapa.txt") == 1)
				cout << "Pomyslnie zaladowana standardowa mapa!                         ";
			else cout <<"Blad odczytu mapy!                                             ";
		}

		if (input == 'e') {
			Edytor * edytor = new Edytor(mapa);
			delete edytor;
			drawMenu();
		}

		if (input == 'o') {
			gotoxy(20,20);
			cout << "Podaj nazwe mapy                                              ";
			char * nazwaMapy;
			nazwaMapy = new char[255];
			cin >> nazwaMapy;
			gotoxy(20, 20);
			if(mapa->GetMap(nazwaMapy) == 1)
				cout << "Zaladowany pomyslnie nowa mape!                           ";
			else cout << "Blad odczytu mapy!                                       ";
		}
	} while (input != 'q');
}

/*gra***************************************************************************************************/

// zmienne statyczne

//czas
//static time_t Start_time;
//static time_t Current_time;
int sizeX;
int sizeY;
void Labirynt3d::start() {
	sizeX = 20;
	sizeY = 20;
	// czyszczenie ekranu, resetowanie zmiennych, tworzenie obiektów

	system("cls");

	gracz = new Player(mapa->playerCords->x, mapa->playerCords->y);


	// tworzenie tablic generycznych

	ekranMapy = new int*[mapa->mapSize->y];
	staryEkranMapy = new int*[mapa->mapSize->y];

	ekranGlowny = new int*[wielkoscEkranGlowny->y];
	staryEkranGlowny = new int*[wielkoscEkranGlowny->y];

	ekranMini = new int*[wielkoscMini->y];
	staryEkranMini = new int*[wielkoscMini->y];

	ekranSwiata = new int*[wielkoscEkran->y];
	staryEkranSwiata = new int*[wielkoscEkran->y];

	for (int i = 0; i < sizeY; i++) {

		ekranMapy[i] = new int[wielkoscEkran->x];
		staryEkranMapy[i] = new int[wielkoscEkran->x];
	}

	for (int i = 0; i < wielkoscMini->y; i++) {
		ekranMini[i] = new int[wielkoscMini->x];
		staryEkranMini[i] = new int[wielkoscMini->x];
	}

	for (int i = 0; i < wielkoscEkran->y; i++) {
		ekranSwiata[i] = new int[wielkoscEkran->x];
		staryEkranSwiata[i] = new int[wielkoscEkran->x];
	}

	for (int i = 0; i < wielkoscEkranGlowny->y; i++){
		ekranGlowny[i] = new int[wielkoscEkranGlowny->x];
		staryEkranGlowny[i] = new int[wielkoscEkranGlowny->x];
		for (int j = 0; j < wielkoscEkranGlowny->x; j++) {
			ekranGlowny[i][j] = (char) ' ';
			staryEkranGlowny[i][j] = (char) ' ';
		}
	}
	// ustawianie poczatkowego czasu
	start_time = time(nullptr);
	current_time = time(nullptr);

	// petla

	loop();
	delete gracz;
}

void Labirynt3d::loop() {
	update();
	render();
	print();
	input = 0;
	// petla
	animacjaChodzenia = 5;
	przelacznikAnimacji = false;
	do {
		if (kbhit() != 0) {
			input = getch();
		}
		else input = 0;

		if (input == 'm') {
			mapSwitch = !mapSwitch;
		}

		if (input == 'a') {
			przelacznikAnimacji = !przelacznikAnimacji;
		}

		if (input == 'd') {
			if (mapa->_Mapa[gracz->getCordInFrontOfCharacter().y-1][gracz->getCordInFrontOfCharacter().x-1] == '6')
				mapa->_Mapa[gracz->getCordInFrontOfCharacter().y - 1][gracz->getCordInFrontOfCharacter().x - 1] = '7';
			else if (mapa->_Mapa[gracz->getCordInFrontOfCharacter().y - 1][gracz->getCordInFrontOfCharacter().x - 1] == '7')
				mapa->_Mapa[gracz->getCordInFrontOfCharacter().y - 1][gracz->getCordInFrontOfCharacter().x - 1] = '6';
		}

		if (input != 0) {
			if (
				input == (char)72
				&& przelacznikAnimacji
				&& mapa->_Mapa[gracz->getCordInFrontOfCharacter().y - 1][gracz->getCordInFrontOfCharacter().x - 1] == '0'
				&& animacjaChodzenia > 4
			) {
					animacjaChodzenia = 0;
					update(animacjaChodzenia);
					render(animacjaChodzenia);
					print();
				} else {
					update();
					render();
					print();
				}
		}
		else if (animacjaChodzenia++ < 5) {
			update(animacjaChodzenia);
			render(animacjaChodzenia);
			print();
		}
		else if (animacjaChodzenia == 4) {
			animacjaChodzenia = 5;
			update();
			render();
			print();
		}
		
		if (time(nullptr) > current_time) {
			current_time = time(nullptr);

			int sec = (current_time - start_time) % 60;
			int min = (current_time - start_time) / 60;

			gotoxy(4, 4);
			cout << "    ";
			gotoxy(4, 4);
			cout << min << ":" << sec;


			gotoxy(20, 44);
			cout << "Maciej Komorowski S160822";

			gotoxy(1, 1);
		}
		
	} while (input != 'q');
}

void Labirynt3d::worldUpdate(int animacja = 5) {

	//czyszczenie
	for (int i = 0; i < wielkoscEkran->y; i++)
		for (int j = 0; j < wielkoscEkran->x; j++) {
			ekranSwiata[i][j] = ' ';
		}
	int perspektywa = 0;
	//wypelnienie
	for (int z = glebokosc; z > 0; z--) {


		int animacjaY = 0;

		if (animacja <= 4)
			animacjaY = animacja;
		if (z * 3 + animacjaY > wielkoscEkran->y / 2)
			animacjaY = 0;
		else if (wielkoscEkran->y - z * 3 - animacjaY < 0)
			animacjaY = 0;
		if (animacjaY == 4) 
			animacjaY = 3;

		int perspektywaY = z * 3 - animacjaY;

		for (int y = perspektywaY; (y < wielkoscEkran->y - perspektywaY); y++) {
			for (int x = 0; x < wielkoscEkran->x; x++) {

				perspektywa = 3 * (glebokosc - z);
				if (perspektywa == 0)
					perspektywa = 2;

				if (animacja > 0 && animacja < 5)
					if (animacja == 4)
						perspektywa += 3;
					else 
						perspektywa += animacja;
						
						

				//lewa strona

				if (x < (wielkoscEkran->x / 2) - perspektywa) {
					//horyzont
					if (ekranMini[glebokosc - z][0] == ' ' && z == 7 && wielkoscEkran->y / 2 == y) {
						ekranSwiata[y][x] = '-';
					}
					else

						if (ekranMini[glebokosc - z][0] != ' ')
						 //sciecia
						 if ((ekranMini[glebokosc - z][1] == ' ' || ekranMini[glebokosc - z][1] == '^')
							 &&(
							 
							 (x == (wielkoscEkran->x / 2) - perspektywa - 1 && (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1))
							 || (x == (wielkoscEkran->x / 2) - perspektywa - 2 && (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1))
							 || (x == (wielkoscEkran->x / 2) - perspektywa - 3 && (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1))

							 || (x == (wielkoscEkran->x / 2) - perspektywa - 1 && (y == perspektywaY + 1 || y == wielkoscEkran->y - perspektywaY - 2))
							 || (x == (wielkoscEkran->x / 2) - perspektywa - 2 && (y == perspektywaY + 1 || y == wielkoscEkran->y - perspektywaY - 2))

							 || (x == (wielkoscEkran->x / 2) - perspektywa - 1 && (y == perspektywaY + 2 || y == wielkoscEkran->y - perspektywaY - 3))
							)
						) 
							ekranSwiata[y][x] = ' ';
					else
						if ((ekranMini[glebokosc - z][1] == ' ' || ekranMini[glebokosc - z][1] == '^')
							&& (

							(x == (wielkoscEkran->x / 2) - perspektywa - 1 && (y == perspektywaY + 3))
							|| (x == (wielkoscEkran->x / 2) - perspektywa - 2 && (y == perspektywaY + 2))
							|| (x == (wielkoscEkran->x / 2) - perspektywa - 3 && (y == perspektywaY + 1))
							)
						)
							ekranSwiata[y][x] = '\\';
					else
						if ((ekranMini[glebokosc - z][1] == ' ' || ekranMini[glebokosc - z][1] == '^')
						&& (
						(x == (wielkoscEkran->x / 2) - perspektywa - 1 && y == wielkoscEkran->y - perspektywaY - 4)
						|| (x == (wielkoscEkran->x / 2) - perspektywa - 2 && y == wielkoscEkran->y - perspektywaY - 3)
						|| (x == (wielkoscEkran->x / 2) - perspektywa - 3 && y == wielkoscEkran->y - perspektywaY - 2)
						)
					)
						ekranSwiata[y][x] = '/';

						else
							if (x == (wielkoscEkran->x / 2) - perspektywa - 1 && (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1))
							ekranSwiata[y][x] = '+';
						else
							if (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1)
							ekranSwiata[y][x] = '-';
						else
							if (x == (wielkoscEkran->x / 2) - perspektywa - 1 || x == (wielkoscEkran->x / 2) - perspektywa - 4)
							ekranSwiata[y][x] = '|';
						else if (ekranMini[glebokosc - z][0] == char(250)) {
							if (x % 2 == 0 && y % 2 == 0)
								ekranSwiata[y][x] = char(250);
						} else
						ekranSwiata[y][x] = ekranMini[glebokosc - z][0];
				} 
				//prawa strona


				else if (x > (wielkoscEkran->x / 2) + perspektywa) {
					if (ekranMini[glebokosc - z][2] == ' ' && z == 7 && wielkoscEkran->y / 2 == y) {
						ekranSwiata[y][x] = '-';
					}
					else
					if (ekranMini[glebokosc - z][2] != ' ')
						//sciecia
						if ((ekranMini[glebokosc - z][1] == ' ' || ekranMini[glebokosc - z][1] == '^')
							&& (

							(x == (wielkoscEkran->x / 2) + perspektywa + 1 && (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1))
							|| (x == (wielkoscEkran->x / 2) + perspektywa + 2 && (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1))
							|| (x == (wielkoscEkran->x / 2) + perspektywa + 3 && (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1))

							|| (x == (wielkoscEkran->x / 2) + perspektywa + 1 && (y == perspektywaY + 1 || y == wielkoscEkran->y - perspektywaY - 2))
							|| (x == (wielkoscEkran->x / 2) + perspektywa + 2 && (y == perspektywaY + 1 || y == wielkoscEkran->y - perspektywaY - 2))

							|| (x == (wielkoscEkran->x / 2) + perspektywa + 1 && (y == perspektywaY + 2 || y == wielkoscEkran->y - perspektywaY - 3))

							)
						)
							ekranSwiata[y][x] = ' ';
						else
							if ((ekranMini[glebokosc - z][1] == ' ' || ekranMini[glebokosc - z][1] == '^')
							&& (

							(x == (wielkoscEkran->x / 2) + perspektywa + 1 && (y == perspektywaY + 3))
							|| (x == (wielkoscEkran->x / 2) + perspektywa + 2 && (y == perspektywaY + 2))
							|| (x == (wielkoscEkran->x / 2) + perspektywa + 3 && (y == perspektywaY + 1))
							)
							)
							ekranSwiata[y][x] = '/';
						else
							if ((ekranMini[glebokosc - z][1] == ' ' || ekranMini[glebokosc - z][1] == '^')
							&& (
							(x == (wielkoscEkran->x / 2) + perspektywa + 1 && y == wielkoscEkran->y - perspektywaY - 4)
							|| (x == (wielkoscEkran->x / 2) + perspektywa + 2 && y == wielkoscEkran->y - perspektywaY - 3)
							|| (x == (wielkoscEkran->x / 2) + perspektywa + 3 && y == wielkoscEkran->y - perspektywaY - 2)
							)
							)
							ekranSwiata[y][x] = '\\';

						else if (ekranMini[glebokosc - z][2] != ' ')
							if (x == (wielkoscEkran->x / 2) + perspektywa + 1 && (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1))
							ekranSwiata[y][x] = '+';
						else
							if (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1)
							ekranSwiata[y][x] = '-';
						else
							if (x == (wielkoscEkran->x / 2) + perspektywa + 1 || x == (wielkoscEkran->x / 2) + perspektywa + 4)
							ekranSwiata[y][x] = '|';
							else if (ekranMini[glebokosc - z][2] == char(250)) {
								if (x % 2 == 0 && y % 2 == 0)
									ekranSwiata[y][x] = char(250);
							}
							else
							ekranSwiata[y][x] = ekranMini[glebokosc - z][2];
				}
				
				//srodek
				else {
					if (ekranMini[glebokosc - z][1] == ' ' && z == 7 && wielkoscEkran->y / 2 == y) {
						ekranSwiata[y][x] = '-';
					}
					else
						if (ekranMini[glebokosc - z][1] != '^' && ekranMini[glebokosc - z][1] != ' ') {
						
							if ((x == (wielkoscEkran->x / 2) - perspektywa || x == (wielkoscEkran->x / 2) + perspektywa) && (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1))
							ekranSwiata[y][x] = '+';
						else
							if (y == perspektywaY || y == wielkoscEkran->y - perspektywaY - 1)
							ekranSwiata[y][x] = '-';
						else 
							if (x == (wielkoscEkran->x / 2) - perspektywa || x == (wielkoscEkran->x / 2) + perspektywa)
							ekranSwiata[y][x] = '|';
						else if (ekranMini[glebokosc - z][1] == char(250)) {
							if (x % 2 == 0 && y % 2 == 0)
								ekranSwiata[y][x] = char(250);
						}
						else
							ekranSwiata[y][x] = ekranMini[glebokosc - z][1];
					}
						
				}
			}
		}
	}
	//ramka
	for (int x = 0; x < wielkoscEkran->x; x++) {
		ekranSwiata[0][x] = (char)219;
		ekranSwiata[1][x] = ' ';
		ekranSwiata[2][x] = ' ';
		ekranSwiata[3][x] = ' ';
		ekranSwiata[4][x] = (char)219;
		ekranSwiata[wielkoscEkran->y - 1][x] = (char)219;
		ekranSwiata[wielkoscEkran->y - 2][x] = ' ';
		ekranSwiata[wielkoscEkran->y - 3][x] = ' ';
		ekranSwiata[wielkoscEkran->y - 4][x] = ' ';
		ekranSwiata[wielkoscEkran->y - 5][x] = (char)219;
	}
	for (int y = 0; y < wielkoscEkran->y; y++) {
		ekranSwiata[y][0] = (char)219;
		ekranSwiata[y][wielkoscEkran->x - 1] = (char)219;
	}
}

void Labirynt3d::renderWorld(int whereX, int whereY) {
	for (int y = 0; y < wielkoscEkran->y; y++)
		for (int x = 0; x < wielkoscEkran->x; x++) {
			ekranGlowny[y + whereX][x + whereX] = (char)ekranSwiata[y][x];
		}
};

void Labirynt3d::print() {

	for (int y = 0; y < wielkoscEkranGlowny->y; y++)
		for (int x = 0; x < wielkoscEkranGlowny->x; x++) {
			gotoxy(x, y);
			if (staryEkranGlowny[y][x] != ekranGlowny[y][x])
				cout << (char)ekranGlowny[y][x];
		}

	for (int i = 0; i < wielkoscEkranGlowny->y; i++){
		for (int j = 0; j < wielkoscEkranGlowny->x; j++) {
			staryEkranGlowny[i][j] = ekranGlowny[i][j];
		}
	}

}


void Labirynt3d::minimapUpdate() {
	for (int y = 0; y < wielkoscMini->y; y++)
	{
		for (int x = 0; x < wielkoscMini->x; x++) {
			staryEkranMini[y][x] = ekranMini[y][x];

			//gora
			if (gracz->getDirection() == 0 &&
				gracz->getPosition().y - 7 + y >= 0 &&
				gracz->getPosition().x - 2 + x >= 0 &&
				gracz->getPosition().x - 2 + x <= mapa->mapSize->x
				)
				ekranMini[y][x] = mapa->_Mapa[gracz->getPosition().y - 7 + y][gracz->getPosition().x + x - 2];

			//dol
			else if (gracz->getDirection() == 2 &&
				gracz->getPosition().y + 6 - y <= mapa->mapSize->y &&
				gracz->getPosition().x - x >= 0 &&
				gracz->getPosition().x - 2 + x <= mapa->mapSize->x
				)
				ekranMini[y][x] = mapa->_Mapa[gracz->getPosition().y + 5 - y][gracz->getPosition().x - x];

			//prawo
			else if (
				gracz->getDirection() == 1 &&
				gracz->getPosition().x + 5 - y <= mapa->mapSize->x &&
				gracz->getPosition().y + x - 2 >= 0 &&
				gracz->getPosition().y + x - 2 <= mapa->mapSize->y
				)
				ekranMini[y][x] = mapa->_Mapa[gracz->getPosition().y + x - 2][gracz->getPosition().x + 5 - y];

			//lewo
			else if (
				gracz->getDirection() == 3 &&
				gracz->getPosition().x - 7 + y >= 0 &&
				gracz->getPosition().y - x >= 0 &&
				gracz->getPosition().y + x - 2 <= mapa->mapSize->y
				)
				ekranMini[y][x] = mapa->_Mapa[gracz->getPosition().y - x][gracz->getPosition().x - 7 + y];
			else ekranMini[y][x] = '*';


			//rodzaj scian
			switch (ekranMini[y][x])
			{
			case '0':
				ekranMini[y][x] = ' ';
				break;
			case '1':
				ekranMini[y][x] = char(176);
				break;
			case '2':
				ekranMini[y][x] = char(177);
				break;
			case '3':
				ekranMini[y][x] = char(178);
				break;
			case '4':
				ekranMini[y][x] = char(219);
				break;
			case '5':
				ekranMini[y][x] = '.';
				break;
			case '6':
				ekranMini[y][x] = char(206);
				break;
			case '7':
				ekranMini[y][x] = char(250);
				break;
			default:
				break;
			}

		}
	}
	ekranMini[6][1] = '^';
}

void Labirynt3d::renderMap(int whereX, int whereY) {
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 24; j++) {
			if (i == 1 || j == 1 || i == 22 || j == 22)
				ekranGlowny[i + whereY][j + whereX] = ' ';
			else
			if (i == 0 || j == 0 || i == 23 || j == 23)
				ekranGlowny[i + whereY][j + whereX] = (char)219;
			else
			switch (ekranMapy[i-2][j-2]) {

			case '0':
				ekranGlowny[i + whereY][j + whereX] = ' ';
				break;
			case '1':
				ekranGlowny[i + whereY][j + whereX] = char(176);
				break;
			case '2':
				ekranGlowny[i + whereY][j + whereX] = char(177);
				break;
			case '3':
				ekranGlowny[i + whereY][j + whereX] = char(178);
				break;
			case '4':
				ekranGlowny[i + whereY][j + whereX] = char(219);
				break;
			case '5':
				ekranGlowny[i + whereY][j + whereX] = '.';
				break;
			case '6':
				ekranGlowny[i + whereY][j + whereX] = char(206);
				break;
			case '7':
				ekranGlowny[i + whereY][j + whereX] = char(250);
				break;
			case '<':
				ekranGlowny[i + whereY][j + whereX] = '<';
				break;
			case '>':
				ekranGlowny[i + whereY][j + whereX] = '>';
				break;
			case '^':
				ekranGlowny[i + whereY][j + whereX] = '^';
				break;
			case 'V':
				ekranGlowny[i + whereY][j + whereX] = 'V';
				break;
			}
		}
}

void Labirynt3d::mapUpdate() {
	// rysowanie ekranu na podstawie mapy
	for (int i = 0; i < mapa->mapSize->y; i++)
	{
		for (int j = 0; j < mapa->mapSize->x; j++)
		{
			staryEkranMapy[i][j] = ekranMapy[i][j];
			ekranMapy[i][j] = mapa->_Mapa[i][j];
		}
	}

	switch (gracz->getDirection())
	{
	case 0:
		ekranMapy[gracz->getPosition().y - 1][gracz->getPosition().x - 1] = '^';
		break;
	case 1:
		ekranMapy[gracz->getPosition().y - 1][gracz->getPosition().x - 1] = '>';
		break;
	case 2:
		ekranMapy[gracz->getPosition().y - 1][gracz->getPosition().x - 1] = 'V';
		break;
	case 3:
		ekranMapy[gracz->getPosition().y - 1][gracz->getPosition().x - 1] = '<';
		break;
	default:
		break;
	}
}

void Labirynt3d::renderMinimap(int whereX, int whereY) {
	for (int y = 0; y < wielkoscMini->y; y++)
		for (int x = 0; x < wielkoscMini->x; x++) 
				ekranGlowny[y + whereY][x + whereX] = (char)ekranMini[y][x];
}

void Labirynt3d::init() {
	menu();
};
