#include "raylib.h"
#include <iostream>


#define WINDOW_TITLE "Snake game"

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Food {
public:
    Vector2 position{};

    Food() {
        // Seed the random number generator
        SetRandomSeed(time(nullptr));
        position = GenerateRandomPos();
    }

    void Draw() const {
        DrawRectangle(static_cast<int>(position.x) * cellSize,
                      static_cast<int>(position.y) * cellSize,
                      cellSize, cellSize, darkGreen);
    }

    ~Food() {
        DrawRectangle(static_cast<int>(position.x) * cellSize,
                      static_cast<int>(position.y) * cellSize,
                      cellSize, cellSize, green);
    }

    static Vector2 GenerateRandomPos() {
        const int x = GetRandomValue(0, cellCount - 1);
        const int y = GetRandomValue(0, cellCount - 1);
        return Vector2{static_cast<float>(x), static_cast<float>(y)};
    }
};


using namespace std;

int main() {
    cout << "Starting the game" << endl;
    auto food = Food();
    // Create entry screen.
    InitWindow(cellSize * cellCount, cellSize * cellCount, WINDOW_TITLE);
    SetTargetFPS(60);

    // Game loop
    // 1. Event handling
    // 2. Updating Positions
    // 3. Drawing Objects
    while (!WindowShouldClose()) {
        BeginDrawing();

        // Drawing
        ClearBackground(green);
        food.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
