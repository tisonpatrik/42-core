#include "Zombie.hpp"

#include <iostream>

static bool testHorde(int count, const std::string &name)
{
    std::cout << "Testing N = " << count << ", name = \""
              << name << "\"" << std::endl;

    Zombie *horde = zombieHorde(count, name);

    if ((count > 0 && horde == 0) || (count <= 0 && horde != 0))
    {
        std::cerr << "Unexpected horde allocation." << std::endl;
        delete[] horde;
        return false;
    }

    for (int i = 0; i < count; ++i)
        horde[i].announce();

    delete[] horde;
    return true;
}

int main()
{
    if (!testHorde(5, "Foo")
        || !testHorde(1, "Bar")
        || !testHorde(2, "")
        || !testHorde(0, "Empty")
        || !testHorde(-3, "Invalid"))
        return 1;

    std::cout << "All horde tests passed." << std::endl;
    return 0;
}
