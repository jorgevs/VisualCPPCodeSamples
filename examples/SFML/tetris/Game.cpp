#include "Game.h"

const Time Game::TimePerFrame = seconds(1.f / 60.f);


Game::Game() : window(VideoMode(320, 480), ".:TETRIS:.") {
	// Seeds the pseudo - random number generator used by rand() with the value seed.
	// time's parameter is an alternate return path. If you pass in NULL (or 0) it is ignored. 
	// Otherwise, you must pass the address of a time_t object which will be filled with the time.
	srand(time(0));

	this->colorNum = 1;
	this->dx = 0;
	this->rotate = false;
	this->timer = 0;
	this->delay = 0.3;

	this->t1.loadFromFile("images/tiles.png");
	this->t2.loadFromFile("images/background.png");
	this->t3.loadFromFile("images/frame.png");

	this->s.setTexture(t1);
	this->background.setTexture(t2);
	this->frame.setTexture(t3);

	// Initialize "a"
	createNewFigure();
}

Game::~Game() {}

void Game::run() {
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen()) {
		/*Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;*/

		processEvents();
		update(TimePerFrame);
		render();
		//}
	}
}

void Game::processEvents() {
	Event e;
	while (window.pollEvent(e)) {
		if (e.type == Event::Closed) {
			window.close();
		}
		if (e.type == Event::KeyPressed) {
			if (e.key.code == Keyboard::Up) rotate = true;
			else if (e.key.code == Keyboard::Left) dx = -1;
			else if (e.key.code == Keyboard::Right) dx = 1;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		// Reduces the delay from 0.3 to 0.05 accelerating the cycle
		delay = 0.05;
	}
}

void Game::update(Time dt) {
	float time = clock.getElapsedTime().asSeconds();
	clock.restart();
	timer += time;

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

		// Restart the timer
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
		// If count is lower than N moves "k" along with "i", otherwise  it will help to overwrite the 
		// completed row (where count was iqual to N) in the next iteration
		if (count < N) {
			k--;
		}
	}

	dx = 0;
	rotate = false;
	delay = 0.3;
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
			s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
			s.setPosition(j * 18, i * 18);
			s.move(28, 31); //offset
			window.draw(s);
		}
	}
	for (int i = 0; i < 4; i++) {
		s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
		s.setPosition(a[i].x * 18, a[i].y * 18);
		s.move(28, 31); //offset
		window.draw(s);
	}

	window.draw(frame);

	window.display();
}

/**
	This function checks if a given point is out of bounds or if it collides
	with another existing point in the field.
	returns 0 if out of bounds or collides
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