/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-jules.gresset
** File description:
** Movable
*/

#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

enum Direction {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT,
    NONE
};

struct Movable {
    Direction direction;
};

#endif /* !MOVABLE_HPP_ */
