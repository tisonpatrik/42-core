#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

#include <iostream>

static void printTitle(const std::string &title) {
  std::cout << std::endl << "--- " << title << " ---" << std::endl;
}

static void testAttack(void) {
  // Arrange
  ClapTrap clap("Clappy");

  // Act
  clap.attack("a dummy");

  // Assert: prints "causing 0 points of damage"
}

static void testDamageAndRepair(void) {
  // Arrange
  ClapTrap clap("Clappy");

  // Act
  clap.takeDamage(3);
  clap.beRepaired(2);

  // Assert: prints 7 hit points, then 9 hit points
}

static void testNoEnergy(void) {
  // Arrange
  ClapTrap clap("Tired");
  for (int i = 0; i < 10; i++)
    clap.attack("a dummy");

  // Act
  clap.attack("a dummy");

  // Assert: prints "can't attack"
}

static void testNoHitPoints(void) {
  // Arrange
  ClapTrap clap("Fragile");
  clap.takeDamage(25);

  // Act
  clap.beRepaired(5);

  // Assert: prints "can't repair"
}

static void testScavChaining(void) {
  // Arrange + Act
  ScavTrap scav("Serena");

  // Assert: prints ClapTrap then ScavTrap on creation,
  // ScavTrap then ClapTrap on destruction
}

static void testScavDefaultConstructor(void) {
  // Arrange + Act
  ScavTrap scav;

  // Assert: prints "default" as the name, then "causing 20 points of damage"
  scav.attack("a dummy");
}

static void testScavAttack(void) {
  // Arrange
  ScavTrap scav("Serena");

  // Act
  scav.attack("a dummy");

  // Assert: prints "ScavTrap Serena attacks", "causing 20 points of damage"
}

static void testScavInheritedMethods(void) {
  // Arrange
  ScavTrap scav("Serena");

  // Act
  scav.takeDamage(30);
  scav.beRepaired(10);

  // Assert: prints 70 hit points, then 80 hit points
}

static void testScavGuardGate(void) {
  // Arrange
  ScavTrap scav("Serena");

  // Act
  scav.guardGate();

  // Assert: prints "is now in Gate keeper mode"
}

static void testScavNoEnergy(void) {
  // Arrange
  ScavTrap scav("Tired");
  for (int i = 0; i < 50; i++)
    scav.attack("a dummy");

  // Act
  scav.attack("a dummy");

  // Assert: prints "can't attack" only after 50 attacks
}

static void testScavCopyConstructor(void) {
  // Arrange
  ScavTrap original("Original");
  original.takeDamage(40);

  // Act
  ScavTrap copy(original);
  copy.takeDamage(0);

  // Assert: the copy keeps 60 hit points, not the starting 100
}

static void testScavAssignment(void) {
  // Arrange
  ScavTrap source("Source");
  ScavTrap target("Target");
  source.takeDamage(40);

  // Act
  target = source;
  target.takeDamage(0);

  // Assert: prints "ScavTrap Source takes 0 points" with 60 hit points
}

static void testScavThroughClapTrapPointer(void) {
  // Arrange
  ClapTrap *clap = new ScavTrap("Pointer");

  // Act
  clap->attack("a dummy");
  delete clap;

  // Assert: prints "ScavTrap Pointer attacks",
  // then destroys ScavTrap before ClapTrap
}

int main(void) {
  printTitle("ClapTrap: attack");
  testAttack();
  printTitle("ClapTrap: damage and repair");
  testDamageAndRepair();
  printTitle("ClapTrap: no energy");
  testNoEnergy();
  printTitle("ClapTrap: no hit points");
  testNoHitPoints();
  printTitle("ScavTrap: construction and destruction chaining");
  testScavChaining();
  printTitle("ScavTrap: default constructor");
  testScavDefaultConstructor();
  printTitle("ScavTrap: attack");
  testScavAttack();
  printTitle("ScavTrap: inherited takeDamage and beRepaired");
  testScavInheritedMethods();
  printTitle("ScavTrap: guardGate");
  testScavGuardGate();
  printTitle("ScavTrap: no energy after 50 attacks");
  testScavNoEnergy();
  printTitle("ScavTrap: copy constructor");
  testScavCopyConstructor();
  printTitle("ScavTrap: assignment operator");
  testScavAssignment();
  printTitle("ScavTrap: through a ClapTrap pointer");
  testScavThroughClapTrapPointer();
  return 0;
}
