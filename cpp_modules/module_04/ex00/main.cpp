
#include "Animal.hpp"


static void testDifferentSounds(void) {
  // Arrange
  Dog dog;
  Cat cat;
  // Act
  dog.makeSound();
  cat.makeSound();
}

int main(void) {
  testDifferentSounds();
  return 0;
}
