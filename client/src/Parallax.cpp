/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Parallax
*/

#include "Parallax.hpp"

Parallax::Parallax(std::string pathToAssets) : _path(pathToAssets)
{
    loadTextures(getAllFiles());
}

Parallax::~Parallax()
{
}

void Parallax::loadTextures(std::vector<std::string> paths)
{
    for (auto path : paths) {
        try {
            _textureList.push_back(std::make_tuple(LoadTexture(path.c_str()), 1920));
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

std::vector<std::string> Parallax::getAllFiles(void)
{
    std::vector<std::string> paths;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(_path)) {
            if (std::filesystem::is_regular_file(entry.path())) {
                paths.push_back(entry.path().string());
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return paths;
}

void Parallax::update(void)
{
    float speed = 1.8;

    for (auto &tuple : _textureList) {
        const Texture2D& texture = std::get<0>(tuple);
        if (std::get<1>(tuple) - speed + texture.width < 0)
            tuple = std::make_tuple(texture, 1920 - speed);
        else
            tuple = std::make_tuple(texture, std::get<1>(tuple) - speed);
        speed *= 1.3;
    }
}

void Parallax::draw(void)
{
    update();
    for (auto tuple : _textureList) {
        Graphic::drawTexture(std::get<0>(tuple), std::get<1>(tuple), 0, RWHITE);
    }
}