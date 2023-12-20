
#ifndef CONTROLLABLE_HPP
#define CONTROLLABLE_HPP

struct Controllable
{
    int value;

    Controllable(int value) : value(value) {}

    Controllable() = default;

    ~Controllable() = default;
};

#endif // CONTROLLABLE_HPP