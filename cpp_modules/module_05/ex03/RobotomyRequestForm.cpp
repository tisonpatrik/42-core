#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

const char *const RobotomyRequestForm::formName = "robotomy request";
const int RobotomyRequestForm::signGrade;
const int RobotomyRequestForm::execGrade;

RobotomyRequestForm::RobotomyRequestForm(void)
    : AForm(formName, signGrade, execGrade), target("default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm(formName, signGrade, execGrade), target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
    : AForm(other), target(other.target) {}

RobotomyRequestForm &
RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    this->target = other.target;
  }
  return *this;
}

RobotomyRequestForm::~RobotomyRequestForm(void) {}

const std::string &RobotomyRequestForm::getTarget(void) const {
  return this->target;
}

void RobotomyRequestForm::executeAction(void) const {
  static bool seeded = false;
  if (!seeded) {
    std::srand(std::time(0));
    seeded = true;
  }
  std::cout << "* bzzzzz... drilling noises... bzzzzz *" << std::endl;
  if (std::rand() % 2)
    std::cout << this->target << " has been robotomized successfully"
              << std::endl;
  else
    std::cout << "The robotomy of " << this->target << " failed" << std::endl;
}
