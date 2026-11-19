#include "ShrubberyCreationForm.hpp"

#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(void)
    : AForm("shrubbery creation", 145, 137), target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("shrubbery creation", 145, 137), target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(
    const ShrubberyCreationForm &other)
    : AForm(other), target(other.target) {}

ShrubberyCreationForm &
ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    this->target = other.target;
  }
  return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {}

const std::string &ShrubberyCreationForm::getTarget(void) const {
  return this->target;
}

void ShrubberyCreationForm::executeAction(void) const {
  std::string filename = this->target + "_shrubbery";
  std::ofstream file(filename.c_str());
  if (!file)
    throw ShrubberyCreationForm::FileOpenException();
  file << "     ^           ^\n"
          "    ^^^         ^^^\n"
          "   ^^^^^       ^^^^^\n"
          "  ^^^^^^^     ^^^^^^^\n"
          " ^^^^^^^^^   ^^^^^^^^^\n"
          "     |           |\n";
}

const char *
ShrubberyCreationForm::FileOpenException::what(void) const throw() {
  return "shrubbery file could not be opened";
}
