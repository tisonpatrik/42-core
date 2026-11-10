#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap(void) : ClapTrap() {
  this->hitPoints = 100;
  this->energyPoints = 50;
  this->attackDamage = 20;
  std::cout << "ScavTrap " << this->name << " created by default constructor"
            << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
  this->hitPoints = 100;
  this->energyPoints = 50;
  this->attackDamage = 20;
  std::cout << "ScavTrap " << this->name << " created by name constructor"
            << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other) {
  std::cout << "ScavTrap " << this->name << " created by copy constructor"
            << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other) {
  std::cout << "ScavTrap " << this->name << " assigned from ScavTrap "
            << other.name << std::endl;
  ClapTrap::operator=(other);
  return *this;
}

ScavTrap::~ScavTrap(void) {
  std::cout << "ScavTrap " << this->name << " destroyed" << std::endl;
}

void ScavTrap::attack(const std::string &target) {
  if (this->hitPoints == 0 || this->energyPoints == 0) {
    std::cout << "ScavTrap " << this->name
              << " can't attack: no hit points or energy points left!"
              << std::endl;
    return;
  }
  this->energyPoints--;
  std::cout << "ScavTrap " << this->name << " attacks " << target
            << ", causing " << this->attackDamage << " points of damage!"
            << std::endl;
}

void ScavTrap::guardGate() {
  std::cout << "ScavTrap " << this->name << " is now in Gate keeper mode."
            << std::endl;
}
