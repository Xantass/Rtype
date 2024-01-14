/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** SoundSystem
*/

#include "SoundSystem.hpp"

inline void SoundSystem::Update(Coordinator &coordinator)
{
    for (auto entity : this->_entities) {
        auto& sound = coordinator.GetComponent<Son>(entity);

        if (sound.shouldBePlayed) {
            Graphic::playSound(sound.sound);
            sound.shouldBePlayed = false;
        }
    }
}
