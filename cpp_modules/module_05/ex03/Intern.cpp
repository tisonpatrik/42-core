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

// A lookup table instead of an if/else chain: each form name sits next to
// the member function that creates it
AForm *Intern::makeForm(const std::string &name,
                        const std::string &target) const {
  struct FormType {
    const char *formName;
    AForm *(Intern::*create)(const std::string &target) const;
  };

  // Built once, on the first call
  static const FormType formTypes[] = {
      {ShrubberyCreationForm::formName, &Intern::createShrubbery},
      {RobotomyRequestForm::formName, &Intern::createRobotomy},
      {PresidentialPardonForm::formName, &Intern::createPardon}};
  // Size of the whole table divided by the size of one entry
  static const int formCount = sizeof(formTypes) / sizeof(formTypes[0]);

  for (int i = 0; i < formCount; i++) {
    if (name == formTypes[i].formName) {
      std::cout << "Intern creates " << name << std::endl;
      return (this->*formTypes[i].create)(target);
    }
  }
  std::cout << "Intern can't create " << name << ": no such form"
            << std::endl;
  return 0;
}
