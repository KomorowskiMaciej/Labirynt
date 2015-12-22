#ifndef Labirynt_3d_h
#define Labirynt_3d_h

#include <iostream>
#include "conio2.h"
#include "Player.h"
#include <time.h>
#include "mapa.h"
#include "Vector2.h"

using namespace std;

class Labirynt3d {

private:
	Labirynt3d(void) {
		glebokosc = 7;
		wielkoscMini = new Vector2(3, 7);
		wielkoscEkran = new Vector2(61, 45);
		wielkoscEkranGlowny = new Vector2(80, 50);
		mapSwitch = false;
	};

	//klawiatura
	int input;
	//mapa
	Vector2 *wielkoscMini;
	Vector2 *wielkoscEkran;
	Vector2 *wielkoscEkranGlowny;
	int glebokosc;

	time_t start_time;
	time_t current_time;

	bool mapSwitch;

	//obiekty
	Player *gracz;
	void print();
	void drawMenu();
	void menu();
	void loop();
	void start();
	//update
	void update(int animacja = 5) {
		// ruch postaci
		gracz->doAction(input, mapa);
		// aktualizacja tablic minimapy
		if (animacja > 4)
			minimapUpdate();
		// aktualizacja tablicy swiata 3d
		worldUpdate(animacja);
		// aktualizacja tablic mapy
		mapUpdate();
	}

	//render
	void render(int animacja = 5) {
		renderWorld(2, 2);
		//renderMinimap(58, 7);
		if (mapSwitch)
			renderMap(21, 13);
		gotoxy(1, 1);
	}

	Mapa *mapa;
	int **ekranMapy;
	int **staryEkranMapy;
	int **ekranSwiata;
	int **staryEkranSwiata;
	int **ekranMini;
	int **staryEkranMini;
	int **ekranGlowny;
	int **staryEkranGlowny;
	int animacjaChodzenia;
	void minimapUpdate();
	void renderMinimap(int, int);
	void renderMap(int, int);
	void renderWorld(int, int);
	void mapUpdate();
	void worldUpdate(int);
	bool przelacznikAnimacji;
public:

	void init();


	//sigleton
	static Labirynt3d & getInstance()
	{
		static Labirynt3d instance;
		return instance;
	}
};

#endif