#include "DiamondTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap(void)
    : ClapTrap("default_clap_name"), ScavTrap(), FragTrap(), name("default") {
  this->hitPoints = 100;   // FragTrap
  this->energyPoints = 50; // ScavTrap
  this->attackDamage = 30; // FragTrap
  std::cout << "DiamondTrap " << this->name << " created by default constructor"
            << std::endl;
}

DiamondTrap::DiamondTrap(const std::string &name)
    : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name),
      name(name) {
  this->hitPoints = 100;   // FragTrap
  this->energyPoints = 50; // ScavTrap
  this->attackDamage = 30; // FragTrap
  std::cout << "DiamondTrap " << this->name << " created by name constructor"
            << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other)
    : ClapTrap(other), ScavTrap(other), FragTrap(other), name(other.name) {
  std::cout << "DiamondTrap " << this->name << " created by copy constructor"
            << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other) {
  std::cout << "DiamondTrap " << this->name << " assigned from DiamondTrap "
            << other.name << std::endl;
  ClapTrap::operator=(other);
  this->name = other.name;
  return *this;
}

DiamondTrap::~DiamondTrap(void) {
  std::cout << "DiamondTrap " << this->name << " destroyed" << std::endl;
}

void DiamondTrap::attack(const std::string &target) {
  ScavTrap::attack(target);
}

void DiamondTrap::whoAmI(void) {
  std::cout << "I am DiamondTrap " << this->name << ", my ClapTrap name is "
            << ClapTrap::name << std::endl;
}
