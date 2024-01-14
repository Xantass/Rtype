
#ifndef IGAMEOBJECT_HPP
#define IGAMEOBJECT_HPP

class IGameObject
{
public:
    virtual ~IGameObject() = default;

    virtual void Initialize() = 0;

    // Update the state of the object (e.g., position, health).
    virtual void Update(float deltaTime) = 0;

    // Handle events like input or collisions.
    virtual void HandleEvent(const Event &event) = 0;

    // Render the object to the screen.
    virtual void Render() const = 0;
};

#endif // IGAMEOBJECT_HPP