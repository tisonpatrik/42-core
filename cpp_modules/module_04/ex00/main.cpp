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

int main(void) {
  testSubjectExample();
  testWrongCat();
  return 0;
}
