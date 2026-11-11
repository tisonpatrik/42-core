#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

#include <iostream>

static void testSubjectExample(void) {
  // Arrange
  IMateriaSource *src = new MateriaSource();
  src->learnMateria(new Ice());
  src->learnMateria(new Cure());
  ICharacter *me = new Character("me");
  AMateria *tmp;
  tmp = src->createMateria("ice");
  me->equip(tmp);
  tmp = src->createMateria("cure");
  me->equip(tmp);
  ICharacter *bob = new Character("bob");

  // Act
  me->use(0, *bob);
  me->use(1, *bob);

  delete bob;
  delete me;
  delete src;

  // Assert: "* shoots an ice bolt at bob *", then "* heals bob's wounds *"
}

static void testFullInventoryAndInvalidSlots(void) {
  // Arrange
  Character me("me");
  Character bob("bob");
  for (int i = 0; i < 4; i++)
    me.equip(new Ice());
  AMateria *extra = new Cure();

  // Act
  me.equip(extra);
  me.use(3, bob);
  me.use(4, bob);
  me.use(-1, bob);
  me.unequip(7);

  delete extra;

  // Assert: only one ice bolt, the Cure doesn't fit and invalid slots do
  // nothing
}

static void testUnequip(void) {
  // Arrange
  Character me("me");
  Character bob("bob");
  AMateria *cure = new Cure();
  me.equip(cure);

  // Act
  me.unequip(0);
  me.use(0, bob);
  me.equip(new Ice());
  me.use(0, bob);

  delete cure;

  // Assert: nothing after unequip, then an ice bolt from the freed slot 0
}

static void testDeepCopy(void) {
  // Arrange
  Character original("original");
  Character bob("bob");
  original.equip(new Ice());
  Character assigned("assigned");
  assigned.equip(new Cure());

  // Act
  Character copy(original);
  assigned = original;
  original.use(0, bob);
  copy.use(0, bob);
  assigned.use(0, bob);

  // Assert: three ice bolts, every Character has its own Ice, and the old
  // Cure of assigned is deleted (valgrind shows no leaks or double frees)
}

static void testUnknownType(void) {
  // Arrange
  MateriaSource src;
  src.learnMateria(new Ice());

  // Act
  AMateria *fire = src.createMateria("fire");

  // Assert: prints 1, createMateria returns 0 for an unknown type
  std::cout << (fire == 0) << std::endl;
}

int main(void) {
  testSubjectExample();
  testFullInventoryAndInvalidSlots();
  testUnequip();
  testDeepCopy();
  testUnknownType();
  return 0;
}
