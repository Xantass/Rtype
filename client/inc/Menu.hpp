/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include "Graphic.hpp"

class Menu {
    public:
        std::string action = "";
        std::string _host;
        std::string _port;
        std::string _name;
        std::string _nbPlayer;
        std::vector<std::vector<std::string>> _roomList;
        int page = 0;
        Menu(std::string host, std::string port, std::string name) : _host(host), _port(port), _name(name), _nbPlayer("4") {}
        ~Menu() {}
        void displayMenu(void) {
            if (Graphic::isKeyPressed(KEY_TAB)) {
                action = "";
            }
            if (action == "<") {
                page = page == 0 ? 0 : page - 1;
                action = "Join Room";
            } else if (action == ">") {
                page += 1;
                action = "Join Room";
            }
            if (action == "") {
                displayButton({760, 460}, {400, 80}, "Create Room", true);
                displayButton({760, 620}, {400, 80}, "Join Room", true);
            } else if (action == "Create Room") {
                createRoom();
            } else if (action == "Join Room") {
                displayJoinable();
            }
        }
        void displayJoinable(void) {
            getRoomList();
            int padding = 120;
            int i = 0;
            std::size_t startIdx = 4 * page;
            std::size_t endIdx = std::min(static_cast<std::size_t>(4 * (page + 1) - 1), _roomList.size() - 1);

            std::vector<std::vector<std::string>> subVector;
            subVector.insert(subVector.end(), _roomList.begin() + startIdx, _roomList.begin() + endIdx + 1);
            for (auto room : subVector) {
                displayButton({760, static_cast<float>(320 + padding * i)}, {310, 80}, room[1], true);
                displayButton({1080, static_cast<float>(320 + padding * i)}, {80, 80}, room[2], false);
                i += 1;
            }

            displayButton({900, 800}, {50, 50}, "<", true);
            if (subVector.size() == 4 && _roomList.size() % 4 != 0)
                displayButton({970, 800}, {50, 50}, ">", true);
            else
                displayButton({970, 800}, {50, 50}, ">", false);
        }
        void createRoom(void) {
            displayTextInput({760, 380}, {400, 80}, _host);
            displayTextInput({760, 500}, {400, 80}, _port);
            displayTextInput({760, 620}, {400, 80}, _name);
            displayTextInput({760, 740}, {180, 80}, _nbPlayer);
            displayButton({980, 740}, {180, 80}, "Launch Game", true);
        }
    protected:
    private:
        void displayTextInput(Vector2 pos, Vector2 size, std::string &text) {
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
        void displayButton(Vector2 pos, Vector2 size, std::string text, bool clickable) {
            Graphic::drawRectangle(pos.x, pos.y, size.x, size.y, LIGHTGRAY);
            Graphic::drawRectangleLines(pos.x, pos.y, size.x, size.y, GRAY);

            int textHeight = 20;
            int textWidth = Graphic::measureText(text.c_str(), textHeight);

            int textX = static_cast<int>(pos.x + (size.x - textWidth) / 2);
            int textY = static_cast<int>(pos.y + (size.y - textHeight) / 2);
            Graphic::drawText(text.c_str(), textX, textY, 20, DARKGRAY);

            if (clickable) {
                Vector2 mousePosition = Graphic::getMousePosition();
                bool selected = Graphic::checkCollisionPointRec(mousePosition.x, mousePosition.y, pos.x, pos.y, size.x, size.y);

                if (selected && Graphic::isMouseButtonPressed())
                    this->action = text;
            }
        }
        void getRoomList(void) {
            _roomList.clear();
            std::ifstream input("room.txt");

            if (!input) {
                std::cerr << "Error opening file." << std::endl;
                return;
            }
            std::string header;
            std::getline(input, header);

            while (std::getline(input, header)) {
                std::istringstream iss(header);
                std::string token;
                std::vector<std::string> room;
                while (iss >> token) {
                    room.push_back(token);
                }
                _roomList.push_back(room);
                room.clear();
            }
            input.close();
        }
};

#endif /* !MENU_HPP_ */
