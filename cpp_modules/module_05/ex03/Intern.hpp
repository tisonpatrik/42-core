#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"

#include <string>

class Intern {
private:
  AForm *createShrubbery(const std::string &target) const;
  AForm *createRobotomy(const std::string &target) const;
  AForm *createPardon(const std::string &target) const;

public:
  Intern(void);
  Intern(const Intern &other);
  Intern &operator=(const Intern &other);
  ~Intern(void);

  AForm *makeForm(const std::string &name, const std::string &target) const;
};

#endif
