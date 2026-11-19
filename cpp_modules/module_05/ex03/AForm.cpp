#include "AForm.hpp"

static void validateGrade(int grade) {
  if (grade < 1)
    throw AForm::GradeTooHighException();
  if (grade > 150)
    throw AForm::GradeTooLowException();
}

AForm::AForm(void)
    : name("default"), isSigned(false), gradeToSign(150),
      gradeToExecute(150) {}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign),
      gradeToExecute(gradeToExecute) {
  validateGrade(gradeToSign);
  validateGrade(gradeToExecute);
}

AForm::AForm(const AForm &other)
    : name(other.name), isSigned(other.isSigned),
      gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {}

// The name and grades are const, only the signed status can be copied
AForm &AForm::operator=(const AForm &other) {
  if (this != &other)
    this->isSigned = other.isSigned;
  return *this;
}

AForm::~AForm(void) {}

const std::string &AForm::getName(void) const { return this->name; }

bool AForm::getIsSigned(void) const { return this->isSigned; }

int AForm::getGradeToSign(void) const { return this->gradeToSign; }

int AForm::getGradeToExecute(void) const { return this->gradeToExecute; }

void AForm::beSigned(const Bureaucrat &bureaucrat) {
  if (bureaucrat.getGrade() > this->gradeToSign)
    throw AForm::GradeTooLowException();
  this->isSigned = true;
}

// Requirements are checked once here, concrete forms only do their action
void AForm::execute(const Bureaucrat &executor) const {
  if (!this->isSigned)
    throw AForm::NotSignedException();
  if (executor.getGrade() > this->gradeToExecute)
    throw AForm::GradeTooLowException();
  this->executeAction();
}

const char *AForm::GradeTooHighException::what(void) const throw() {
  return "grade is too high";
}

const char *AForm::GradeTooLowException::what(void) const throw() {
  return "grade is too low";
}

const char *AForm::NotSignedException::what(void) const throw() {
  return "form is not signed";
}

std::ostream &operator<<(std::ostream &os, const AForm &form) {
  os << "Form " << form.getName()
     << ", signed: " << (form.getIsSigned() ? "yes" : "no")
     << ", grade to sign: " << form.getGradeToSign()
     << ", grade to execute: " << form.getGradeToExecute();
  return os;
}
