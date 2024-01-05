/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Graphic
*/

/**
 * @file Graphic.hpp
 * @brief File containing the Graphic class
 *
 *
 */
#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#define RBLACK Color{0, 0, 0, 0}
#define RWHITE Color{255 ,255, 255, 255}

#include <iostream>
#include <unordered_map>
#include "raylib.h"

inline std::unordered_map<std::string, Texture2D> _textures;

/**
 * @class Graphic
 * @brief Class of the graphic
 *
 */
class Graphic {
    public:
        /**
         * @brief Init the components
         *
         * @param width
         * @param height
         * @param title
         */
        static void init(int width, int height, std::string title) {
            InitWindow(width, height, title.c_str());
            InitAudioDevice();
        }
        /**
         * @brief Close the components
         *
         */
        static void close(void) {
            CloseAudioDevice();
            CloseWindow();
        }
        /**
         * @brief Check if the window should be closed
         *
         * @return true
         * @return false
         */
        static bool shouldCloseWindow(void) {
            return WindowShouldClose();
        }
        /**
         * @brief Start the drawing mode
         *
         */
        static void beginDrawing(void) {
            BeginDrawing();
        }
        /**
         * @brief End the drawing mode
         *
         */
        static void endDrawing(void) {
            EndDrawing();
        }
        /**
         * @brief Clear the background with a color
         *
         * @param color
         */
        static void clearBackground(Color color) {
            ClearBackground(color);
        }
        /**
         * @brief Draw a texture on the window
         *
         * @param texture
         * @param posX
         * @param posY
         * @param color
         */
        static void drawTexture(Texture texture, int posX, int posY, Color color) {
            DrawTexture(texture, posX, posY, color);
        }
        /**
         * @brief Check if a key is currently down
         *
         * @param key
         * @return true
         * @return false
         */
        static bool isKeyDown(int key) {
            return IsKeyDown(key);
        }
        /**
         * @brief Check if a key is currently up
         *
         * @param key
         * @return true
         * @return false
         */
        static bool isKeyUp(int key) {
            return IsKeyUp(key);
        }
        /**
         * @brief Load a texture
         *
         * @param path
         * @return Texture
         */
        static Texture loadTexture(std::string path) {
            // return LoadTexture(path.c_str());
            return _textures[path];
        }
        /**
         * @brief Load a music
         *
         * @param path
         * @return Music
         */
        static Music loadMusic(std::string path) {
            return LoadMusicStream(path.c_str());
        }
        /**
         * @brief Unload a music
         *
         * @param music
         */
        static void unloadMusic(Music music) {
            UnloadMusicStream(music);
        }
        /**
         * @brief Play a music
         *
         * @param music
         */
        static void playMusic(Music music) {
            PlayMusicStream(music);
        }
        /**
         * @brief Update a music
         *
         * @param music
         */
        static void updateMusic(Music music) {
            UpdateMusicStream(music);
        }
};

#endif /* !GRAPHIC_HPP_ */
