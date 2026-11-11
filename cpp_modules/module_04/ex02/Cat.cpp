#include "Cat.hpp"
#include <iostream>

Cat::Cat(void) : Animal(), brain(new Brain()) {
  this->type = "Cat";
  std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other), brain(new Brain(*other.brain)) {
  std::cout << "Cat copy constructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
  std::cout << "Cat copy assignment operator called" << std::endl;
  Animal::operator=(other);
  *this->brain = *other.brain;
  return *this;
}

Cat::~Cat(void) {
  std::cout << "Cat destructor called" << std::endl;
  delete this->brain;
}

void Cat::makeSound(void) const { std::cout << "Mnaou!" << std::endl; }

void Cat::setIdea(int index, const std::string &idea) {
  this->brain->setIdea(index, idea);
}

std::string Cat::getIdea(int index) const {
  return this->brain->getIdea(index);
}
