/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Event
*/

/**
 * @file Event.hpp
 * @brief File containing the Event class
 * 
 */


#ifndef EVENT_HPP_
#define EVENT_HPP_

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
        PARAM = 2,
        JOIN = 1,
        EMPTY = 0,
    };

    /**
     * @brief Construct a new Event object
     * 
     * @param t Type of the event
     * @param e Entity of the event
     * @param d Data of the event
     */
    Event(const actions t, Entity e, const std::any& d) : _type(t), _entity(e), _data(d) {}

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
    std::any _data;
};

#endif /* !EVENT_HPP_ */
