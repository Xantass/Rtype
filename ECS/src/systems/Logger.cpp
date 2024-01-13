/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Logger
*/

#include <iostream>
#include <iomanip>
#include <chrono>

#include "Logger.hpp"
#include "HealthPoint.hpp"
#include "Sprite.hpp"
#include "Graphic.hpp"

void Logger::Update(Coordinator &coordinator)
{
    if (Graphic::isKeyPressed(KEY_F1))
        _isDisplayed = !_isDisplayed;
    
    if (!_isDisplayed)
        return;

    int yOffset = 80;
    Color color;

    Graphic::drawRectangle(0, 0, 800, 700, {100, 100, 100, 100});
    Graphic::drawRectangleLines(0, 0, 800, 700, WHITE);
    Graphic::drawText("Logger", 10, 10, 30, WHITE);
    Graphic::drawText("Entities", 10, 50, 25, WHITE);
    Graphic::drawText("Events", 550, 50, 25, WHITE);
    Graphic::drawText(std::to_string(Graphic::getFPS()) + " FPS", 550, 20, 20, WHITE);

    std::queue<Event> events = coordinator.GetEventQueue();

    int mouseX = Graphic::getMousePosition().x;
    int mouseY = Graphic::getMousePosition().y;

    if (Graphic::isMouseButtonPressed()) {
        for (auto entity : _entities) {
            auto &position = coordinator.GetComponent<Position>(entity);

            if (mouseX > position._x && mouseX < position._x + 100 && mouseY > position._y && mouseY < position._y + 100) {
                _idSelected = entity;
                break;
            } else
                _idSelected = -1;
        }
    }

    for (auto entity : _entities) {
        auto &position = coordinator.GetComponent<Position>(entity);
        auto &velocity = coordinator.GetComponent<Velocity>(entity);
        auto &hitbox = coordinator.GetComponent<Hitbox>(entity);
        auto &healthPoint = coordinator.GetComponent<HealthPoint>(entity);

        Graphic::drawRectangleLines(position._x + hitbox._x, position._y + hitbox._y, hitbox.width, hitbox.height, RED);
        Graphic::drawText("Entity " + std::to_string(entity), position._x, position._y + hitbox.height, 20, RED);

        if ((mouseX > position._x && mouseX < position._x + 100 && mouseY > position._y && mouseY < position._y + 100) ||
            (mouseX > 10 && mouseX < 10 + 100 && mouseY > yOffset && mouseY < yOffset + 20) ||
            _idSelected == entity) {
            if (_idSelected == entity)
                color = GREEN;
            else
                color = YELLOW;
            Graphic::drawText("Entity: " + std::to_string(entity), 10, yOffset, 20, color);
            yOffset += 20;

            Graphic::drawText("Position x: " + std::to_string(position._x) + " y: " + std::to_string(position._y), 10, yOffset, 20, color);
            yOffset += 20;

            Graphic::drawText("Velocity x: " + std::to_string(velocity._x) + " y: " + std::to_string(velocity._y), 10, yOffset, 20, color);
            yOffset += 20;

            Graphic::drawText("--Hitbox--", 10, yOffset, 20, color);
            Graphic::drawText("offset_x: " + std::to_string(hitbox._x) + " offset_y: " + std::to_string(hitbox._y), 10, yOffset + 20, 20, color);
            Graphic::drawText("width: " + std::to_string(hitbox.width) + " height: " + std::to_string(hitbox.height), 10, yOffset + 40, 20, color);
            yOffset += 60;

            Graphic::drawText("HealthPoint: " + std::to_string(healthPoint._curr_hp), 10, yOffset, 20, color);
            yOffset += 20;
        } else {
            Graphic::drawText("Entity: " + std::to_string(entity), 10, yOffset, 20, WHITE);
            yOffset += 20;
        }
    }

    while (!events.empty()) {
        auto event = events.front();
        events.pop();

        std::string res;

        if (event._type == Event::actions::CREATE)
            res = "CREATE " + std::to_string(event._entity);
        else if (event._type == Event::actions::DESTROY)
            res = "DESTROY " + std::to_string(event._entity);
        else if (event._type == Event::actions::MOVE)
            res = "MOVE " + std::to_string(event._entity);

        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "(%H:%M:%S)");
        std::string timeString = ss.str();

        res = timeString + " " + res;
        
        _eventStack.push_back(res);
    }

    yOffset = 80;

    while (_eventStack.size() > 30)
        _eventStack.erase(_eventStack.begin());

    for (auto res : _eventStack) {
        Graphic::drawText(res, 550, yOffset, 20, WHITE);
        yOffset += 20;
    }
}