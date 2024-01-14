#include "Game.h"

template <typename T>
void Coordinator::RegisterComponent() {
    std::size_t componentType = typeid(T).hash_code();
    entityComponents[componentType] = std::unordered_map<std::size_t, Component*>();
}

template <typename T>
T& Coordinator::AddComponent(Entity& entity, T component) {
    std::size_t componentType = typeid(T).hash_code();
    entity.components[componentType] = new T(std::move(component));
    return *static_cast<T*>(entity.components[componentType]);
}

Game::Game() : isMenuActive(true) {
    currentPlayerEntity = new Entity();

    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<ColorComponent>();

    physicsSystem = coordinator.RegisterSystem<PhysicsSystem>();
    colorSystem = coordinator.RegisterSystem<ColorSystem>();

    auto& positionComponent = coordinator.AddComponent(*currentPlayerEntity, Position{});
    auto& colorComponent = coordinator.AddComponent(*currentPlayerEntity, ColorComponent{});

    camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };

    player1.size = { 1.0f, 1.0f, 1.0f };
    player2.size = { 1.0f, 1.0f, 1.0f };

    startButton = { static_cast<float>(GetScreenWidth() / 2 - 80), static_cast<float>(GetScreenHeight() / 2 - 40), 160, 80 };

    currentPlayer = &player1;

    SetTargetFPS(60);
}

Game::~Game() {
    delete currentPlayerEntity;
}

void Game::Run() {
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

void Game::UpdateMenu() {
    if (CheckCollisionPointRec(GetMousePosition(), startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isMenuActive = false;
    }
}

void Game::Update() {
        if (IsKeyDown(KEY_RIGHT)) camera.position.x += 0.2f;
        else if (IsKeyDown(KEY_LEFT)) camera.position.x -= 0.2f;
        else if (IsKeyDown(KEY_DOWN)) camera.position.z += 0.2f;
        else if (IsKeyDown(KEY_UP)) camera.position.z -= 0.2f;

        if (IsKeyPressed(KEY_TAB)) {
            currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
        }

        if (IsKeyDown(KEY_A)) currentPlayer->position.x -= 0.2f;
        else if (IsKeyDown(KEY_D)) currentPlayer->position.x += 0.2f;
        else if (IsKeyDown(KEY_S)) currentPlayer->position.z += 0.2f;
        else if (IsKeyDown(KEY_W)) currentPlayer->position.z -= 0.2f;

        collision1 = CheckCollisionWithRedSquare(player1);
        collision2 = CheckCollisionWithRedSquare(player2);

        UpdatePlayerColorsV2();}

bool Game::CheckCollisionWithRedSquare(Player& player) {
        int gridX = static_cast<int>((player.position.x + 4.0f) / 2.0f);
        int gridZ = static_cast<int>((player.position.z + 4.0f) / 2.0f);

        return redSquarePositions.find({ static_cast<float>(gridX), static_cast<float>(gridZ) }) != redSquarePositions.end();
   }

void Game::UpdatePlayerColorsV2() {
    int gridXPlayer1 = static_cast<int>((player1.position.x + 4.0f) / 2.0f);
        int gridZPlayer1 = static_cast<int>((player1.position.z + 4.0f) / 2.0f);

        int gridXPlayer2 = static_cast<int>((player2.position.x + 4.0f) / 2.0f);
        int gridZPlayer2 = static_cast<int>((player2.position.z + 4.0f) / 2.0f);

        player1.color = (redSquarePositions.find({ static_cast<float>(gridXPlayer1), static_cast<float>(gridZPlayer1) }) != redSquarePositions.end()) ? BLUE : GREEN;
        player2.color = (redSquarePositions.find({ static_cast<float>(gridXPlayer2), static_cast<float>(gridZPlayer2) }) != redSquarePositions.end()) ? BLUE : GREEN;
    }

void Game::Draw() {
  BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawCubeV(player1.position, player1.size, player1.color);
        DrawCubeV(player2.position, player2.size, player2.color);

        DrawChessboard();

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();}

void Game::DrawChessboard() {
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
        }}

void Game::DrawMenu() {
        BeginDrawing();
        DrawRectangleRec(startButton, DARKGRAY);
        DrawText("Start", startButton.x + 10, startButton.y + 10, 20, RAYWHITE);
        EndDrawing();}
