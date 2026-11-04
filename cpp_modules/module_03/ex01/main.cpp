#include "ClapTrap.hpp"

static void testAttack(void)
{
    // Arrange
    ClapTrap clap("Clappy");

    // Act
    clap.attack("a dummy");

    // Assert: prints "causing 0 points of damage"
}

static void testDamageAndRepair(void)
{
    // Arrange
    ClapTrap clap("Clappy");

    // Act
    clap.takeDamage(3);
    clap.beRepaired(2);

    // Assert: prints 7 hit points, then 9 hit points
}

static void testNoEnergy(void)
{
    // Arrange
    ClapTrap clap("Tired");
    for (int i = 0; i < 10; i++)
        clap.attack("a dummy");

    // Act
    clap.attack("a dummy");

    // Assert: prints "can't attack"
}

static void testNoHitPoints(void)
{
    // Arrange
    ClapTrap clap("Fragile");
    clap.takeDamage(25);

    // Act
    clap.beRepaired(5);

    // Assert: prints "can't repair"
}

int main(void)
{
    testAttack();
    testDamageAndRepair();
    testNoEnergy();
    testNoHitPoints();
    return 0;
}
