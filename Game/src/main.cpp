#include "raylib.h"

class Game {
public:
    Game() {
        InitWindow(1200, 800, "Mon Jeu 3D"); // Agrandissement de la fenêtre
        camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

        // Player 1 setup
        player1.position = { -2.0f, 1.0f, 2.0f };
        player1.size = { 1.0f, 2.0f, 1.0f };
        player1.color = GREEN;

        // Player 2 setup
        player2.position = { 2.0f, 1.0f, 2.0f };
        player2.size = { 1.0f, 2.0f, 1.0f };
        player2.color = GREEN;

        enemyBoxPos = { -4.0f, 1.0f, 0.0f };
        enemyBoxSize = { 2.0f, 2.0f, 2.0f };

        enemySpherePos = { 4.0f, 0.0f, 0.0f };
        enemySphereSize = 1.5f;

        collision1 = false;
        collision2 = false;

        currentPlayer = &player1; // Initial player is player 1

        SetTargetFPS(60);
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
    Camera camera;

    struct Player {
        Vector3 position;
        Vector3 size;
        Color color;
    };

    Player player1;
    Player player2;

    Vector3 enemyBoxPos;
    Vector3 enemyBoxSize;

    Vector3 enemySpherePos;
    float enemySphereSize;

    bool collision1;
    bool collision2;

    Player* currentPlayer;

    void Update() {
        // Switch player with the Tab key
        if (IsKeyPressed(KEY_TAB)) {
            if (currentPlayer == &player1) {
                currentPlayer = &player2;
            } else {
                currentPlayer = &player1;
            }
        }

        // Move the current player
        if (IsKeyDown(KEY_A)) currentPlayer->position.x -= 0.2f;
        else if (IsKeyDown(KEY_D)) currentPlayer->position.x += 0.2f;
        else if (IsKeyDown(KEY_S)) currentPlayer->position.z += 0.2f;
        else if (IsKeyDown(KEY_W)) currentPlayer->position.z -= 0.2f;

        collision1 = false;
        collision2 = false;


    }

    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw player 1
        DrawCubeV(player1.position, player1.size, (collision1) ? RED : player1.color);

        // Draw player 2
        DrawCubeV(player2.position, player2.size, (collision2) ? RED : player2.color);

        // Draw chessboard in the center
        DrawChessboard();

        // Draw planets in the background
        DrawPlanets();

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    void DrawChessboard() {
        for (int i = -4; i <= 4; i++) {
            for (int j = -4; j <= 4; j++) {
                Vector3 squarePosition = { static_cast<float>(i) * 2.0f, 0.0f, static_cast<float>(j) * 2.0f };
                Color squareColor = ((i + j) % 2 == 0) ? WHITE : BLACK;
                DrawCube(squarePosition, 2.0f, 0.1f, 2.0f, squareColor);
            }
        }
    }

    void DrawPlanets() {
        // Draw three planets in the background
        return;
    }
};

int main() {
    Game game;
    game.Run();

    return 0;
}
