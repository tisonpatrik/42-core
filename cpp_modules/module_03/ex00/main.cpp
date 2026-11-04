#include "ClapTrap.hpp"

#include <cassert>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>

static std::ostringstream g_captured;
static std::streambuf *g_coutBuffer;

static void startCapture(void)
{
    g_captured.str("");
    g_coutBuffer = std::cout.rdbuf(g_captured.rdbuf());
}

// Restores std::cout, shows the captured messages and returns them for the assert.
static std::string stopCapture(void)
{
    std::cout.rdbuf(g_coutBuffer);
    std::cout << g_captured.str();
    return g_captured.str();
}

static bool contains(const std::string &text, const std::string &expected)
{
    return text.find(expected) != std::string::npos;
}

static void attack_withEnergy_printsDamageMessage(void)
{
    // Arrange
    ClapTrap clap("Clappy");

    // Act
    startCapture();
    clap.attack("a dummy");
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "ClapTrap Clappy attacks a dummy, causing 0 points of damage!"));
}

static void attack_withoutEnergy_fails(void)
{
    // Arrange
    ClapTrap clap("Tired");
    for (int i = 0; i < 10; i++)
        clap.attack("a dummy");

    // Act
    startCapture();
    clap.attack("a dummy");
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "can't attack"));
}

static void takeDamage_smallAmount_lowersHitPoints(void)
{
    // Arrange
    ClapTrap clap("Clappy");

    // Act
    startCapture();
    clap.takeDamage(3);
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "now has 7 hit points"));
}

static void takeDamage_withoutEnergy_stillLowersHitPoints(void)
{
    // Arrange
    ClapTrap clap("Tired");
    for (int i = 0; i < 10; i++)
        clap.attack("a dummy");

    // Act
    startCapture();
    clap.takeDamage(1);
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "now has 9 hit points"));
}

static void takeDamage_hugeAmount_stopsAtZero(void)
{
    // Arrange
    ClapTrap clap("Fragile");

    // Act
    startCapture();
    clap.takeDamage(UINT_MAX);
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "now has 0 hit points"));
}

static void beRepaired_withEnergy_raisesHitPoints(void)
{
    // Arrange
    ClapTrap clap("Clappy");

    // Act
    startCapture();
    clap.beRepaired(2);
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "now has 12 hit points"));
}

static void beRepaired_hugeAmount_doesNotOverflow(void)
{
    // Arrange
    ClapTrap clap("Strong");

    // Act
    startCapture();
    clap.beRepaired(UINT_MAX);
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "now has 4294967295 hit points"));
}

static void actions_withoutHitPoints_fail(void)
{
    // Arrange
    ClapTrap clap("Fragile");
    clap.takeDamage(10);

    // Act
    startCapture();
    clap.attack("a dummy");
    clap.beRepaired(5);
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "can't attack"));
    assert(contains(output, "can't repair"));
}

static void copyConstructor_copiesStateIndependently(void)
{
    // Arrange
    ClapTrap original("Original");
    original.takeDamage(4);

    // Act
    ClapTrap copy(original);
    startCapture();
    copy.takeDamage(1);
    original.takeDamage(2);
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "now has 5 hit points"));
    assert(contains(output, "now has 4 hit points"));
}

static void assignment_copiesNameAndState(void)
{
    // Arrange
    ClapTrap source("Source");
    ClapTrap target;
    source.takeDamage(4);

    // Act
    target = source;
    startCapture();
    target.takeDamage(1);
    const std::string output = stopCapture();

    // Assert
    assert(contains(output, "ClapTrap Source takes 1 points of damage and now has 5 hit points"));
}

int main(void)
{
    attack_withEnergy_printsDamageMessage();
    attack_withoutEnergy_fails();
    takeDamage_smallAmount_lowersHitPoints();
    takeDamage_withoutEnergy_stillLowersHitPoints();
    takeDamage_hugeAmount_stopsAtZero();
    beRepaired_withEnergy_raisesHitPoints();
    beRepaired_hugeAmount_doesNotOverflow();
    actions_withoutHitPoints_fail();
    copyConstructor_copiesStateIndependently();
    assignment_copiesNameAndState();
    return 0;
}
