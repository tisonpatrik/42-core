#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm(void)
    : AForm("robotomy request", 72, 45), target("default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("robotomy request", 72, 45), target(target) {}

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
