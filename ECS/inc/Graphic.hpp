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
#include "raylib.h"


class Graphic {
    public:
        static void initWindow(int width, int height, std::string title) {
            InitWindow(width, height, title.c_str());
        }
        static void closeWindow(void) {
            CloseWindow();
        }
        static bool shouldCloseWindow(void) {
            return WindowShouldClose();
        }
        static void beginDrawing(void) {
            BeginDrawing();
        }
        static void endDrawing(void) {
            EndDrawing();
        }
        static void clearBackground(Color color) {
            ClearBackground(color);
        }
        static void drawTexture(Texture texture, int posX, int posY, Color color) {
            DrawTexture(texture, posX, posY, color);
        }
        static bool isKeyDown(int key) {
            return IsKeyDown(key);
        }
        static bool isKeyUp(int key) {
            return IsKeyUp(key);
        }
};

#endif /* !GRAPHIC_HPP_ */
