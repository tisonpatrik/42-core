#include "HumanB.hpp"

#include <iostream>

HumanB::HumanB( std::string &name) : name(name), weapon(0)
{
}

void HumanB::setWeapon(Weapon &weapon)
{
    this->weapon = &weapon;
}

void HumanB::attack(void)
{
    if (weapon == 0)
    {
        std::cout << name << " has no weapon to attack with" << std::endl;
        return;
    }

    std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}
