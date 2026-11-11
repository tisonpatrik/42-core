#include "Character.hpp"

Character::Character(void) : name("default") {
  for (int i = 0; i < 4; i++)
    this->inventory[i] = 0;
}

Character::Character(std::string const &name) : name(name) {
  for (int i = 0; i < 4; i++)
    this->inventory[i] = 0;
}

Character::Character(const Character &other) : name(other.name) {
  for (int i = 0; i < 4; i++)
    this->inventory[i] = 0;
  this->copyInventory(other);
}

Character &Character::operator=(const Character &other) {
  if (this != &other) {
    this->name = other.name;
    this->clearInventory();
    this->copyInventory(other);
  }
  return *this;
}

Character::~Character(void) { this->clearInventory(); }

void Character::clearInventory(void) {
  for (int i = 0; i < 4; i++) {
    delete this->inventory[i];
    this->inventory[i] = 0;
  }
}

void Character::copyInventory(const Character &other) {
  for (int i = 0; i < 4; i++) {
    if (other.inventory[i])
      this->inventory[i] = other.inventory[i]->clone();
  }
}

std::string const &Character::getName() const { return this->name; }

void Character::equip(AMateria *m) {
  if (!m)
    return;
  for (int i = 0; i < 4; i++) {
    if (this->inventory[i] == m)
      return;
  }
  for (int i = 0; i < 4; i++) {
    if (!this->inventory[i]) {
      this->inventory[i] = m;
      return;
    }
  }
}

void Character::unequip(int idx) {
  if (idx < 0 || idx >= 4)
    return;
  this->inventory[idx] = 0;
}

void Character::use(int idx, ICharacter &target) {
  if (idx < 0 || idx >= 4 || !this->inventory[idx])
    return;
  this->inventory[idx]->use(target);
}
