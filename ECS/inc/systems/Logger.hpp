/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Logger
*/

/**
 * @file Logger.hpp
 * @brief File containing the Logger class
 *
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "System.hpp"
#include "Coordinator.hpp"

class Logger : public System {
public:
    /**
     * @brief Update the logger
     * 
     * @param coordinator Coordinator reference
     */
    void Update(Coordinator &coordinator);

protected:
private:

    /**
     * @brief The id of the selected entity
     * 
     */
    unsigned int _idSelected = -1;

    /**
     * @brief Event stack
     * 
     */
    std::vector<std::string> _eventStack = {};

    /**
     * @brief If the logger is displayed
     * 
     */
    bool _isDisplayed = false;
};

#include "../../src/systems/Logger.cpp"

#endif /* !LOGGER_HPP_ */
