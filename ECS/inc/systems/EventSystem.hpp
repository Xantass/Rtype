/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** EventSystem
*/

#ifndef EVENTSYSTEM_HPP_
#define EVENTSYSTEM_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include "Entity.hpp"

class EventSystem : public System {
public:

    /**
     * @brief Run all the events
     * 
     */
    void RunEvents(Coordinator &coordinator);

protected:
private:
};

#include "../../src/systems/EventSystem.cpp"

#endif /* !EVENTSYSTEM_HPP_ */
