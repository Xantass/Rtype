// entity.h
#pragma once

#include "raylib.h"
#include "components.h"

class Entity {
public:
    TransformComponent transform;
    RenderComponent render;
};
