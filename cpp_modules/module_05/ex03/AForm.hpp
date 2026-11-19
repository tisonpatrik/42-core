#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"

#include <exception>
#include <ostream>
#include <string>

class AForm {
private:
  const std::string name;
  bool isSigned;
  const int gradeToSign;
  const int gradeToExecute;

protected:
  virtual void executeAction(void) const = 0;

public:
  AForm(void);
  AForm(const std::string &name, int gradeToSign, int gradeToExecute);
  AForm(const AForm &other);
  AForm &operator=(const AForm &other);
  virtual ~AForm(void);

  const std::string &getName(void) const;
  bool getIsSigned(void) const;
  int getGradeToSign(void) const;
  int getGradeToExecute(void) const;
  void beSigned(const Bureaucrat &bureaucrat);
  void execute(const Bureaucrat &executor) const;

  class GradeTooHighException : public std::exception {
  public:
    const char *what(void) const throw();
  };

  class GradeTooLowException : public std::exception {
  public:
    const char *what(void) const throw();
  };

  class NotSignedException : public std::exception {
  public:
    const char *what(void) const throw();
  };
};

std::ostream &operator<<(std::ostream &os, const AForm &form);

#endif
