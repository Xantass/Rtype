#include "raylib.h"

class Game {
public:
    Game() {
        InitWindow(800, 600, "Mon Jeu 3D");
        camera = { 0 };
        camera.position = { 0.0f, 10.0f, 10.0f };
        camera.target = { 0.0f, 0.0f, 0.0f };
        camera.up = { 0.0f, 1.0f, 0.0f };
        camera.fovy = 45.0f;
    }

    ~Game() {
        CloseWindow();
    }

    void Run() {
        while (!WindowShouldClose()) {
            Update();
            Draw();
        }
    }

private:
    Camera3D camera;

    void Update() {
        // Update your game logic here if needed
    }

    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw the first cube
        DrawCube({ -2.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);

        // Draw the second cube
        DrawCube({ 2.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, BLUE);

        EndMode3D();

        EndDrawing();
    }
};

int main() {
    Game game;
    game.Run();

    return 0;
}
