#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

static void testExecuteAllForms(void) {
  // Arrange
  Bureaucrat boss("Boss", 1);
  ShrubberyCreationForm shrubbery("home");
  RobotomyRequestForm robotomy("Bender");
  PresidentialPardonForm pardon("Arthur Dent");
  AForm *forms[] = {&shrubbery, &robotomy, &pardon};

  for (int i = 0; i < 3; i++) {
    // Act
    boss.signForm(*forms[i]);
    boss.executeForm(*forms[i]);
  }

  // Assert: every form is signed and executed, home_shrubbery is created,
  // Bender is robotomized or not, Arthur Dent is pardoned
}

static void testExecuteUnsigned(void) {
  // Arrange
  Bureaucrat boss("Boss", 1);
  PresidentialPardonForm pardon("Ford Prefect");

  // Act
  boss.executeForm(pardon);

  // Assert: "Boss couldn't execute presidential pardon because form is not
  // signed."
}

static void testExecuteGradeTooLow(void) {
  // Arrange
  Bureaucrat signer("Signer", 70);
  Bureaucrat clerk("Clerk", 50);
  RobotomyRequestForm robotomy("Marvin");
  signer.signForm(robotomy);

  // Act
  clerk.executeForm(robotomy);

  // Assert: signed by Signer, but Clerk (50) can't execute it (needs 45)
}

static void testRobotomyIsRandom(void) {
  // Arrange
  Bureaucrat boss("Boss", 1);
  RobotomyRequestForm robotomy("Bender");
  boss.signForm(robotomy);

  for (int i = 0; i < 4; i++) {
    // Act
    robotomy.execute(boss);
  }

  // Assert: a mix of successful and failed robotomies
}

int main(void) {
  testExecuteAllForms();
  testExecuteUnsigned();
  testExecuteGradeTooLow();
  testRobotomyIsRandom();
  return 0;
}
