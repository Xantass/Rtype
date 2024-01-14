/*
** EPITECH PROJECT, 2024
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Creator
*/

#ifndef CREATOR_HPP_
#define CREATOR_HPP_

#include "ECSFlappy.hpp"

class Creator {
    public:
        Creator();
        ~Creator();

        void createEntities(Coordinator &coordinator);
    protected:
    private:
        void createBird(Coordinator &coordinator);
        void createBackground(Coordinator &coordinator);
        void createPipes(Coordinator &coordinator);
        void createCoin(Coordinator &coordinator);
};

#endif /* !CREATOR_HPP_ */
