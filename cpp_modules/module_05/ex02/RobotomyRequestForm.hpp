#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

#include <string>

class RobotomyRequestForm : public AForm {
private:
  std::string target;

  void executeAction(void) const;

public:
  static const char *const formName;
  static const int signGrade = 72;
  static const int execGrade = 45;

  RobotomyRequestForm(void);
  RobotomyRequestForm(const std::string &target);
  RobotomyRequestForm(const RobotomyRequestForm &other);
  RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
  ~RobotomyRequestForm(void);

  const std::string &getTarget(void) const;
};

#endif
