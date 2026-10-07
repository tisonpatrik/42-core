#include "replaceFile.hpp"
#include "replaceText.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

static std::string readFile(const std::string &filename)
{
    std::ifstream input(filename.c_str(), std::ios::binary);
    assert(input.is_open());
    std::string content;
    char character;
    while (input.get(character))
        content += character;
    assert(input.eof() && !input.bad());
    return content;
}

static void testReplacesAllMatches()
{
    // Arrange
    const std::string input = "hello world hello";
    const std::string expected = "hi world hi";

    // Act
    const std::string result = replaceText(input, "hello", "hi");

    // Assert
    assert(result == expected);
}

static void testDoesNotReplaceInsertedText()
{
    // Arrange
    const std::string input = "aaa";
    const std::string expected = "aaaaaa";

    // Act
    const std::string result = replaceText(input, "a", "aa");

    // Assert
    assert(result == expected);
}

static void testKeepsTextWithoutMatches()
{
    // Arrange
    const std::string input = "hello world";

    // Act
    const std::string result = replaceText(input, "missing", "hi");

    // Assert
    assert(result == input);
}

static void testRejectsEmptySearch()
{
    // Arrange
    const std::string input = "hello";
    bool rejected = false;

    // Act
    try
    {
        replaceText(input, "", "hi");
    }
    catch (const std::invalid_argument &)
    {
        rejected = true;
    }

    // Assert
    assert(rejected);
}

static void testReplacesFile()
{
    // Arrange
    const std::string filename = "bin/test-fixtures/input.txt";
    const std::string original = readFile("fixtures/input.txt");
    const std::string expected = readFile("fixtures/expected.txt");

    // Act
    replaceFile(filename, "hello", "hi");

    // Assert
    assert(readFile(filename + ".replace") == expected);
    assert(readFile(filename) == original);
}

int main()
{
    testReplacesAllMatches();
    testDoesNotReplaceInsertedText();
    testKeepsTextWithoutMatches();
    testRejectsEmptySearch();
    testReplacesFile();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
