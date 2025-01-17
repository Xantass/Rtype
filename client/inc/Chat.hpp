/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Chat
*/

#ifndef CHAT_HPP_
#define CHAT_HPP_

#include <chrono>
#include <algorithm>
#include <vector>
#include <iostream>
#include "Coordinator.hpp"
#include "Graphic.hpp"

class Chat {
    public:
        Chat(std::string user) {
            _isOpen = false;
            _chat = "";
            _user = user;
            _duration = std::chrono::seconds(2);
            receiveTime = std::chrono::steady_clock::now();
        };
        ~Chat() {

        };

        void displayChatWindow(Coordinator &coordinator) {
            std::queue<Event> eventQueue = coordinator.GetEventQueue();
            // std::cout << "EventSystem, last event: " << event._type << std::endl;

            while (!eventQueue.empty()) {
                Event event = eventQueue.front();
                eventQueue.pop();
                if (event._type == Event::CREATE_MESSAGE) {
                    std::reverse(chatList.begin(), chatList.end());
                    std::pair<std::string, std::string> chat = std::make_pair(std::any_cast<std::string>(event._data.at(0)), std::any_cast<std::string>(event._data.at(1)));
                    chatList.push_back(chat);
                    std::reverse(chatList.begin(), chatList.end());
                    receiveTime = std::chrono::steady_clock::now();
                }
            }
            if (std::chrono::steady_clock::now() - receiveTime < _duration) {
                std::pair<std::string, std::string> chat = chatList[0];
                int nameWidth = Graphic::measureText((std::get<0>(chat) + ": ").c_str(), 20);
                if (std::get<0>(chat) == "System") {
                    Graphic::drawText((std::get<0>(chat) + ": ").c_str(), 60, 925, 20, {183, 32, 145, 255});
                }
                else {
                    Graphic::drawText((std::get<0>(chat) + ": ").c_str(), 60, 925, 20, {38, 138, 4, 255});
                }
                Graphic::drawText(std::get<1>(chat).c_str(), 60 + nameWidth, 925, 20, {255, 255, 255, 255});
            }
            drawWindow(_isOpen, coordinator);
        }

        bool isOpen(void) {
            return _isOpen;
        }

    protected:
        void drawWindow(bool isOpen, Coordinator &coordinator) {
            int size;
            if (isOpen) {
                Graphic::drawRectangle(50, 630, 600, 400, {0, 0, 0, 50});
                Graphic::drawRectangleLines(50, 630, 600, 400, RWHITE);
                Graphic::drawRectangleLines(50, 960, 600, 70, RWHITE);
                size = 600;
                detectInput();
                displayChats();
            } else {
                Graphic::drawRectangle(50, 960, 300, 70, {0, 0, 0, 50});
                Graphic::drawRectangleLines(50, 960, 300, 70, RWHITE);
                size = 300;
            }
            std::string text = isOpen ? _chat : "Open Chat";
            int textHeight = 20;
            int textWidth = Graphic::measureText(text.c_str(), textHeight);

            int textX = _isOpen ? 60 : static_cast<int>(50 + (size - textWidth) / 2);
            int textY = static_cast<int>(960 + (70 - textHeight) / 2);
            Graphic::drawText(text.c_str(), textX, textY, 20, RWHITE);
            Vector2 mousePosition = Graphic::getMousePosition();
            bool selected = Graphic::checkCollisionPointRec(mousePosition.x, mousePosition.y, 50, 630, 600, 400);

            if (!selected && Graphic::isMouseButtonPressed() && _isOpen)
                _isOpen = !_isOpen;
            if (Graphic::isKeyPressed(KEY_ENTER)) {
                if (_chat != "" && _isOpen) {
                    //chatList.push_back(std::make_pair(_user, _chat));
                    coordinator.AddEvent(Event{Event::actions::MESSAGE, 0, {std::make_any<std::string>(_chat)}});
                    _chat.clear();
                } else {
                    _isOpen = !_isOpen;
                }
            }
        }
        void detectInput(void) {
            int key = Graphic::getCharPressed();
            if ((key >= 32) && (key <= 125) && Graphic::measureText(_chat.c_str(), 20) < 580) {
                _chat += static_cast<char>(key);
            }
            if (Graphic::isKeyPressed(KEY_BACKSPACE) && _chat.length() > 0) {
                _chat.pop_back();
            }
        }
        void displayChats(void) {
            int y = 925;
            int padding = 25;
            for (auto chat : chatList) {
                if ((y - padding) < 635)
                    break;
                displayChat(chat, y);
            }
            //std::reverse(chatList.begin(), chatList.end());
        }
        void displayChat(std::pair<std::string, std::string> chat, int &y) {
            int textHeight = 20;
            int nameWidth = Graphic::measureText((std::get<0>(chat) + ": ").c_str(), textHeight);
            int textWidth = Graphic::measureText(std::get<1>(chat).c_str(), textHeight);

            if (std::get<0>(chat) == _user) {
                nameWidth = Graphic::measureText("Me: ", textHeight);
                Graphic::drawText("Me: ", 60, y, 20, {39, 33, 219, 255});
            } else if (std::get<0>(chat) == "System") {
                Graphic::drawText((std::get<0>(chat) + ": ").c_str(), 60, y, 20, {183, 32, 145, 230});
            }
            else {
                Graphic::drawText((std::get<0>(chat) + ": ").c_str(), 60, y, 20, {38, 138, 4, 255});
            }
            if (nameWidth + textWidth >= 600) {
                std::string breakStr = "";
                while (nameWidth + textWidth >= 600) {
                    breakStr += std::get<1>(chat).back();
                    std::get<1>(chat).pop_back();
                    textWidth = Graphic::measureText(std::get<1>(chat).c_str(), textHeight);
                }
                Graphic::drawText(std::get<1>(chat).c_str(), 60 + nameWidth, y, 20, RWHITE);
                Graphic::drawText(breakStr.c_str(), 60 + nameWidth, y + 15, 20, RWHITE);
            } else {
                Graphic::drawText(std::get<1>(chat).c_str(), 60 + nameWidth, y, 20, RWHITE);
            }
            y -= 40;
        }
    private:
        std::vector<std::pair<std::string, std::string>> chatList;
        bool _isOpen;
        std::string _chat;
        std::string _user;
        std::chrono::seconds _duration;
        std::chrono::steady_clock::time_point receiveTime;
};

#endif /* !CHAT_HPP_ */
