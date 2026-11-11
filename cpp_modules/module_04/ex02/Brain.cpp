#include "Brain.hpp"
#include <iostream>

Brain::Brain(void) {
  std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain &other) {
  std::cout << "Brain copy constructor called" << std::endl;
  for (int i = 0; i < 100; i++)
    this->ideas[i] = other.ideas[i];
}

Brain &Brain::operator=(const Brain &other) {
  std::cout << "Brain copy assignment operator called" << std::endl;
  if (this != &other) {
    for (int i = 0; i < 100; i++)
      this->ideas[i] = other.ideas[i];
  }
  return *this;
}

Brain::~Brain(void) { std::cout << "Brain destructor called" << std::endl; }

void Brain::setIdea(int index, const std::string &idea) {
  if (index < 0 || index >= 100)
    return;
  this->ideas[index] = idea;
}

std::string Brain::getIdea(int index) const {
  if (index < 0 || index >= 100)
    return "";
  return this->ideas[index];
}
