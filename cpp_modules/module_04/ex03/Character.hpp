#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Character : public ICharacter {
private:
  std::string name;
  AMateria *inventory[4];

  void clearInventory(void);
  void copyInventory(const Character &other);

public:
  Character(void);
  Character(std::string const &name);
  Character(const Character &other);
  Character &operator=(const Character &other);
  ~Character(void);

  std::string const &getName() const;
  void equip(AMateria *m);
  void unequip(int idx);
  void use(int idx, ICharacter &target);
};

#endif
