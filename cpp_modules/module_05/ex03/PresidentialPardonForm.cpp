#include "PresidentialPardonForm.hpp"

#include <iostream>

PresidentialPardonForm::PresidentialPardonForm(void)
    : AForm("presidential pardon", 25, 5), target("default") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
    : AForm("presidential pardon", 25, 5), target(target) {}

PresidentialPardonForm::PresidentialPardonForm(
    const PresidentialPardonForm &other)
    : AForm(other), target(other.target) {}

PresidentialPardonForm &
PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    this->target = other.target;
  }
  return *this;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {}

const std::string &PresidentialPardonForm::getTarget(void) const {
  return this->target;
}

void PresidentialPardonForm::executeAction(void) const {
  std::cout << this->target << " has been pardoned by Zaphod Beeblebrox"
            << std::endl;
}
