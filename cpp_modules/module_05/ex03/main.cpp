#include "Bureaucrat.hpp"
#include "Intern.hpp"

#include <iostream>

static void testSubjectExample(void) {
  // Arrange
  Intern someRandomIntern;
  Bureaucrat boss("Boss", 1);
  AForm *rrf;

  // Act
  rrf = someRandomIntern.makeForm("robotomy request", "Bender");
  boss.signForm(*rrf);
  boss.executeForm(*rrf);

  delete rrf;

  // Assert: "Intern creates robotomy request", then it is signed and executed
}

static void testAllForms(void) {
  // Arrange
  Intern intern;
  std::string names[] = {"shrubbery creation", "robotomy request",
                         "presidential pardon"};
  int formCount = sizeof(names) / sizeof(names[0]);

  for (int i = 0; i < formCount; i++) {
    // Act
    AForm *form = intern.makeForm(names[i], "office");

    // Assert: each form has the requested name and its own grades
    std::cout << *form << std::endl;
    delete form;
  }
}

static void testUnknownForm(void) {
  // Arrange
  Intern intern;

  // Act
  AForm *form = intern.makeForm("coffee request", "Boss");

  // Assert: an error message, then prints 1, makeForm returns 0
  std::cout << (form == 0) << std::endl;
}

int main(void) {
  testSubjectExample();
  testAllForms();
  testUnknownForm();
  return 0;
}
