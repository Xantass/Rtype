// components.h
#pragma once

#include "raylib.h"

struct TransformComponent {
    Vector3 position;
    Vector3 scale;
};

struct RenderComponent {
    Color color;
};
