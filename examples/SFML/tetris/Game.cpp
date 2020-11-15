#include "Game.h"
#include <iostream>

/**
* Game Constructor
*/
Game::Game() : window(VideoMode(600, 760), ".:TETRIS:.") {
	// Seeds the pseudo - random number generator used by rand() with the value seed.
	// time's parameter is an alternate return path. If you pass in NULL (or 0) it is ignored. 
	// Otherwise, you must pass the address of a time_t object which will be filled with the time.
	srand(time(0));
	
	this->colorNum = 1;
	this->dx = 0;
	this->rotate = false;
	this->isLineRemoved = false;
	this->timer = 0;
	this->delay = 0.3;

	this->t1.loadFromFile("images/tetrisTiles.png");
	this->t2.loadFromFile("images/tetrisBackground.png");
	//this->t3.loadFromFile("images/tetrisFrame.png");

	this->s.setTexture(t1);
	this->background.setTexture(t2);
	this->frame.setTexture(t3);


	buffer.loadFromFile("sounds/deleteLine.ogg");
	sound.setBuffer(buffer);
	
	// Initialize "a"
	createNewFigure();
}

/**
* This is the principal method, which orchestates all the operations to be 
* executed in the game.
*/
void Game::run() {
	Clock clock; // Starts counting as soon as it is created
	const Time TimePerFrame = seconds(1.f / 60.f);
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen()) {

		processEvents();

		// The following code assures that the update() method is called once per frame,
		// in a fixed time (60 frames per second in this case).
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			update(TimePerFrame);
		}

		playSounds();

		render();
	}
}

void Game::processEvents() {
	Event e;
	while (window.pollEvent(e)) {
		if (e.type == Event::Closed) {
			window.close();
		}
		if (e.type == Event::KeyPressed) {
			if (e.key.code == Keyboard::Up) {
				rotate = true;
			} else if (e.key.code == Keyboard::Left) {
				dx = -1;
			} else if (e.key.code == Keyboard::Right) {
				dx = 1;
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		// Reduces the delay from 0.3 to 0.05 accelerating the cycle
		delay = 0.05;
	}
}

void Game::update(Time deltaTime) {
	timer += deltaTime.asSeconds();

	//// <- Move -> ///
	// Store old "a" values into "b" and updates "a" based on the move
	if (dx != 0) {
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!check()) {
			// If "a" cannot be moved, then revert "a" to its original values
			for (int i = 0; i < 4; i++) {
				a[i] = b[i];
			}
		}
	}

	//////Rotate//////
	if (rotate) {
		Point p = a[1]; //center of rotation
		for (int i = 0; i < 4; i++) {
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
		if (!check()) {
			for (int i = 0; i < 4; i++) {
				a[i] = b[i];
			}
		}
	}

	///////Tick//////
	if (timer > delay) {
		// Store old "a" values into "b" and moves "a" one position down
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].y += 1;
		}

		if (!check()) {
			for (int i = 0; i < 4; i++) {
				field[b[i].y][b[i].x] = colorNum;
			}

			createNewFigure();
		}

		// After every tick restart the timer
		timer = 0;
	}

	///////check lines//////////
	int k = M - 1;
	for (int i = M - 1; i > 0; i--) {
		int count = 0;
		for (int j = 0; j < N; j++) {
			if (field[i][j]) {
				count++;
			}
			field[k][j] = field[i][j];
		}
		// If count is lower than N moves "k" along with "i", otherwise it will help to overwrite the 
		// completed row (where count was iqual to N) in the next iteration
		if (count < N) {
			k--;
		} else {
			isLineRemoved = true;
		}
	}

	dx = 0;
	rotate = false;
	delay = 0.3;
}


/**
* Plays any global sound based on flags
*/
void Game::playSounds() {
	if (isLineRemoved) {
		sound.play();
		isLineRemoved = false;
	}
}

void Game::createNewFigure() {
	// Ramdomly selects a new color and a figure
	colorNum = (rand() % 7) + 1;  // Returns a value between 1 and 7
	int n = rand() % 7;			  // Retuns a value between 0 and 6 that points to the new figure
	for (int i = 0; i < 4; i++) {
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
}

void Game::render() {
	window.clear(Color::White);

	/////////draw//////////
	window.draw(background);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			// If field's position is zero, do nothing
			if (field[i][j] == 0) {
				continue;
			}
			s.setTextureRect(IntRect(field[i][j] * NUM_PIXELS, 0, NUM_PIXELS, NUM_PIXELS));
			s.setPosition(j * NUM_PIXELS, i * NUM_PIXELS);
			s.move(30, 30); //offset
			window.draw(s);
		}
	}
	for (int i = 0; i < 4; i++) {
		s.setTextureRect(IntRect(colorNum * NUM_PIXELS, 0, NUM_PIXELS, NUM_PIXELS));
		s.setPosition(a[i].x * NUM_PIXELS, a[i].y * NUM_PIXELS);
		s.move(30, 30); //offset
		window.draw(s);
	}

	window.draw(frame);

	window.display();
}

/**
* This function checks if a given point is out of bounds or if it collides 
* with another existing point in the field.
* Returns 0 if out of bounds or collides
*/
bool Game::check() {
	for (int i = 0; i < 4; i++) {
		// Check if any "a" point is out of bounds
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) {
			return 0;
			// Check if the field has a value other than zero in "a" point
		} else if (field[a[i].y][a[i].x]) {
			return 0;
		}
	}
	// If not out of bounds or collides then return 1
	return 1;
};