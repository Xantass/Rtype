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
            return LoadTexture(path.c_str());
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
        /**
         * @brief Draw a rectangle
         *
         * @param x
         * @param y
         * @param width
         * @param height
         * @param color
         */
        static void drawRectangle(int x, int y, int width, int height, Color color) {
            DrawRectangle(x, y, width, height, color);
        }
        /**
         * @brief Draw rectangle lines
         *
         * @param x
         * @param y
         * @param width
         * @param height
         * @param color
         */
        static void drawRectangleLines(int x, int y, int width, int height, Color color) {
            DrawRectangleLines(x, y, width, height, color);
        }
        /**
         * @brief Check if a point and a rect intersects
         *
         * @param xP
         * @param yP
         * @param xR
         * @param yR
         * @param width
         * @param height
         * @return true
         * @return false
         */
        static bool checkCollisionPointRec(float xP, float yP, float xR, float yR, float width, float height) {
            return CheckCollisionPointRec({xP, yP}, {xR, yR, width, height});
        }
        /**
         * @brief Get the Mouse Position object
         *
         * @return Vector2
         */
        static Vector2 getMousePosition(void) {
            return GetMousePosition();
        }
        /**
         * @brief Check if left mouse button is pressed
         *
         * @return true
         * @return false
         */
        static bool isMouseButtonPressed(void) {
            return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        }
        /**
         * @brief Measure display size of text
         *
         * @param text
         * @param fontSize
         * @return int
         */
        static int measureText(std::string text, int fontSize) {
            return MeasureText(text.c_str(), fontSize);
        }
        /**
         * @brief Draw text
         *
         * @param text
         * @param posX
         * @param posY
         * @param fontSize
         * @param color
         */
        static void drawText(std::string text, int posX, int posY, int fontSize, Color color) {
            return DrawText(text.c_str(), posX, posY, fontSize, color);
        }
        /**
         * @brief Get the Char pressed on keyboard
         *
         * @return int
         */
        static int getCharPressed(void) {
            return GetCharPressed();
        }
        /**
         * @brief Check if a key is pressed
         *
         * @param key
         * @return true
         * @return false
         */
        static bool isKeyPressed(int key) {
            return IsKeyPressed(key);
        }
        /**
         * @brief Check if a key is released
         *
         * @param key
         * @return true
         * @return false
         */
        static bool isKeyReleased(int key) {
            return IsKeyReleased(key);
        }
        /**
         * @brief Toggle fullscreen
         *
         */
        static void toggleFullScreen(void) {
            ToggleFullscreen();
        }
        /**
         * @brief Get the FPS
         *
         * @return int
         */
        static int getFPS(void) {
            return GetFPS();
        }
        /**
         * @brief Check if left mouse button is currently down
         *
         * @return true
         * @return false
         */
        static bool isMouseButtonDown(void) {
            return IsMouseButtonDown(0);
        }
        /**
         * @brief Set the volume of Music object
         *
         * @param music
         * @param volume
         */
        static void setMusicVolume(Music music, float volume) {
            SetMusicVolume(music, volume);
        }
};

#endif /* !GRAPHIC_HPP_ */
