#include "Bureaucrat.hpp"

static void validateGrade(int grade) {
  if (grade < 1)
    throw Bureaucrat::GradeTooHighException();
  if (grade > 150)
    throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(void) : name("default"), grade(150) {}

Bureaucrat::Bureaucrat(const std::string &name, int grade)
    : name(name), grade(grade) {
  validateGrade(grade);
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
    : name(other.name), grade(other.grade) {}

// The name is const, only the grade can be copied
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
  if (this != &other)
    this->grade = other.grade;
  return *this;
}

Bureaucrat::~Bureaucrat(void) {}

const std::string &Bureaucrat::getName(void) const { return this->name; }

int Bureaucrat::getGrade(void) const { return this->grade; }

// Grade 1 is the highest, so incrementing means going down to 1
void Bureaucrat::incrementGrade(void) {
  validateGrade(this->grade - 1);
  this->grade--;
}

void Bureaucrat::decrementGrade(void) {
  validateGrade(this->grade + 1);
  this->grade++;
}

const char *Bureaucrat::GradeTooHighException::what(void) const throw() {
  return "grade is too high";
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw() {
  return "grade is too low";
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat) {
  os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade()
     << ".";
  return os;
}
