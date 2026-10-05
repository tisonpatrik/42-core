#include "replaceFile.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>

static bool writeFile(const std::string &filename, const std::string &content)
{
    std::ofstream output(filename.c_str(), std::ios::binary | std::ios::trunc);
    if (!output.is_open())
        return false;
    output << content;
    output.close();
    return static_cast<bool>(output);
}

static bool readFile(const std::string &filename, std::string &content)
{
    std::ifstream input(filename.c_str(), std::ios::binary);
    if (!input.is_open())
        return false;
    content.clear();
    char character;
    while (input.get(character))
        content += character;
    return input.eof() && !input.bad();
}

static bool reportTest(const std::string &name, bool passed)
{
    std::cout << (passed ? "[PASS] " : "[FAIL] ") << name << std::endl;
    return passed;
}

struct TestCase
{
    std::string name;
    std::string content;
    std::string search;
    std::string replacement;
    std::string expected;
};

static bool testReplacement(const std::string &directory, const TestCase &test)
{
    const std::string filename = directory + "/" + test.name + ".txt";
    std::string result;
    std::string original;
    const bool passed = writeFile(filename, test.content)
        && replaceFile(filename, test.search, test.replacement)
        && readFile(filename + ".replace", result)
        && result == test.expected
        && readFile(filename, original)
        && original == test.content;
    return reportTest(test.name, passed);
}

static bool expectFailure(const std::string &filename, const std::string &s1,
                          const std::string &s2)
{
    std::ostringstream errors;
    std::streambuf *original = std::cerr.rdbuf(errors.rdbuf());
    const bool result = replaceFile(filename, s1, s2);
    std::cerr.rdbuf(original);
    return !result && !errors.str().empty();
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <test directory>" << std::endl;
        return 1;
    }

    const std::string directory = argv[1];
    const TestCase tests[] = {
        {"basic", "hello world hello\n", "hello", "hi", "hi world hi\n"},
        {"adjacent", "aaaa", "aa", "X", "XX"},
        {"overlapping", "ababa", "aba", "X", "Xba"},
        {"longer replacement", "a b a", "a", "alphabet", "alphabet b alphabet"},
        {"deletion", "abcabc", "abc", "", ""},
        {"no recursive replacement", "aaa", "a", "aa", "aaaaaa"},
        {"identical strings", "foo foo", "foo", "foo", "foo foo"},
        {"no match", "unchanged\n", "missing", "new", "unchanged\n"},
        {"empty file", "", "abc", "x", ""},
        {"long search", "abc", "abcdef", "x", "abc"},
        {"multiline", "first\nsecond\nfirst\n", "first", "done",
         "done\nsecond\ndone\n"},
        {"match across lines", "ab\ncd\nab\ncd", "b\nc", "X", "aXd\naXd"},
        {"CRLF", "one\r\none\r\n", "one", "two", "two\r\ntwo\r\n"},
        {"binary bytes", std::string("a\0ba\0b", 6), "a", "x",
         std::string("x\0bx\0b", 6)},
        {"buffer boundary", std::string(4095, 'x') + "ab" + std::string(4095, 'x'),
         "ab", "Z", std::string(4095, 'x') + "Z" + std::string(4095, 'x')}
    };

    bool passed = true;
    for (std::size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i)
        passed = testReplacement(directory, tests[i]) && passed;

    passed = reportTest("empty filename", expectFailure("", "a", "b")) && passed;
    passed = reportTest("missing input",
                        expectFailure(directory + "/missing.txt", "a", "b"))
        && passed;
    passed = reportTest("directory as input", expectFailure(directory, "a", "b"))
        && passed;

    const std::string emptySearchFile = directory + "/empty-search.txt";
    std::string preserved;
    const bool emptySearchPassed = writeFile(emptySearchFile, "unchanged")
        && writeFile(emptySearchFile + ".replace", "preserved")
        && expectFailure(emptySearchFile, "", "x")
        && readFile(emptySearchFile + ".replace", preserved)
        && preserved == "preserved";
    passed = reportTest("empty search preserves existing output", emptySearchPassed)
        && passed;

    const std::string blockedFile = directory + "/blocked.txt";
    passed = reportTest("output cannot be opened",
                        writeFile(blockedFile, "hello")
                        && expectFailure(blockedFile, "hello", "hi"))
        && passed;

    return passed ? 0 : 1;
}
