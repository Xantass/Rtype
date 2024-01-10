/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** EventManager
*/

#ifndef EVENTMANAGER_HPP_
#define EVENTMANAGER_HPP_

#include <queue>
#include <string>
#include <any>

#include "Entity.hpp"

/**
 * @class Event
 * @brief Class of the event
 * @details The Event class is a class that represents an event.
 * 
 */
struct Event {
    enum actions {
        MOVE = 11,
        SHOOT = 10,
        EMPTY = 0,
        PARAM = 2,
        JOIN = 1,
        CREATE = 3,
        DESTROY = 4,
        SPAWN = 5,
        MESSAGE = 15,
    };

    /**
     * @brief Construct a new Event object
     * 
     * @param t Type of the event
     * @param e Entity of the event
     * @param d Data of the event
     */
    Event(actions t, Entity e, std::vector<std::any> d) : _type(t), _entity(e), _data(d) {}

    /**
     * @brief Type of the event
     * 
     */
    actions _type;

    /**
     * @brief Entity of the event
     * 
     */
    Entity _entity;

    /**
     * @brief Data of the event
     * 
     */
    std::vector<std::any> _data;
};

class EventManager {
public:

	/**
	 * @brief Add an event to the queue
	 * 
	 * @param event Event to add
	 */
	void AddEvent(Event event);

	/**
	 * @brief Get the first event of the queue
	 * 
	 * @return Event First event of the queue
	 */
	Event GetEvent();

    /**
     * @brief Get the Event Queue object
     * 
     * @return std::queue<Event> Queue of events
     */
    std::queue<Event> GetEventQueue() const;


protected:
private:
	/**
	 * @brief Queue of events
	 * 
	 */
	std::queue<Event> _eventQueue;
};

#include "../src/EventManager.cpp"

#endif /* !EVENTMANAGER_HPP_ */
