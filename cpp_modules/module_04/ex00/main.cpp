#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <iostream>

static void testSubjectExample(void) {
  // Arrange
  const Animal *meta = new Animal();
  const Animal *j = new Dog();
  const Animal *i = new Cat();

  // Act
  std::cout << j->getType() << " " << std::endl;
  std::cout << i->getType() << " " << std::endl;
  i->makeSound();
  j->makeSound();
  meta->makeSound();

  delete meta;
  delete j;
  delete i;

  // Assert: Dog and Cat types, then "Mnaou!", "Haf!" and the Animal sound
}

static void testWrongCat(void) {
  // Arrange
  const WrongAnimal *wrong = new WrongCat();

  // Act
  std::cout << wrong->getType() << " " << std::endl;
  wrong->makeSound();

  delete wrong;

  // Assert: WrongCat type, but the WrongAnimal sound, because makeSound is not
  // virtual
}

static void testWrongCatDirectCall(void) {
  // Arrange
  const WrongCat cat;
  const WrongAnimal &asAnimal = cat;

  // Act
  cat.makeSound();
  asAnimal.makeSound();

  // Assert: "Mnaou!" when called on WrongCat, "Wrong animal sound" through
  // WrongAnimal, because makeSound is not virtual
}

static void testAnimalArray(void) {
  // Arrange
  const Animal *animals[2] = {new Dog(), new Cat()};

  // Act
  for (int i = 0; i < 2; i++)
    animals[i]->makeSound();
  for (int i = 0; i < 2; i++)
    delete animals[i];

  // Assert: "Haf!" then "Mnaou!", and delete runs Dog and Cat destructors
  // before Animal, because the destructor is virtual
}

static void testCopyAndAssignment(void) {
  // Arrange
  const Dog original;

  // Act
  Dog copy(original);
  Dog assigned;
  assigned = original;
  std::cout << copy.getType() << " " << assigned.getType() << std::endl;

  // Assert: copy constructor and copy assignment messages, then "Dog Dog"
}

int main(void) {
  testSubjectExample();
  testWrongCat();
  testWrongCatDirectCall();
  testAnimalArray();
  testCopyAndAssignment();
  return 0;
}
