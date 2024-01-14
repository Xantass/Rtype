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

void AssetManager::LoadTexture(std::string base64, std::string path, int index)
{
    if (_sprite.find(index) == _sprite.end()) {
        _sprite[index] = path;
        // std::cout << "_sprite[" << index << "]: " << path << std::endl;
        if (std::filesystem::exists(path) == true) {
            return;
        }
        std::ofstream fichier;

        fichier.open(path, std::ios::app);
        if (fichier.is_open()) {
            fichier << base64;
            fichier.close();
        } else {
            std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
        }
    }
    return;
}