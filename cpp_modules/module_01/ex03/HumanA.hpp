#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"

#include <string>

class HumanA
{
private:
    std::string name;
    Weapon &weapon;

public:
    HumanA( std::string &name, Weapon &weapon);

    void attack(void) ;
};

#endif
