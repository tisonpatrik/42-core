#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <ostream>
#include <string>

class Bureaucrat {
private:
  const std::string name;
  int grade;

public:
  static const int highestGrade = 1;
  static const int lowestGrade = 150;

  Bureaucrat(void);
  Bureaucrat(const std::string &name, int grade);
  Bureaucrat(const Bureaucrat &other);
  Bureaucrat &operator=(const Bureaucrat &other);
  ~Bureaucrat(void);

  const std::string &getName(void) const;
  int getGrade(void) const;
  void incrementGrade(void);
  void decrementGrade(void);

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
