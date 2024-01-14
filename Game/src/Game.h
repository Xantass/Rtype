#ifndef GAME_H
#define GAME_H

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
    void RegisterComponent();

    template <typename T>
    T& AddComponent(Entity& entity, T component);

    template <typename T>
    T* RegisterSystem() {
        std::size_t systemType = typeid(T).hash_code();
        systems[systemType] = new T();
        return static_cast<T*>(systems[systemType]);
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

    Game();

    ~Game();

    void Run();

private:
    void UpdateMenu();

    void Update();

    bool CheckCollisionWithRedSquare(Player& player);

    void UpdatePlayerColorsV2();

    void Draw();

    void DrawChessboard();

    void DrawMenu();
};

#endif // GAME_H
