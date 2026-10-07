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
    const std::string input = "hello world hello";
    const std::string expected = "hi world hi";

    const std::string result = replaceText(input, "hello", "hi");

    assert(result == expected);
}

static void testDoesNotReplaceInsertedText()
{
    const std::string input = "aaa";
    const std::string expected = "aaaaaa";

    const std::string result = replaceText(input, "a", "aa");

    assert(result == expected);
}

static void testKeepsTextWithoutMatches()
{
    const std::string input = "hello world";

    const std::string result = replaceText(input, "missing", "hi");

    assert(result == input);
}

static void testRejectsEmptySearch()
{
    const std::string input = "hello";
    bool rejected = false;

    try
    {
        replaceText(input, "", "hi");
    }
    catch (const std::invalid_argument &)
    {
        rejected = true;
    }

    assert(rejected);
}

static void testReplacesFile()
{
    const std::string filename = "bin/test-fixtures/input.txt";
    const std::string original = readFile("fixtures/input.txt");
    const std::string expected = readFile("fixtures/expected.txt");

    replaceFile(filename, "hello", "hi");

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
