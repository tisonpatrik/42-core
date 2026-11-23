#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

#include <string>

class PresidentialPardonForm : public AForm {
private:
  std::string target;

  void executeAction(void) const;

public:
  static const char *const formName;
  static const int signGrade = 25;
  static const int execGrade = 5;

  PresidentialPardonForm(void);
  PresidentialPardonForm(const std::string &target);
  PresidentialPardonForm(const PresidentialPardonForm &other);
  PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
  ~PresidentialPardonForm(void);

  const std::string &getTarget(void) const;
};

#endif
