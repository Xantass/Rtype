/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Parallax
*/

#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include <tuple>
#include <vector>
#include <map>
#include <iostream>
#include <filesystem>
#include "Graphic.hpp"

class Parallax {
    public:
        Parallax(std::string pathToAssets);
        ~Parallax();
        void draw(void);

    protected:
    private:
        std::map<std::string, float> _speedMap;
        std::map<std::string, Texture2D> _textureMap;
        std::vector<std::tuple<Texture2D, float>> _textureList;
        std::string _path;
        void loadTextures(std::vector<std::string> paths);
        std::vector<std::string> getAllFiles(void);
        void update(void);
};

#endif /* !PARALLAX_HPP_ */
