#include "raylib.h"
#include <iostream>
#define SCREEN_WIDTH (750)
#define SCREEN_HEIGHT (750)

#define WINDOW_TITLE "Snake game"

Color green = {173, 204, 96, 255};
Color darkGreen= {43, 51, 24, 255};

using namespace std;

int main() {
    cout << "Starting the game" << endl;

    // Create entry screen.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Game loop
    // 1. Event handling
    // 2. Updating Positions
    // 3. Drawing Objects
    while (!WindowShouldClose()) {
        BeginDrawing();

        // Drawing
        ClearBackground(green);


        EndDrawing();
    }

    CloseWindow();

    return 0;
}
