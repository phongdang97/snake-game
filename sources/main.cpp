#include "raylib.h"
#include <iostream>
#define SCREEN_WIDTH (750)
#define SCREEN_HEIGHT (750)

#define WINDOW_TITLE "Snake game"

using namespace std;

int main() {
    cout << "Starting the game" << endl;

    // Create entry screen.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);


    CloseWindow();

    return 0;
}
