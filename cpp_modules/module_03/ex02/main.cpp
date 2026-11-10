#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

static void testClapAttackAndRepair(void) {
  // Arrange
  ClapTrap clap("Clappy");

  // Act
  clap.attack("a dummy");
  clap.takeDamage(3);
  clap.beRepaired(2);

  // Assert: 0 points of damage, 7 hit points, then 9 hit points
}

static void testClapNoEnergy(void) {
  // Arrange
  ClapTrap clap("Tired");
  for (int i = 0; i < 10; i++)
    clap.attack("a dummy");

  // Act
  clap.attack("a dummy");

  // Assert: prints "can't attack"
}

static void testScavAttackAndGuardGate(void) {
  // Arrange
  ScavTrap scav("Serena");

  // Act
  scav.attack("a dummy");
  scav.guardGate();

  // Assert: ClapTrap then ScavTrap on creation, 20 points of damage,
  // Gate keeper mode, ScavTrap then ClapTrap on destruction
}

static void testScavDamageAndRepair(void) {
  // Arrange
  ScavTrap scav("Serena");

  // Act
  scav.takeDamage(30);
  scav.beRepaired(10);

  // Assert: 70 hit points, then 80 hit points
}

static void testFragAttackAndHighFive(void) {
  // Arrange
  FragTrap frag("Fraggy");

  // Act
  frag.attack("a dummy");
  frag.highFivesGuys();

  // Assert: ClapTrap then FragTrap on creation, 30 points of damage,
  // high five request, FragTrap then ClapTrap on destruction
}

static void testFragDamageAndRepair(void) {
  // Arrange
  FragTrap frag("Fraggy");

  // Act
  frag.takeDamage(50);
  frag.beRepaired(20);

  // Assert: 50 hit points, then 70 hit points
}

int main(void) {
  testClapAttackAndRepair();
  testClapNoEnergy();
  testScavAttackAndGuardGate();
  testScavDamageAndRepair();
  testFragAttackAndHighFive();
  testFragDamageAndRepair();
  return 0;
}
