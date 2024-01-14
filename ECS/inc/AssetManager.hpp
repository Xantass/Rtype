/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** AssetManager
*/

#ifndef ASSETMANAGER_HPP_
#define ASSETMANAGER_HPP_

#include <iostream>
#include <map>
#include <fstream>
#include <filesystem>
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

    /**
     * @brief Loads a texture from Base64-encoded data and associates it with a specified index.
     * @param base64 The Base64-encoded texture data.
     * @param path The path to the texture file (for reference).
     * @param index The index to associate with the loaded texture.
     */
    void LoadTexture(std::string base64, std::string path, int index);

    /**
     * @brief Map associating indices to texture paths.
     * 
     * This map stores the association between texture indices and their respective paths.
     */
    std::map<int, std::string> _sprite;

protected:
private:
    /**
     * @brief Unordered map associating texture names to Texture objects.
     * 
     * This unordered map stores the association between texture names and their respective Texture objects.
     */
    std::unordered_map<std::string, Texture> _sprites;
};

#include "../../src/AssetManager.cpp"

#endif /* !ASSETMANAGER_HPP_ */
