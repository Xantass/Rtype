
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

struct Drawable
{
    int value;

    Drawable(int value) : value(value) {}

    Drawable() = default;

    ~Drawable() = default;
};

#endif // DRAWABLE_HPP