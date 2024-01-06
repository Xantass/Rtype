/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** EventManager
*/

#include "EventManager.hpp"

inline void EventManager::AddEvent(Event event) {
    
    this->_eventQueue.push(event);
}

inline Event EventManager::GetEvent() {
    if (this->_eventQueue.empty() != true) {
        Event event = this->_eventQueue.front();
        this->_eventQueue.pop();
        return event;
    }
    return Event{Event::actions::EMPTY, 0, {std::any(int(-1))}};
}

inline std::queue<Event> EventManager::GetEventQueue() const {
    return std::queue<Event>(this->_eventQueue);
}