#include "Bureaucrat.hpp"
#include "Form.hpp"

#include <iostream>

static void testSignSuccess(void) {
  // Arrange
  Bureaucrat bob("Bob", 10);
  Form form("28B", 20, 5);

  // Act
  bob.signForm(form);

  // Assert: "Bob signed 28B", then the form shows signed: yes
  std::cout << form << std::endl;
}

static void testSignTooLow(void) {
  // Arrange
  Bureaucrat jim("Jim", 100);
  Form form("28C", 50, 5);

  // Act
  jim.signForm(form);

  // Assert: "Jim couldn't sign 28C because grade is too low.", signed: no
  std::cout << form << std::endl;
}

static void testExactGrade(void) {
  // Arrange
  Bureaucrat ann("Ann", 50);
  Form form("A38", 50, 50);

  // Act
  ann.signForm(form);

  // Assert: "Ann signed A38", the required grade itself is enough
  std::cout << form << std::endl;
}

static void testInvalidFormGrades(void) {
  // Arrange
  int grades[][2] = {{0, 10}, {10, 151}};
  int gradeCount = sizeof(grades) / sizeof(grades[0]);

  for (int i = 0; i < gradeCount; i++) {
    try {
      // Act
      Form invalid("Invalid", grades[i][0], grades[i][1]);
      std::cout << invalid << std::endl;
    } catch (std::exception &e) {
      // Assert: "grade is too high", then "grade is too low"
      std::cout << e.what() << std::endl;
    }
  }
}

int main(void) {
  testSignSuccess();
  testSignTooLow();
  testExactGrade();
  testInvalidFormGrades();
  return 0;
}
