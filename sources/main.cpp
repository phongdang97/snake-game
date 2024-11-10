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
int offset = 75;
double lastUpdateTime = 0;

bool eventTriggered(double interval) {
    const double currentTime = GetTime();
    if (currentTime > lastUpdateTime + interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool elementInDeque(Vector2 element, const deque<Vector2> &deque) {
    for (const auto &i: deque) {
        if (Vector2Equals(i, element)) return true;
    }
    return false;
}


void DrawPoint(int x, int y, Color color) {
    // DrawRectangle( color);
    auto rectangle = Rectangle{float(x * cellSize + offset), float(y * cellSize + offset), float(cellSize), float(cellSize)};
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


    void Update(Vector2 foodPos) {
        cout <<"Snake: " << body[0].x << " " << body[0].y << endl;
        cout <<"Food: " << foodPos.x << " " << foodPos.y << endl;

        if (Vector2Equals(foodPos, Vector2Add(body[0], direction))) {
            body.push_front(Vector2Add(body[0], direction));
        } else {
            body.push_front(Vector2Add(body[0], direction));
            body.pop_back();
        }
        if (body[0].x > static_cast<float>(cellCount - 1)) {
            body[0].x = 0;
        }
        if (body[0].x < 0) {
            body[0].x = static_cast<float>(cellCount - 1);
        }
        if (body[0].y > static_cast<float>(cellCount - 1)) {
            body[0].y = 0;
        }
        if (body[0].y < 0) {
            body[0].y = static_cast<float>(cellCount - 1);
        }
    }
};


class Food {
public:
    Vector2 position{};


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
    static Vector2 GenerateRandomCell() {
        const int x = GetRandomValue(0, cellCount - 1);
        const int y = GetRandomValue(0, cellCount - 1);

        return Vector2{static_cast<float>(x), static_cast<float>(y)};
    }

    static Vector2 GenerateRandomPos(const deque<Vector2> &snakeBody) {
        Vector2 pos = GenerateRandomCell();
        while (elementInDeque(pos, snakeBody)) {
            pos = GenerateRandomCell();
        }
        return pos;
    }
};


class Game {
public:
    Snake snake;
    Food food;

    Game() {
        snake = Snake{};
        food = Food{};
        // food.position = Food::GenerateRandomPos(snake.body);
    }

    void Draw() {
        food.Draw();
        snake.Draw();
    }

    void Update() {
        const auto foodPos = food.position;
        this->checkSnakeEatable();
        snake.Update(foodPos);
    }

    void checkSnakeEatable() {
        if (Vector2Equals(Vector2Add(snake.body[0], snake.direction), food.position)) {
            cout << "Snake is eating" << endl;
            food.position = Food::GenerateRandomPos(snake.body);
        }
    }
};

using namespace std;

int main() {
    // SetRandomSeed(time(nullptr));
    cout << "Starting the game" << endl;

    auto game = Game{};

    // Create entry screen.
    InitWindow(cellSize * cellCount + 2 * offset, cellSize * cellCount + 2 * offset, WINDOW_TITLE);
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

        DrawRectangleLinesEx(Rectangle{
                                 (float) offset - 5, (float) offset - 5, (float) cellSize * cellCount + 10,
                                 (float) cellSize * cellCount + 10
                             }, 5,
                             darkGreen);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
