/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <algorithm>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include "Graphic.hpp"
#include "Coordinator.hpp"

class Menu {
    public:
        Music _music = Graphic::loadMusic("assets/Theme.mp3");
        Texture2D settings;
        std::string action = "";
        std::string _host;
        std::string _port;
        std::string _name;
        std::string _pathSprite;
        std::string _nbPlayer;
        std::string _errorLoad;
        std::string _errorSelectSprite;
        std::string _errorSelectEnnemy;
        std::string _errorSelectBullet;
        int _selectSprite = -1;
        int _selectBullet = -1;
        int _selectEnnemyBullet = -1;
        int _selectEnnemy = -1;
        int _selectEnnemyTwo = -1;
        int _selectEnnemyElite = -1;
        int _selectEnnemyBoss = -1;
        std::vector<std::vector<std::string>> _roomList;
        Coordinator &_coordinator;
        int page = 0;
        std::string _settingsState = "";
        float volume = 1;
        Menu(std::string host, std::string port, std::string name, Coordinator &coordinator) : settings(Graphic::loadTexture("assets/settings.png")), _host(host), _port(port), _name(name), _nbPlayer("4"), _coordinator(coordinator)  {Graphic::playMusic(_music);}
        ~Menu() {Graphic::unloadMusic(_music);}
        void displayMenu(AssetManager &assetManager) {
            if (Graphic::isKeyPressed(KEY_TAB)) {
                if (action == "Select Ennemy" || action == "Select Bullet" || action == "Select Second Ennemy" || action == "Select Elite Ennemy" || action == "Select Boss Ennemy" || action == "Select Ennemy Bullet") {
                    action = "Create Room";
                } else {
                    action = "";
                    _errorLoad = "";
                    _errorSelectBullet = "";
                    _errorSelectEnnemy = "";
                    _errorSelectSprite = "";
                    _selectBullet = -1;
                    _selectEnnemyBullet = -1;
                    _selectEnnemy = -1;
                    _selectEnnemyTwo = -1;
                    _selectEnnemyElite = -1;
                    _selectEnnemyBoss = -1;
                }
            }
            if (action == "<") {
                page = page == 0 ? 0 : page - 1;
                action = "Join Room";
            } else if (action == ">") {
                page += 1;
                action = "Join Room";
            }
            if (action == "") {
                displayButton({760, 300}, {400, 80}, "Load Sprite", true);
                displayButton({760, 460}, {400, 80}, "Select Sprite", true);
                displayButton({760, 620}, {400, 80}, "Create Room", true);
                displayButton({760, 780}, {400, 80}, "Join Room", true);
            } else if (action == "Create Room") {
                createRoom();
            } else if (action == "Join Room") {
                displayJoinable();
            } else if (action == "Load Sprite") {
                displayLoadSprite();
            } else if (action == "Select Sprite") {
                displaySelectSprite(assetManager, _selectSprite);
            } else if (action == "Select Ennemy") {
                displaySelectSprite(assetManager, _selectEnnemy);
            } else if (action == "Select Bullet") {
                displaySelectSprite(assetManager, _selectBullet);
            } else if (action == "Select Second Ennemy") {
                displaySelectSprite(assetManager, _selectEnnemyTwo);
            } else if (action == "Select Elite Ennemy") {
                displaySelectSprite(assetManager, _selectEnnemyElite);
            } else if (action == "Select Boss Ennemy") {
                displaySelectSprite(assetManager, _selectEnnemyBoss);
            } else if (action == "Select Ennemy Bullet") {
                displaySelectSprite(assetManager, _selectEnnemyBullet);
            } else {
                for (auto room : _roomList) {
                    if (room[1] == action) {
                        if (_selectSprite == -1) {
                            action = "Join Room";
                            _errorSelectSprite = "Error: Choose your skin for the game";
                            return;
                        }
                        std::vector<std::string> list(3, "");
                        list[0] = _host;
                        list[1] = room[0];
                        list[2] = room[1];
                        std::cout << "select: " << _selectSprite << std::endl;
                        _coordinator.AddEvent(Event{Event::actions::JOIN, 0, {std::make_any<int>(_selectSprite), std::make_any<std::string>(list[0]), std::make_any<std::string>(list[1]), std::make_any<std::string>(list[2]), std::make_any<std::string>("false")}});
                        action = "Game";
                        _errorSelectSprite = "";
                        break;
                    } else if ("Spect.\n" + room[1] == action) {
                        std::vector<std::string> list(3, "");
                        list[0] = _host;
                        list[1] = room[0];
                        list[2] = room[1];
                        _coordinator.AddEvent(Event{Event::actions::JOIN, 0, {std::make_any<int>(_selectSprite), std::make_any<std::string>(list[0]), std::make_any<std::string>(list[1]), std::make_any<std::string>(list[2]), std::make_any<std::string>("true")}});
                        action = "Game";
                        break;
                    }
                }
            }
        }
        void displayJoinable(void) {
            if (_errorSelectSprite != "") {
                displayTextWithBackground(_errorSelectSprite, 800, 100);
            }
            getRoomList();
            std::size_t endIdx;
            if (_roomList.size() == 0) {
                endIdx = -1;
            } else {
                int padding = 120;
                int i = 0;
                std::size_t startIdx = 4 * page;
                endIdx = std::min(static_cast<std::size_t>(4 * (page + 1) - 1), _roomList.size() - 1);

                std::vector<std::vector<std::string>> subVector;
                subVector.insert(subVector.end(), _roomList.begin() + startIdx, _roomList.begin() + endIdx + 1);
                for (auto room : subVector) {
                    displayButton({760, static_cast<float>(320 + padding * i)}, {310, 80}, room[1], true);
                    displayButton({1080, static_cast<float>(320 + padding * i)}, {80, 80}, room[2], false);
                    displayButton({1170, static_cast<float>(320 + padding * i)}, {80, 80}, "Spect.\n" + room[1], true);
                    i += 1;
                }
            }
            displayButton({900, 800}, {50, 50}, "<", true);
            if ((endIdx + 1) != _roomList.size())
                displayButton({970, 800}, {50, 50}, ">", true);
            else
                displayButton({970, 800}, {50, 50}, ">", false);
        }

        void displaySelectSprite(AssetManager &assetManager, int& value) {
            size_t index = 0;
            size_t i = 1;
            float xPos = 600.0f;
            float yPos = 300.0f;
            int heightMax = 0;
            for (auto sprite : assetManager._sprite) {
                Texture tmp = assetManager.LoadTexture(sprite.second);

                DrawTextureRec(tmp, {0, 0, static_cast<float>(tmp.width), static_cast<float>(tmp.height)}, {xPos, yPos}, WHITE);

                if (CheckCollisionPointRec(GetMousePosition(), {xPos, yPos, static_cast<float>(tmp.width), static_cast<float>(tmp.height)})) {
                    DrawRectangleLines(static_cast<int>(xPos), static_cast<int>(yPos), static_cast<float>(tmp.width), static_cast<float>(tmp.height), RED);

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        value = static_cast<int>(index);
                    }
                }
                xPos = xPos + (static_cast<float>(tmp.width) + 100.0f);
                if (heightMax < tmp.height)
                    heightMax = tmp.height;
                if ((i % 4 == 0 && i != 0)) {
                    yPos = yPos + static_cast<float>(heightMax) + 100.0f;
                    xPos = 600.0f;
                    heightMax = 0;
                }
                i++;
                index++;
            }
            xPos = 860.0f;
            yPos = 100.0f;
            if (value != -1) {
                Texture tmp = assetManager.LoadTexture(assetManager._sprite[value]);
                DrawTextureRec(assetManager.LoadTexture(assetManager._sprite[value]), {0, 0, static_cast<float>(tmp.width), static_cast<float>(tmp.height)}, {xPos, yPos}, WHITE);
            }
        }

        void displayLoadSprite(void) {
            if (_errorLoad != "") {
                displayTextWithBackground(_errorLoad, 860, 100);
            }
            displayTextInput({560, 380}, {800, 80}, _pathSprite, 65);
            displayButton({1180, 500}, {180, 80}, "Send Sprite", true);
        }

        void createRoom(void) {
            displayTextInput({760, 20}, {400, 80}, _host, 20);
            displayTextInput({760, 120}, {400, 80}, _port, 20);
            displayTextInput({760, 220}, {400, 80}, _name, 20);
            displayButton({760, 320}, {400, 80}, "Select Bullet", true);
            displayButton({760, 420}, {400, 80}, "Select Ennemy", true);
            displayButton({760, 520}, {400, 80}, "Select Second Ennemy", true);
            displayButton({760, 620}, {400, 80}, "Select Elite Ennemy", true);
            displayButton({760, 720}, {400, 80}, "Select Boss Ennemy", true);
            displayButton({760, 820}, {400, 80}, "Select Ennemy Bullet", true);
            displayTextInput({760, 920}, {180, 80}, _nbPlayer, 20);
            displayButton({980, 920}, {180, 80}, "Launch Game", true);
        }

    protected:
    private:
        void displayTextInput(Vector2 pos, Vector2 size, std::string &text, std::size_t length) {
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
                if ((key >= 32) && (key <= 125) && text.length() < length) {
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
        void displayTextWithBackground(std::string text, int xPos, int yPos) {
            int textHeight = 20;
            int textWidth = Graphic::measureText(text.c_str(), textHeight);

            Graphic::drawRectangle(xPos, yPos, textWidth + 20, textHeight + 20, LIGHTGRAY);
            Graphic::drawRectangleLines(xPos, yPos, textWidth + 20, textHeight + 20, GRAY);
            Graphic::drawText(text.c_str(), xPos + 10, yPos + 10, 20, DARKGRAY);
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
                while (std::getline(iss, token, '\t')) {
                    room.push_back(token);
                }
                _roomList.push_back(room);
                room.clear();
            }
            input.close();
        }
        void displaySettings(void) {
            if (_settingsState == "") {
                Graphic::drawTexture(settings, 1790, 0, RWHITE);
                Vector2 mousePosition = Graphic::getMousePosition();
                if (Graphic::checkCollisionPointRec(mousePosition.x, mousePosition.y, 1790, 0, 150, 100) && Graphic::isMouseButtonPressed()) {
                    _settingsState = "Settings";
                }
            } else if (_settingsState == "Settings") {
                Graphic::drawRectangle(1610, 10, 300, 70, {0, 0, 0, 50});
                Graphic::drawRectangleLines(1610, 10, 300, 70, RWHITE);
                Rectangle sliderBar = { 1660, 35, 200, 20 };
                Rectangle sliderKnob = { sliderBar.x + (sliderBar.width - 20) * volume, sliderBar.y - 10, 20, 40 };
                Vector2 mousePosition = Graphic::getMousePosition();
                bool knobHovered = Graphic::checkCollisionPointRec(mousePosition.x, mousePosition.y, sliderKnob.x, sliderKnob.y, sliderKnob.width, sliderKnob.height);
                if (Graphic::isMouseButtonDown()) {
                    if (knobHovered) {
                        mousePosition = Graphic::getMousePosition();
                        sliderKnob.x = std::clamp(mousePosition.x - sliderKnob.width / 2, sliderBar.x, sliderBar.x + sliderBar.width - sliderKnob.width);
                        float relativeX = sliderKnob.x - sliderBar.x;
                        float normalizedX = relativeX / (sliderBar.width - sliderKnob.width);
                        volume = normalizedX;
                        Graphic::setMusicVolume(_music, volume);
                    }
                }
                if (Graphic::isMouseButtonPressed() && !knobHovered) {
                    _settingsState = "";
                }
                DrawRectangleRec(sliderBar, GRAY);
                DrawRectangleRec(sliderKnob, knobHovered ? DARKGRAY : LIGHTGRAY);
            }
        }
};

#endif /* !MENU_HPP_ */
