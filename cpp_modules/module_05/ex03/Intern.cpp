#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <iostream>

Intern::Intern(void) {}

Intern::Intern(const Intern &other) { (void)other; }

Intern &Intern::operator=(const Intern &other) {
  (void)other;
  return *this;
}

Intern::~Intern(void) {}

AForm *Intern::createShrubbery(const std::string &target) const {
  return new ShrubberyCreationForm(target);
}

AForm *Intern::createRobotomy(const std::string &target) const {
  return new RobotomyRequestForm(target);
}

AForm *Intern::createPardon(const std::string &target) const {
  return new PresidentialPardonForm(target);
}

// A lookup table of member function pointers instead of an if/else chain:
// name i is built by creator i
AForm *Intern::makeForm(const std::string &name,
                        const std::string &target) const {
  static const std::string names[] = {ShrubberyCreationForm::formName,
                                      RobotomyRequestForm::formName,
                                      PresidentialPardonForm::formName};
  static AForm *(Intern::*const creators[])(const std::string &) const = {
      &Intern::createShrubbery, &Intern::createRobotomy,
      &Intern::createPardon};
  static const int formCount = sizeof(names) / sizeof(names[0]);

  for (int i = 0; i < formCount; i++) {
    if (name == names[i]) {
      std::cout << "Intern creates " << name << std::endl;
      return (this->*creators[i])(target);
    }
  }
  std::cout << "Intern can't create " << name << ": no such form"
            << std::endl;
  return 0;
}
