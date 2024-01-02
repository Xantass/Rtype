/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <iostream>
#include "Graphic.hpp"

class Menu {
    public:
        std::string action = "";
        std::string _host;
        std::string _port;
        std::string _name;
        std::string _nbPlayer;
        Menu(std::string host, std::string port, std::string name) : _host(host), _port(port), _name(name), _nbPlayer("4") {}
        ~Menu() {}
        void displayMenu(void) {
            if (action == "") {
                displayButton({760, 460}, {400, 80}, "Create Room");
                displayButton({760, 620}, {400, 80}, "Join Room");
            } else if (action == "Create Room") {
                createRoom();
            } else if (action == "Join Room") {
                return;
            }
        }
        void displayJoinable(void) {
            return;
        }
        void createRoom(void) {
            displayTextInput({760, 380}, {400, 80}, _host);
            displayTextInput({760, 500}, {400, 80}, _port);
            displayTextInput({760, 620}, {400, 80}, _name);
            displayTextInput({760, 740}, {180, 80}, _nbPlayer);
            displayButton({980, 740}, {180, 80}, "Launch Game");
        }
    protected:
    private:
        static void displayTextInput(Vector2 pos, Vector2 size, std::string &text) {
            Graphic::drawRectangle(pos.x, pos.y, size.x, size.y, LIGHTGRAY);
            Graphic::drawRectangleLines(pos.x, pos.y, size.x, size.y, GRAY);

            int textHeight = 20;
            int textWidth = Graphic::measureText(text.c_str(), textHeight);

            int textX = static_cast<int>(pos.x + (size.x - textWidth) / 2);
            int textY = static_cast<int>(pos.y + (size.y - textHeight) / 2);
            Graphic::drawText(text.c_str(), textX, textY, 20, DARKGRAY);
            Vector2 mousePosition = Graphic::getMousePosition();
            bool selected = Graphic::checkCollisionPointRec(mousePosition.x, mousePosition.y, pos.x, pos.y, size.x, size.y);

            if (selected) {
                int key = Graphic::getCharPressed();
                if ((key >= 32) && (key <= 125) && text.length() < 20) {
                    text += static_cast<char>(key);
                }

                if (Graphic::isKeyPressed(KEY_BACKSPACE) && text.length() > 0) {
                    text.pop_back();
                }
            }
        }
        void displayButton(Vector2 pos, Vector2 size, std::string text) {
            Graphic::drawRectangle(pos.x, pos.y, size.x, size.y, LIGHTGRAY);
            Graphic::drawRectangleLines(pos.x, pos.y, size.x, size.y, GRAY);

            int textHeight = 20;
            int textWidth = Graphic::measureText(text.c_str(), textHeight);

            int textX = static_cast<int>(pos.x + (size.x - textWidth) / 2);
            int textY = static_cast<int>(pos.y + (size.y - textHeight) / 2);
            Graphic::drawText(text.c_str(), textX, textY, 20, DARKGRAY);
            Vector2 mousePosition = Graphic::getMousePosition();
            bool selected = Graphic::checkCollisionPointRec(mousePosition.x, mousePosition.y, pos.x, pos.y, size.x, size.y);

            if (selected && Graphic::isMouseButtonPressed()) {
                this->action = text;
            }
        }
};

#endif /* !MENU_HPP_ */
