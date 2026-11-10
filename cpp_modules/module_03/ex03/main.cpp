#include "ClapTrap.hpp"
#include "DiamondTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

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

static void testScavAttackAndGuardGate(void) {
  // Arrange
  ScavTrap scav("Serena");

  // Act
  scav.attack("a dummy");
  scav.guardGate();

  // Assert: prints ClapTrap then ScavTrap on creation, "causing 20 points of
  // damage", Gate keeper mode, then ScavTrap then ClapTrap on destruction
}

static void testScavDamageAndRepair(void) {
  // Arrange
  ScavTrap scav("Serena");

  // Act
  scav.takeDamage(30);
  scav.beRepaired(10);

  // Assert: prints 70 hit points, then 80 hit points
}

static void testScavCopy(void) {
  // Arrange
  ScavTrap original("Original");
  original.takeDamage(40);

  // Act
  ScavTrap copy(original);
  copy.takeDamage(0);

  // Assert: the copy keeps 60 hit points
}

static void testFragAttackAndHighFive(void) {
  // Arrange
  FragTrap frag("Fraggy");

  // Act
  frag.attack("a dummy");
  frag.highFivesGuys();

  // Assert: prints ClapTrap then FragTrap on creation, "causing 30 points of
  // damage", the high five request, then FragTrap then ClapTrap on destruction
}

static void testFragDamageAndRepair(void) {
  // Arrange
  FragTrap frag("Fraggy");

  // Act
  frag.takeDamage(50);
  frag.beRepaired(20);

  // Assert: prints 50 hit points, then 70 hit points
}

static void testDiamondAttackAndWhoAmI(void) {
  // Arrange
  DiamondTrap diamond("Diamond");

  // Act
  diamond.attack("a dummy");
  diamond.whoAmI();
  diamond.guardGate();
  diamond.highFivesGuys();

  // Assert: ClapTrap is created only once, ScavTrap attack causes 30 points of
  // damage, whoAmI prints "Diamond" and "Diamond_clap_name"
}

static void testDiamondStats(void) {
  // Arrange
  DiamondTrap diamond("Diamond");

  // Act
  diamond.takeDamage(0);
  for (int i = 0; i < 50; i++)
    diamond.attack("a dummy");
  diamond.attack("a dummy");

  // Assert: 100 hit points (FragTrap), "can't attack" after 50 attacks
  // (ScavTrap energy)
}

int main(void) {
  testAttack();
  testDamageAndRepair();
  testNoEnergy();
  testNoHitPoints();
  testScavAttackAndGuardGate();
  testScavDamageAndRepair();
  testScavCopy();
  testFragAttackAndHighFive();
  testFragDamageAndRepair();
  testDiamondAttackAndWhoAmI();
  testDiamondStats();
  return 0;
}
