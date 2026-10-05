#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
    if (N <= 0)
        return 0;

    Zombie *horde = new Zombie[N];

    try
    {
        for (int i = 0; i < N; ++i)
            horde[i].setName(name);
    }
    catch (...)
    {
        // Release the array if initializing a name fails.
        delete[] horde;
        throw;
    }

    return horde;
}
