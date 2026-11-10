#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap(void) : ClapTrap() {
  this->hitPoints = 100;
  this->energyPoints = 100;
  this->attackDamage = 30;
  std::cout << "FragTrap " << this->name << " created by default constructor"
            << std::endl;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
  this->hitPoints = 100;
  this->energyPoints = 100;
  this->attackDamage = 30;
  std::cout << "FragTrap " << this->name << " created by name constructor"
            << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other) {
  std::cout << "FragTrap " << this->name << " created by copy constructor"
            << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other) {
  std::cout << "FragTrap " << this->name << " assigned from FragTrap "
            << other.name << std::endl;
  ClapTrap::operator=(other);
  return *this;
}

FragTrap::~FragTrap(void) {
  std::cout << "FragTrap " << this->name << " destroyed" << std::endl;
}

void FragTrap::highFivesGuys(void) {
  std::cout << "FragTrap " << this->name << " asks: high five, guys?"
            << std::endl;
}
