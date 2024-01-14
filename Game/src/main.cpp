#include "raylib.h"
#include <set>
#include <unordered_map>
#include <typeinfo>

struct Vector2Comparator {
    bool operator()(const Vector2& v1, const Vector2& v2) const {
        return (v1.x < v2.x) || ((v1.x == v2.x) && (v1.y < v2.y));
    }
};

class Component {
public:
    virtual ~Component() = default;
};

struct Position : public Component {
    float x, y, z;
};

struct Size : public Component {
    float width, height, depth;
};

struct ColorComponent : public Component {
    Color color;
};

class Entity {
public:
    std::unordered_map<std::size_t, Component*> components;

    ~Entity() {
        for (auto& pair : components) {
            delete pair.second;
        }
    }
};

class System {
public:
    virtual void Update(Entity& entity) = 0;
    virtual ~System() = default;
};

class PhysicsSystem : public System {
public:
    std::set<Entity*> _entities;

    void Update(Entity& entity) override {
        auto& positionComponent = *static_cast<Position*>(entity.components[typeid(Position).hash_code()]);
    }
};

class ColorSystem : public System {
public:
    std::set<Entity*> _entities;

    void Update(Entity& entity) override {
        auto& colorComponent = *static_cast<ColorComponent*>(entity.components[typeid(ColorComponent).hash_code()]);
    }
};

class Coordinator {
public:
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, Component*>> entityComponents;
    std::unordered_map<std::size_t, System*> systems;

    template <typename T>
    void RegisterComponent() {
        std::size_t componentType = typeid(T).hash_code();
        entityComponents[componentType] = std::unordered_map<std::size_t, Component*>();
    }

    template <typename T>
    T& AddComponent(Entity& entity, T component) {
        std::size_t componentType = typeid(T).hash_code();
        entity.components[componentType] = new T(std::move(component));
        return *static_cast<T*>(entity.components[componentType]);
    }

    template <typename T>
    System* RegisterSystem() {
        std::size_t systemType = typeid(T).hash_code();
        systems[systemType] = new T();
        return systems[systemType];
    }
};

class Game {
public:
    Coordinator coordinator;
    System* physicsSystem;
    System* colorSystem;
    Entity* currentPlayerEntity;

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

    std::set<Vector2, Vector2Comparator> redSquarePositions;

    bool isMenuActive;
    Rectangle startButton;

    Game() : isMenuActive(true) {
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

    ~Game() {
        delete currentPlayerEntity;
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
    void UpdateMenu() {
        if (CheckCollisionPointRec(GetMousePosition(), startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isMenuActive = false;
        }
    }

    void Update() {
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

        DrawCubeV(player1.position, player1.size, player1.color);
        DrawCubeV(player2.position, player2.size, player2.color);

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
#include <iostream>

int main() {
    std::cout << "Starting the game..." << std::endl;

    InitWindow(1800, 600, "My 3D Game");

    Game game;
    game.Run();

    CloseWindow();

    std::cout << "Exiting the game..." << std::endl;

    return 0;
}
