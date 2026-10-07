#include "Harl.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

static std::string readFixture(const char *filename)
{
    std::ifstream input(filename);
    assert(input.is_open());
    std::string content;
    char character;
    while (input.get(character))
        content += character;
    assert(input.eof() && !input.bad());
    return content;
}

static void testKnownLevels()
{
    // Arrange
    Harl harl;
    const std::string expected = readFixture("fixtures/levels.txt");
    std::ostringstream output;
    std::streambuf *original = std::cout.rdbuf(output.rdbuf());

    // Act
    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
    std::cout.rdbuf(original);

    // Assert
    assert(output.str() == expected);
}

static void testUnknownLevelsAreSilent()
{
    // Arrange
    Harl harl;
    std::ostringstream output;
    std::streambuf *original = std::cout.rdbuf(output.rdbuf());

    // Act
    harl.complain("");
    harl.complain("UNKNOWN");
    harl.complain("debug");
    harl.complain(" INFO ");
    std::cout.rdbuf(original);

    // Assert
    assert(output.str().empty());
}

static void testRepeatedComplaints()
{
    // Arrange
    Harl harl;
    const std::string expected = readFixture("fixtures/repeated.txt");
    std::ostringstream output;
    std::streambuf *original = std::cout.rdbuf(output.rdbuf());

    // Act
    harl.complain("ERROR");
    harl.complain("ERROR");
    std::cout.rdbuf(original);

    // Assert
    assert(output.str() == expected);
}

int main()
{
    testKnownLevels();
    testUnknownLevelsAreSilent();
    testRepeatedComplaints();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
