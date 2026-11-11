#include "Dog.hpp"
#include <iostream>

Dog::Dog(void) : Animal(), brain(new Brain()) {
  this->type = "Dog";
  std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other), brain(new Brain(*other.brain)) {
  std::cout << "Dog copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
  std::cout << "Dog copy assignment operator called" << std::endl;
  Animal::operator=(other);
  *this->brain = *other.brain;
  return *this;
}

Dog::~Dog(void) {
  std::cout << "Dog destructor called" << std::endl;
  delete this->brain;
}

void Dog::makeSound(void) const { std::cout << "Haf!" << std::endl; }

void Dog::setIdea(int index, const std::string &idea) {
  this->brain->setIdea(index, idea);
}

std::string Dog::getIdea(int index) const {
  return this->brain->getIdea(index);
}
