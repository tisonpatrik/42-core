#include "Bureaucrat.hpp"

#include <iostream>

static void testValidBureaucrat(void) {
  // Arrange
  Bureaucrat bob("Bob", 42);

  // Act
  bob.incrementGrade();
  std::cout << bob << std::endl;
  bob.decrementGrade();
  bob.decrementGrade();

  // Assert: prints "Bob, bureaucrat grade 41.", then "... grade 43."
  std::cout << bob << std::endl;
}

static void testInvalidGradeInConstructor(void) {
  // Arrange
  int grades[] = {0, 151};
  int gradeCount = sizeof(grades) / sizeof(grades[0]);

  for (int i = 0; i < gradeCount; i++) {
    try {
      // Act
      Bureaucrat invalid("Invalid", grades[i]);
      std::cout << invalid << std::endl;
    } catch (std::exception &e) {
      // Assert: "grade is too high", then "grade is too low"
      std::cout << e.what() << std::endl;
    }
  }
}

static void testIncrementAtTop(void) {
  // Arrange
  Bureaucrat boss("Boss", 1);

  try {
    // Act
    boss.incrementGrade();
    std::cout << "not reached" << std::endl;
  } catch (std::exception &e) {
    // Assert: "grade is too high" and the grade stays 1
    std::cout << e.what() << std::endl;
  }
  std::cout << boss << std::endl;
}

static void testDecrementAtBottom(void) {
  // Arrange
  Bureaucrat intern("Intern", 150);

  try {
    // Act
    intern.decrementGrade();
    std::cout << "not reached" << std::endl;
  } catch (std::exception &e) {
    // Assert: "grade is too low" and the grade stays 150
    std::cout << e.what() << std::endl;
  }
  std::cout << intern << std::endl;
}

int main(void) {
  testValidBureaucrat();
  testInvalidGradeInConstructor();
  testIncrementAtTop();
  testDecrementAtBottom();
  return 0;
}
