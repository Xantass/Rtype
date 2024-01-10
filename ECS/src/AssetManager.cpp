/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** AssetManager
*/

#include "AssetManager.hpp"

Texture AssetManager::LoadTexture(std::string texturePath)
{
    if (_sprites.find(texturePath) == _sprites.end())
        _sprites[texturePath] = Graphic::loadTexture(texturePath.c_str());
    return _sprites[texturePath];
}