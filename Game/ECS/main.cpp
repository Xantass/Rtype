#include <iostream>
#include <unistd.h>
#include <sys/select.h>
#include "./include/Registry.hpp"

bool gm_run = true;

struct HealthComponent
{
    int hitpoints;
};

void render()
{
    std::cout << "Rendering..." << std::endl;
}

void update_game_state()
{
    #include "./include/SparseArray.hpp"

    std::cout << "Updating game state..." << std::endl;
}

bool data_available()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv);

    return FD_ISSET(STDIN_FILENO, &readfds);
}

void logging_system(Registry &r) {
    auto const &positions = r.get_components<Position>();
    auto const &velocities = r.get_components<Velocity>();

    for (size_t i = 0; i < r.entity_count(); ++i) {
        auto const & pos = positions[i];
        auto const & vel = velocities[i];

        if (pos && vel) {
            std::cerr << "Bonhomme " << i << ": Position = { "
                      << pos->x << ", " << pos->y
                      << " }, Velocity = { " << vel->vx
                      << ", " << vel->vy << " }" << std::endl;
        }
    }
}


void process_input(Position *pos)
{
    if (data_available())
    {
        char input = std::cin.get();
        switch (input)
        {
        case 'p':
            gm_run = false;
            break;
        case 'z':
            pos->y += 1;
            break;
        case 'q':
            pos->x -= 1;
            break;
        case 's':
            pos->y -= 1;
            break;
        case 'd':
            pos->x += 1;
            break;
        }
    }
}

int game_loop(Registry &r, Position *pos, Entity player)
{
    while (gm_run)
    {
        process_input(pos);
        logging_system(r);
        sleep(1);   }
    return 0;
}

int main()
{
    std::cout << "Hello, World!" << std::endl;

    Registry reg;

    reg.register_component_type<Position>();
    reg.register_component_type<Velocity>();
    reg.register_component_type<Controllable>();
    reg.register_component_type<Drawable>();

    Entity player = reg.create_entity();

    reg.add_component<Position>(player, Position{0, 0});
    reg.add_component<Velocity>(player, Velocity{1, 0});

    Entity ent = reg.create_entity();

    reg.add_component<Position>(ent, Position{5, 5});
    reg.add_component<Velocity>(ent, Velocity{6, 0});

    Position *pos = reg.get_component<Position>(player);

    game_loop(reg, pos, player);
    reg.destroy_entity(ent);
    std::cout << "Entity destroyed." << std::endl;

    return 0;
}
