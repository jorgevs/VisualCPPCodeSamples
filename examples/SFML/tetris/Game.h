#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

using namespace sf;

class Game {

public:
	Game();
	void run();

private:
	void processEvents();
	void update(Time dt);
	void playSounds();
	void render();

	bool check();
	void createNewFigure();

private:
	RenderWindow window;

	static const int M = 25;
	static const int N = 10;
	static const int NUM_PIXELS = 24;

	Texture t1, t2, t3;
	Sprite s, background, frame;

	SoundBuffer buffer;
	Sound sound;

	int dx, colorNum;
	bool rotate, isLineRemoved;
	float timer, delay;

	int field[M][N] = { 0 };

	struct Point {
		int x;
		int y;
	};
	Point a[4] = { 0 };
	Point b[4] = { 0 };

	const int figures[7][4] = {
		1,3,5,7, // I
		2,4,5,7, // Z
		3,5,4,6, // S
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // O
	};

};