#include "ClapTrap.hpp"

#include <climits>
#include <iostream>

ClapTrap::ClapTrap(void)
    : name("default"), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap " << this->name << " created by default constructor" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
    : name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap " << this->name << " created by name constructor" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
    : name(other.name), hitPoints(other.hitPoints),
      energyPoints(other.energyPoints), attackDamage(other.attackDamage)
{
    std::cout << "ClapTrap " << this->name << " created by copy constructor" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
    std::cout << "ClapTrap " << this->name << " assigned from ClapTrap " << other.name << std::endl;
    if (this != &other)
    {
        this->name = other.name;
        this->hitPoints = other.hitPoints;
        this->energyPoints = other.energyPoints;
        this->attackDamage = other.attackDamage;
    }
    return *this;
}

ClapTrap::~ClapTrap(void)
{
    std::cout << "ClapTrap " << this->name << " destroyed" << std::endl;
}

void ClapTrap::attack(const std::string &target)
{
    if (this->hitPoints == 0 || this->energyPoints == 0)
    {
        std::cout << "ClapTrap " << this->name
                  << " can't attack: no hit points or energy points left!"
                  << std::endl;
        return;
    }
    this->energyPoints--;
    std::cout << "ClapTrap " << this->name << " attacks " << target
              << ", causing " << this->attackDamage
              << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->hitPoints == 0)
    {
        std::cout << "ClapTrap " << this->name << " has no hit points left and can't take more damage!" << std::endl;
        return;
    }
    if (amount >= this->hitPoints)
        this->hitPoints = 0;
    else
        this->hitPoints -= amount;
    std::cout << "ClapTrap " << this->name << " takes " << amount << " points of damage and now has " << this->hitPoints
              << " hit points!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->hitPoints == 0 || this->energyPoints == 0)
    {
        std::cout << "ClapTrap " << this->name
                  << " can't repair: no hit points or energy points left!"
                  << std::endl;
        return;
    }
    this->energyPoints--;
    if (amount > UINT_MAX - this->hitPoints)
        this->hitPoints = UINT_MAX;
    else
        this->hitPoints += amount;
    std::cout << "ClapTrap " << this->name << " repairs itself for " << amount
              << " points and now has " << this->hitPoints
              << " hit points!" << std::endl;
}
