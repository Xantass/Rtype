#include "raylib.h"
#include <set>

struct Vector2Comparator {
    bool operator()(const Vector2& a, const Vector2& b) const {
        return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
    }
};

class Game {
public:
    Game() {
        InitWindow(1200, 800, "Mon Jeu 3D");
        camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

        player1.position = { -2.0f, 1.0f, 2.0f };
        player1.size = { 1.0f, 2.0f, 1.0f };
        player1.color = GREEN;

        player2.position = { 2.0f, 1.0f, 2.0f };
        player2.size = { 1.0f, 2.0f, 1.0f };
        player2.color = GREEN;

        collision1 = false;
        collision2 = false;

        currentPlayer = &player1;

        SetTargetFPS(60);

        // Ajout du menu
        isMenuActive = true;
        startButton = { 10, 10, 120, 40 };
    }

    ~Game() {
        CloseWindow();
    }

    void Run() {
        while (!WindowShouldClose()) {
            if (isMenuActive) {
                UpdateMenu();
                DrawMenu();
            } else {
                Update();
                Draw();
            }
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

    bool collision1;
    bool collision2;

    Player* currentPlayer;

    // Utilisez le comparateur personnalisé pour l'ensemble
    std::set<Vector2, Vector2Comparator> redSquarePositions;

    // Variables pour le menu
    bool isMenuActive;
    Rectangle startButton;

    void UpdateMenu() {
        if (CheckCollisionPointRec(GetMousePosition(), startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isMenuActive = false;
        }
    }

    void Update() {
        // Camera movement
        if (IsKeyDown(KEY_RIGHT)) camera.position.x += 0.2f;
        else if (IsKeyDown(KEY_LEFT)) camera.position.x -= 0.2f;
        else if (IsKeyDown(KEY_DOWN)) camera.position.z += 0.2f;
        else if (IsKeyDown(KEY_UP)) camera.position.z -= 0.2f;

        // Player switching
        if (IsKeyPressed(KEY_TAB)) {
            currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
        }

        // Player movement
        if (IsKeyDown(KEY_A)) currentPlayer->position.x -= 0.2f;
        else if (IsKeyDown(KEY_D)) currentPlayer->position.x += 0.2f;
        else if (IsKeyDown(KEY_S)) currentPlayer->position.z += 0.2f;
        else if (IsKeyDown(KEY_W)) currentPlayer->position.z -= 0.2f;

        collision1 = CheckCollisionWithRedSquare(player1);
        collision2 = CheckCollisionWithRedSquare(player2);

        UpdatePlayerColorsV2();
    }

    bool CheckCollisionWithRedSquare(Player& player) {
        int gridX = static_cast<int>((player.position.x + 4.0f) / 2.0f);  
        int gridZ = static_cast<int>((player.position.z + 4.0f) / 2.0f);  

        return redSquarePositions.find({ static_cast<float>(gridX), static_cast<float>(gridZ) }) != redSquarePositions.end();
    }

    void UpdatePlayerColorsV2() {
        int gridXPlayer1 = static_cast<int>((player1.position.x + 4.0f) / 2.0f);
        int gridZPlayer1 = static_cast<int>((player1.position.z + 4.0f) / 2.0f);

        int gridXPlayer2 = static_cast<int>((player2.position.x + 4.0f) / 2.0f);
        int gridZPlayer2 = static_cast<int>((player2.position.z + 4.0f) / 2.0f);

        player1.color = (redSquarePositions.find({ static_cast<float>(gridXPlayer1), static_cast<float>(gridZPlayer1) }) != redSquarePositions.end()) ? BLUE : GREEN;
        player2.color = (redSquarePositions.find({ static_cast<float>(gridXPlayer2), static_cast<float>(gridZPlayer2) }) != redSquarePositions.end()) ? BLUE : GREEN;
    }

    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawCubeV(player1.position, player1.size, GREEN );
        DrawCubeV(player2.position, player2.size, BLACK);

        DrawChessboard();

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    void DrawChessboard() {
        for (int i = -4; i <= 4; i++) {
            for (int j = -4; j <= 4; j++) {
                Vector3 squarePosition = { static_cast<float>(i) * 2.0f, 0.0f, static_cast<float>(j) * 2.0f };
                Color squareColor = ((i + j) % 2 == 0) ? GOLD : BLACK;

                if (i == 1 && j == 2) {
                    squareColor = RED;
                    redSquarePositions.insert({ squarePosition.x, squarePosition.z });
                }
                if (i == 3 && j == -1) {
                    squareColor = RED;
                    redSquarePositions.insert({ squarePosition.x, squarePosition.z });
                }

                DrawCube(squarePosition, 2.0f, 0.1f, 2.0f, squareColor);
            }
        }
    }

    void DrawMenu() {
        BeginDrawing();
        DrawRectangleRec(startButton, DARKGRAY);
        DrawText("Start", startButton.x + 10, startButton.y + 10, 20, RAYWHITE);
        EndDrawing();
    }
};

int main() {
    Game game;
    game.Run();

    return 0;
}
