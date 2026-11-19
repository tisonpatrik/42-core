#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <ostream>
#include <string>

class Form;

class Bureaucrat {
private:
  const std::string name;
  int grade;

public:
  Bureaucrat(void);
  Bureaucrat(const std::string &name, int grade);
  Bureaucrat(const Bureaucrat &other);
  Bureaucrat &operator=(const Bureaucrat &other);
  ~Bureaucrat(void);

  const std::string &getName(void) const;
  int getGrade(void) const;
  void incrementGrade(void);
  void decrementGrade(void);
  void signForm(Form &form) const;

  class GradeTooHighException : public std::exception {
  public:
    const char *what(void) const throw();
  };

  class GradeTooLowException : public std::exception {
  public:
    const char *what(void) const throw();
  };
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat);

#endif
