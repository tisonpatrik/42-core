#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void){}

ClapTrap::ClapTrap(std::string name)
{
    this->name = name;
}

ClapTrap::ClapTrap(const ClapTrap &other){
    *this = other;
}
ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
    if (this != &other)
    {
        this->name = other.name;
        this->hitPoints = other.hitPoints;
        this->energyPoints = other.energyPoints;
        this->attack_damage = other.attack_damage;
    }
    return *this;
}

ClapTrap::~ClapTrap(void){}

void ClapTrap::attack(const std::string& target)
{

}

void ClapTrap::takeDamage(unsigned int amount)
{
    if(this->energyPoints > 0)
    {
        this->hitPoints = hitPoints - amount;
        this->energyPoints  = energyPoints - 1;
    }
}

void ClapTrap::beRepaired(unsigned int amount)
{

    if(this->energyPoints > 0)
    {
        this->hitPoints = hitPoints + amount;
        this->energyPoints  = energyPoints - 1;
    }
}
