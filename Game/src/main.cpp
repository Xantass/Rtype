/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** main
*/

#include "raylib.h"

class Game {
public:
    Game() {
        InitWindow(800, 450, "Mon Jeu 3D");
        camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

        // Player 1 setup
        player1.position = { -2.0f, 1.0f, 2.0f };
        player1.size = { 1.0f, 2.0f, 1.0f };
        player1.color = GREEN;

        // Player 2 setup
        player2.position = { 2.0f, 1.0f, 2.0f };
        player2.size = { 1.0f, 2.0f, 1.0f };
        player2.color = BLUE;

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

        // Check collisions player 1 vs enemy-box
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ player1.position.x - player1.size.x / 2,
                                     player1.position.y - player1.size.y / 2,
                                     player1.position.z - player1.size.z / 2 },
                          (Vector3){ player1.position.x + player1.size.x / 2,
                                     player1.position.y + player1.size.y / 2,
                                     player1.position.z + player1.size.z / 2 }},
            (BoundingBox){(Vector3){ enemyBoxPos.x - enemyBoxSize.x / 2,
                                     enemyBoxPos.y - enemyBoxSize.y / 2,
                                     enemyBoxPos.z - enemyBoxSize.z / 2 },
                          (Vector3){ enemyBoxPos.x + enemyBoxSize.x / 2,
                                     enemyBoxPos.y + enemyBoxSize.y / 2,
                                     enemyBoxPos.z + enemyBoxSize.z / 2 }})) collision1 = true;

        // Check collisions player 2 vs enemy-box
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ player2.position.x - player2.size.x / 2,
                                     player2.position.y - player2.size.y / 2,
                                     player2.position.z - player2.size.z / 2 },
                          (Vector3){ player2.position.x + player2.size.x / 2,
                                     player2.position.y + player2.size.y / 2,
                                     player2.position.z + player2.size.z / 2 }},
            (BoundingBox){(Vector3){ enemyBoxPos.x - enemyBoxSize.x / 2,
                                     enemyBoxPos.y - enemyBoxSize.y / 2,
                                     enemyBoxPos.z - enemyBoxSize.z / 2 },
                          (Vector3){ enemyBoxPos.x + enemyBoxSize.x / 2,
                                     enemyBoxPos.y + enemyBoxSize.y / 2,
                                     enemyBoxPos.z + enemyBoxSize.z / 2 }})) collision2 = true;

        // Check collisions player 1 vs enemy-sphere
        if (CheckCollisionBoxSphere(
            (BoundingBox){(Vector3){ player1.position.x - player1.size.x / 2,
                                     player1.position.y - player1.size.y / 2,
                                     player1.position.z - player1.size.z / 2 },
                          (Vector3){ player1.position.x + player1.size.x / 2,
                                     player1.position.y + player1.size.y / 2,
                                     player1.position.z + player1.size.z / 2 }},
            enemySpherePos, enemySphereSize)) collision1 = true;

        // Check collisions player 2 vs enemy-sphere
        if (CheckCollisionBoxSphere(
            (BoundingBox){(Vector3){ player2.position.x - player2.size.x / 2,
                                     player2.position.y - player2.size.y / 2,
                                     player2.position.z - player2.size.z / 2 },
                          (Vector3){ player2.position.x + player2.size.x / 2,
                                     player2.position.y + player2.size.y / 2,
                                     player2.position.z + player2.size.z / 2 }},
            enemySpherePos, enemySphereSize)) collision2 = true;
    }

    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw player 1
        DrawCubeV(player1.position, player1.size, (collision1) ? RED : player1.color);

        // Draw player 2
        DrawCubeV(player2.position, player2.size, (collision2) ? RED : player2.color);

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }
};

int main() {
    Game game;
    game.Run();

    return 0;
}
