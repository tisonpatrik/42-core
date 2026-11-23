#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

#include <exception>
#include <string>

class ShrubberyCreationForm : public AForm {
private:
  std::string target;

  void executeAction(void) const;

public:
  static const char *const formName;
  static const int signGrade = 145;
  static const int execGrade = 137;

  ShrubberyCreationForm(void);
  ShrubberyCreationForm(const std::string &target);
  ShrubberyCreationForm(const ShrubberyCreationForm &other);
  ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
  ~ShrubberyCreationForm(void);

  const std::string &getTarget(void) const;

  class FileOpenException : public std::exception {
  public:
    const char *what(void) const throw();
  };
};

#endif
