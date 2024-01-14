
#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <functional>
#include <set>
#include "Entity.hpp"
#include "SparseArray.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Drawable.hpp"
#include "Controllable.hpp"

class Registry
{
public:
    Entity create_entity();
    void destroy_entity(Entity e);

    template <typename Component>
    void register_component_type();

    template <typename Component>
    SparseArray<Component> &register_component();

    template <class Component>
    SparseArray<Component> &get_components();

    template <class Component>
    SparseArray<Component> const &get_components() const;

    template <typename Component>
    void add_component(Entity e, Component component);

    template <typename Component>
    void remove_component(Entity e);

    template <typename Component>
    Component *get_component(Entity e);

    template <typename Component>
    SparseArray<Component> &get_component_array()
    {
        return *std::static_pointer_cast<SparseArray<Component>>(components_[std::type_index(typeid(Component))]);
    }

    size_t entity_count() {
        return alive_entities_.size();
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> components_;
    std::unordered_map<std::type_index, std::function<void(Entity)>> component_erase_functions_;

    std::unordered_map<std::type_index, std::shared_ptr<void>> component_arrays_;

    size_t next_entity_id_ = 0;
    std::set<Entity> alive_entities_;
};

#include "../registery.cpp" // Include the source file here

#endif /* !REGISTRY_HPP */