/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib-cpp.hpp"

int main() {
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	raylib::Color background(RAYWHITE);
	raylib::Color textColor(LIGHTGRAY);
	raylib::Window w(screenWidth, screenHeight, "raylib [core] example - basic window");

	// Box A: Moving box
	raylib::Rectangle boxA(10, GetScreenHeight() / 2 - 50, 200, 100);
	int boxASpeedX = 4;

	// Box B: Mouse moved box
	raylib::Rectangle boxB(GetScreenWidth() / 2 - 30, GetScreenHeight() / 2 - 30, 60, 60);

	raylib::Rectangle boxCollision(0); // Collision rectangle
	///raylib::Rectangle boxCollision(0,0); // Collision rectangle

	int screenUpperLimit = 40;      // Top menu limits

	bool pause = false;             // Movement pause
	bool collision = false;         // Collision detection

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!w.ShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		
		// Move box if not paused
		if (!pause) boxA.x += boxASpeedX;

		// Bounce box on x screen limits
		if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0)) boxASpeedX *= -1;

		// Update player-controlled-box (box02)
		boxB.x = GetMouseX() - boxB.width / 2;
		boxB.y = GetMouseY() - boxB.height / 2;

		// Make sure Box B does not go out of move area limits
		if ((boxB.x + boxB.width) >= GetScreenWidth()) boxB.x = GetScreenWidth() - boxB.width;
		else if (boxB.x <= 0) boxB.x = 0;

		if ((boxB.y + boxB.height) >= GetScreenHeight()) boxB.y = GetScreenHeight() - boxB.height;
		else if (boxB.y <= screenUpperLimit) boxB.y = screenUpperLimit;

		// Check boxes collision
		collision = boxA.CheckCollision(boxB);

		// Get collision rectangle (only on collision)
		if (collision) boxCollision = boxA.GetCollision(boxB);

		// Pause Box A movement
		if (IsKeyPressed(KEY_SPACE)) pause = !pause;
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		//background.ClearBackground();
		textColor.DrawText("Congrats! You created your first window!", 190, 80, 20);

		ClearBackground(RAYWHITE);

		DrawRectangle(0, 0, screenWidth, screenUpperLimit, collision ? RED : BLACK);

		boxA.Draw(GOLD);
		boxB.Draw(BLUE);

		if (collision) {
			// Draw collision area
			boxCollision.Draw(LIME);

			// Draw collision message
			DrawText("COLLISION!", GetScreenWidth() / 2 - MeasureText("COLLISION!", 20) / 2, screenUpperLimit / 2 - 10, 20, BLACK);

			// Draw collision area
			DrawText(FormatText("Collision Area: %i", (int)boxCollision.width * (int)boxCollision.height), GetScreenWidth() / 2 - 100, screenUpperLimit + 10, 20, BLACK);
		}

		DrawFPS(10, 10);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	return 0;
}