/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Parallax
*/

/**
 * @file Parallax.hpp
 * @brief This is the file for the Parallax class
 *
 */
#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <filesystem>
#include "Graphic.hpp"

/**
 * @brief This is the Parallax class
 *
 */
class Parallax {
    public:
        /**
         * @brief Construct a new Parallax object
         *
         * @param pathToAssets
         */
        Parallax(std::string pathToAssets);
        /**
         * @brief Destroy the Parallax object
         *
         */
        ~Parallax();
        /**
         * @brief Draw all textures of the parallax
         *
         */
        void draw(void);

    protected:
    private:
        std::vector<std::tuple<Texture2D, float>> _textureList;
        std::string _path;
        /**
         * @brief Load all textures from parameter
         *
         * @param paths
         */
        void loadTextures(std::vector<std::string> paths);
        /**
         * @brief Get all files in folder
         *
         * @return std::vector<std::string>
         */
        std::vector<std::string> getAllFiles(void);
        /**
         * @brief Update the position of the textures
         *
         */
        void update(void);
};

#endif /* !PARALLAX_HPP_ */
