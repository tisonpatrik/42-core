#include "PresidentialPardonForm.hpp"

#include <iostream>

const char *const PresidentialPardonForm::formName = "presidential pardon";
const int PresidentialPardonForm::signGrade;
const int PresidentialPardonForm::execGrade;

PresidentialPardonForm::PresidentialPardonForm(void)
    : AForm(formName, signGrade, execGrade), target("default") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
    : AForm(formName, signGrade, execGrade), target(target) {}

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
