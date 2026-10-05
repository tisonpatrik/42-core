#include "Zombie.hpp"

int main()
{
    // Heap: this zombie survives the function that created it.
    Zombie *heapZombie = newZombie("Foo");
    heapZombie->announce();

    // Stack: this zombie is destroyed when randomChump returns.
    randomChump("Bar");

    delete heapZombie;
    return 0;
}
