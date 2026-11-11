#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

#include <iostream>

static void testSubjectExample(void) {
  // Arrange
  const Animal *j = new Dog();
  const Animal *i = new Cat();

  // Act
  delete j;
  delete i;

  // Assert: each Brain is created and deleted, valgrind shows no leaks
}

static void testAnimalArray(void) {
  // Arrange
  const int size = 4;
  const Animal *animals[size];
  for (int i = 0; i < size; i++) {
    if (i < size / 2)
      animals[i] = new Dog();
    else
      animals[i] = new Cat();
  }

  // Act
  for (int i = 0; i < size; i++)
    animals[i]->makeSound();
  for (int i = 0; i < size; i++)
    delete animals[i];

  // Assert: two "Haf!", two "Mnaou!", and each delete runs Brain, Dog or Cat,
  // then Animal destructor
}

static void testDogDeepCopy(void) {
  // Arrange
  Dog original;
  original.setIdea(0, "Chase the cat");

  // Act
  Dog copy(original);
  copy.setIdea(0, "Sleep");
  std::cout << "original: " << original.getIdea(0) << std::endl;
  std::cout << "copy: " << copy.getIdea(0) << std::endl;

  // Assert: original keeps "Chase the cat", copy has "Sleep"
}

static void testCatDeepAssignment(void) {
  // Arrange
  Cat original;
  Cat assigned;
  original.setIdea(0, "Ignore the dog");

  // Act
  assigned = original;
  assigned.setIdea(0, "Eat");
  std::cout << "original: " << original.getIdea(0) << std::endl;
  std::cout << "assigned: " << assigned.getIdea(0) << std::endl;

  // Assert: original keeps "Ignore the dog", assigned has "Eat"
}

int main(void) {
  testSubjectExample();
  testAnimalArray();
  testDogDeepCopy();
  testCatDeepAssignment();
  return 0;
}
