#include "Zombie.hpp"

int main()
{
    Zombie *zombie = newZombie("Foo");
    zombie->announce();

    randomChump("Bar");

    delete zombie;
    return 0;
}
