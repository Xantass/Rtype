/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** EventSystem
*/

/**
 * @file EventSystem.hpp
 * @brief File containing the EventSystem class
 *
 */

#ifndef EVENTSYSTEM_HPP_
#define EVENTSYSTEM_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include "Entity.hpp"
#include "AssetManager.hpp"

/**
 * @class EventSystem
 * @brief Class of the system handling the events
 *
 */
class EventSystem : public System {
public:

    /**
     * @brief Run all the events
     * 
     * @param coordinator Reference to the coordinator
     * @param assetManager Reference to the assetManager
     */
    void RunEvents(Coordinator &coordinator, AssetManager &assetManager);

protected:
private:
};

#include "../../src/systems/EventSystem.cpp"

#endif /* !EVENTSYSTEM_HPP_ */
