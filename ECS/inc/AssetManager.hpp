/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** AssetManager
*/

#ifndef ASSETMANAGER_HPP_
#define ASSETMANAGER_HPP_

#include <iostream>

#include "Graphic.hpp"

class AssetManager {
public:
    AssetManager() {};
    ~AssetManager() {};

    /**
     * @brief Load a texture from a path
     * @details If the texture is already loaded, it will return the texture
     * 
     * @param texturePath Path of the texture
     * @return Texure Texture loaded
     */
    Texture LoadTexture(std::string texturePath);

protected:
private:
    std::unordered_map<std::string, Texture> _sprites;
};

#include "../../src/AssetManager.cpp"

#endif /* !ASSETMANAGER_HPP_ */
