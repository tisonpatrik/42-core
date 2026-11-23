#include "Form.hpp"

static void validateGrade(int grade) {
  if (grade < Bureaucrat::highestGrade)
    throw Form::GradeTooHighException();
  if (grade > Bureaucrat::lowestGrade)
    throw Form::GradeTooLowException();
}

Form::Form(void)
    : name("default"), isSigned(false), gradeToSign(Bureaucrat::lowestGrade),
      gradeToExecute(Bureaucrat::lowestGrade) {}

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign),
      gradeToExecute(gradeToExecute) {
  validateGrade(gradeToSign);
  validateGrade(gradeToExecute);
}

Form::Form(const Form &other)
    : name(other.name), isSigned(other.isSigned),
      gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {}

// The name and grades are const, only the signed status can be copied
Form &Form::operator=(const Form &other) {
  if (this != &other)
    this->isSigned = other.isSigned;
  return *this;
}

Form::~Form(void) {}

const std::string &Form::getName(void) const { return this->name; }

bool Form::getIsSigned(void) const { return this->isSigned; }

int Form::getGradeToSign(void) const { return this->gradeToSign; }

int Form::getGradeToExecute(void) const { return this->gradeToExecute; }

void Form::beSigned(const Bureaucrat &bureaucrat) {
  if (bureaucrat.getGrade() > this->gradeToSign)
    throw Form::GradeTooLowException();
  this->isSigned = true;
}

const char *Form::GradeTooHighException::what(void) const throw() {
  return "grade is too high";
}

const char *Form::GradeTooLowException::what(void) const throw() {
  return "grade is too low";
}

std::ostream &operator<<(std::ostream &os, const Form &form) {
  os << "Form " << form.getName()
     << ", signed: " << (form.getIsSigned() ? "yes" : "no")
     << ", grade to sign: " << form.getGradeToSign()
     << ", grade to execute: " << form.getGradeToExecute();
  return os;
}
