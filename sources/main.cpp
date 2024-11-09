#include "raylib.h"
#include <iostream>
#include <deque>

#include "raymath.h"

#define WINDOW_TITLE "Snake game"

using namespace std;
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
double lastUpdateTime = 0;

bool eventTriggered(double interval) {
    const double currentTime = GetTime();
    if (currentTime > lastUpdateTime + interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void DrawPoint(int x, int y, Color color) {
    // DrawRectangle( color);
    auto rectangle = Rectangle{float(x * cellSize), float(y * cellSize), float(cellSize), float(cellSize)};
    DrawRectangleRounded(rectangle, 0.5, 9, color);
}

class Snake {
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

    void Draw() {
        for (const auto &i: body) {
            DrawPoint(static_cast<int>(i.x),
                      static_cast<int>(i.y),
                      darkGreen);
        }
    }

    void Update() {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
    }
};


class Food {
public:
    Vector2 position{};

    Food() {
        // Seed the random number generator
        SetRandomSeed(time(nullptr));
        position = GenerateRandomPos();
    }

    void Draw() const {
        DrawPoint(static_cast<int>(position.x),
                  static_cast<int>(position.y),
                  darkGreen);
    }

    // ~Food() {
    //     DrawRectangle(static_cast<int>(position.x) * cellSize,
    //                   static_cast<int>(position.y) * cellSize,
    //                   cellSize, cellSize, green);
    // }

    static Vector2 GenerateRandomPos() {
        const int x = GetRandomValue(0, cellCount - 1);
        const int y = GetRandomValue(0, cellCount - 1);
        return Vector2{static_cast<float>(x), static_cast<float>(y)};
    }
};


class Game {
public:
    Snake snake = Snake{};
    Food food = Food{};

    void Draw() {
        food.Draw();
        snake.Draw();
    }

    void Update() {
        snake.Update();
    }
};

using namespace std;

int main() {
    cout << "Starting the game" << endl;
    Game game = Game{};

    // Create entry screen.
    InitWindow(cellSize * cellCount, cellSize * cellCount, WINDOW_TITLE);
    SetTargetFPS(120);

    // Game loop
    // 1. Event handling
    // 2. Updating Positions
    // 3. Drawing Objects
    while (!WindowShouldClose()) {
        BeginDrawing();

        // Drawing
        ClearBackground(green);
        if (eventTriggered(0.2)) {
            // moving the snake
            game.Update();
        }
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = {0, -1};
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = {0, 1};
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = {-1, 0};
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = {1, 0};
        }
        game.Draw();


        EndDrawing();
    }

    CloseWindow();

    return 0;
}
