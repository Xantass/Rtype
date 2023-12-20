

#ifndef RTYPE_ENTITY_HPP
#define RTYPE_ENTITY_HPP

#include <iostream>

class Entity
{
public:
    explicit Entity(size_t id) : id_(id){};

    operator size_t() const { return id_; };

private:
    size_t id_;
};

#endif // RTYPE_ENTITY_HPP