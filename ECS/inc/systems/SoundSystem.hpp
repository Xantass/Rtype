/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** SoundSystem
*/

/**
 * @file SoundSystem.hpp
 * @brief File containing the Sound system
 *
 */

#ifndef SOUNDSYSTEM_HPP_
#define SOUNDSYSTEM_HPP_

#include "System.hpp"
#include "components/Sound.hpp"

/**
 * @class SoundSystem
 * @brief Class of the Sound system
 *
 */
class SoundSystem : public System {
public:
    /**
     * @brief Update the Sound system using the entities stocker in the coordinator
     * @param coordinator : The coordinator of the ECS
     *
     */
    void Update(Coordinator &coordinator);
protected:
private:
};

#include "../../src/systems/SoundSystem.cpp"

#endif /* !SOUNDSYSTEM_HPP_ */
