/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Chat
*/

#include "Chat.hpp"

Chat::Chat(std::string user) {
    this->_isOpen = false;
    this->_chat = "";
    this->_user = user;
    this->_duration = std::chrono::seconds(2);
    this->receiveTime = std::chrono::steady_clock::now();
}

Chat::~Chat()
{
}

void Chat::DisplayChatWindow(Coordinator &coordinator)
{
    std::queue<Event> eventQueue = coordinator.GetEventQueue();

    while (!eventQueue.empty()) {
        Event event = eventQueue.front();
        eventQueue.pop();
        if (event._type == Event::CREATE_MESSAGE) {
            std::reverse(this->chatList.begin(), this->chatList.end());
            std::pair<std::string, std::string> chat = std::make_pair(std::any_cast<std::string>(event._data.at(0)), std::any_cast<std::string>(event._data.at(1)));
            this->chatList.push_back(chat);
            std::reverse(this->chatList.begin(), this->chatList.end());
            this->receiveTime = std::chrono::steady_clock::now();
        }
    }
    if (std::chrono::steady_clock::now() - this->receiveTime < this->_duration) {
        std::pair<std::string, std::string> chat = this->chatList[0];
        int nameWidth = Graphic::measureText((std::get<0>(chat) + ": ").c_str(), 20);
        if (std::get<0>(chat) == "System") {
            Graphic::drawText((std::get<0>(chat) + ": ").c_str(), 60, 925, 20, {183, 32, 145, 255});
        }
        else {
            Graphic::drawText((std::get<0>(chat) + ": ").c_str(), 60, 925, 20, {38, 138, 4, 255});
        }
        Graphic::drawText(std::get<1>(chat).c_str(), 60 + nameWidth, 925, 20, {255, 255, 255, 255});
    }
    DrawWindow(this->_isOpen, coordinator);
}

void Chat::DrawWindow(bool isOpen, Coordinator &coordinator)
{
    int size;
    if (isOpen) {
        Graphic::drawRectangle(50, 630, 600, 400, {0, 0, 0, 50});
        Graphic::drawRectangleLines(50, 630, 600, 400, RWHITE);
        Graphic::drawRectangleLines(50, 960, 600, 70, RWHITE);
        size = 600;
        DetectInput();
        DisplayChats();
    } else {
        Graphic::drawRectangle(50, 960, 300, 70, {0, 0, 0, 50});
        Graphic::drawRectangleLines(50, 960, 300, 70, RWHITE);
        size = 300;
    }
    std::string text = isOpen ? this->_chat : "Open Chat";
    int textHeight = 20;
    int textWidth = Graphic::measureText(text.c_str(), textHeight);

    int textX = this->_isOpen ? 60 : static_cast<int>(50 + (size - textWidth) / 2);
    int textY = static_cast<int>(960 + (70 - textHeight) / 2);
    Graphic::drawText(text.c_str(), textX, textY, 20, RWHITE);
    Vector2 mousePosition = Graphic::getMousePosition();
    bool selected = Graphic::checkCollisionPointRec(mousePosition.x, mousePosition.y, 50, 630, 600, 400);

    if (!selected && Graphic::isMouseButtonPressed() && this->_isOpen)
        this->_isOpen = !this->_isOpen;
    if (Graphic::isKeyPressed(KEY_ENTER)) {
        if (this->_chat != "" && this->_isOpen) {
            //chatList.push_back(std::make_pair(_user, _chat));
            coordinator.AddEvent(Event{Event::actions::MESSAGE, 0, {std::make_any<std::string>(this->_chat)}});
            this->_chat.clear();
        } else {
            this->_isOpen = !this->_isOpen;
        }
    }
}

void Chat::DetectInput(void) {
    int key = Graphic::getCharPressed();
    if ((key >= 32) && (key <= 125) && Graphic::measureText(this->_chat.c_str(), 20) < 580) {
        this->_chat += static_cast<char>(key);
    }
    if (Graphic::isKeyPressed(KEY_BACKSPACE) && this->_chat.length() > 0) {
        this->_chat.pop_back();
    }
}

void Chat::DisplayChats(void)
{
    int y = 925;
    int padding = 25;
    for (auto chat : chatList) {
        if ((y - padding) < 635)
            break;
        DisplayChat(chat, y);
    }
}

void Chat::DisplayChat(std::pair<std::string, std::string> chat, int &y)
{
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