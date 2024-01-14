
#include "./include/Registry.hpp"

Entity Registry::create_entity() {
    Entity newEntity = Entity(next_entity_id_++);
    alive_entities_.insert(newEntity);
    return newEntity;
}

void Registry::destroy_entity(Entity e) {
    for (auto& erase_function : component_erase_functions_) {
        erase_function.second(e);
    }
    alive_entities_.erase(e);
}

template <typename Component>
void Registry::register_component_type() {
    const std::type_index typeIndex = std::type_index(typeid(Component));
    components_[typeIndex] = std::make_shared<SparseArray<Component>>();

    component_erase_functions_[typeIndex] = [this](Entity e) {
        auto& componentArray = get_component_array<Component>();
        componentArray.erase(e);
    };
}

template <typename Component>
void Registry::add_component(Entity e, Component component) {
    const std::type_index typeIndex = std::type_index(typeid(Component));
    auto it = components_.find(typeIndex);
    if (it != components_.end()) {
        std::static_pointer_cast<SparseArray<Component>>(it->second)->insert_at(e, std::move(component));
    }
}

template <typename Component>
void Registry::remove_component(Entity e) {
    const std::type_index typeIndex = std::type_index(typeid(Component));
    auto it = components_.find(typeIndex);
    if (it != components_.end()) {
        std::static_pointer_cast<SparseArray<Component>>(it->second)->erase(e);
    }
}

template <typename Component>
Component* Registry::get_component(Entity e) {
    const std::type_index typeIndex = std::type_index(typeid(Component));
    auto it = components_.find(typeIndex);
    if (it != components_.end()) {
        auto& comp = (*std::static_pointer_cast<SparseArray<Component>>(it->second))[e];
        if (comp) {
            return &(*comp);
        }
    }
    return nullptr;
}

template <typename Component>
SparseArray<Component> &Registry::register_component() {
    const std::type_index typeIndex = std::type_index(typeid(Component));
    components_[typeIndex] = std::make_shared<SparseArray<Component>>();

    component_erase_functions_[typeIndex] = [this](Entity e) {
        auto& componentArray = get_component_array<Component>();
        componentArray.erase(e);
    };
    return *std::static_pointer_cast<SparseArray<Component>>(components_[typeIndex]);
}

template <class Component>
SparseArray<Component> &Registry::get_components() {
    const std::type_index typeIndex = std::type_index(typeid(Component));
    return *std::static_pointer_cast<SparseArray<Component>>(components_[typeIndex]);
}

template <class Component>
SparseArray<Component> const &Registry::get_components() const {
    const std::type_index typeIndex = std::type_index(typeid(Component));
    return *std::static_pointer_cast<SparseArray<Component>>(components_.at(typeIndex));
}