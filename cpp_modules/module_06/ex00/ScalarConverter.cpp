#include "ScalarConverter.hpp"

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>

enum LiteralType { CHAR, INT, FLOAT, DOUBLE, INVALID };

ScalarConverter::ScalarConverter(void) {}

ScalarConverter::ScalarConverter(const ScalarConverter &) {}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) {
  return *this;
}

ScalarConverter::~ScalarConverter(void) {}

// NaN is the only value that is not equal to itself
static bool isNan(double value) { return value != value; }

static bool isInf(double value) {
  return value == std::numeric_limits<double>::infinity() ||
         value == -std::numeric_limits<double>::infinity();
}

// Every comparison with NaN is false, so NaN is never in range
static bool isInRange(double value, double min, double max) {
  return value >= min && value <= max;
}

static bool fitsChar(double value) {
  return isInRange(value, std::numeric_limits<char>::min(),
                   std::numeric_limits<char>::max());
}

static bool fitsInt(double value) {
  return isInRange(value, std::numeric_limits<int>::min(),
                   std::numeric_limits<int>::max());
}

// A float can hold NaN and infinity too, only a finite number can be too big
static bool fitsFloat(double value) {
  return isNan(value) || isInf(value) ||
         isInRange(value, -std::numeric_limits<float>::max(),
                   std::numeric_limits<float>::max());
}

static bool isChar(const std::string &literal) {
  if (literal.length() == 1)
    return !std::isdigit(static_cast<unsigned char>(literal[0]));
  return literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'';
}

// Decimal notation only: [+-]digits[.digits][f] with at least one digit
static LiteralType detectNumber(const std::string &literal) {
  size_t i = 0;
  size_t digits = 0;
  bool hasDot = false;

  if (literal[i] == '+' || literal[i] == '-')
    i++;
  for (; i < literal.length(); i++) {
    if (std::isdigit(static_cast<unsigned char>(literal[i])))
      digits++;
    else if (literal[i] == '.' && !hasDot)
      hasDot = true;
    else
      break;
  }
  if (digits == 0)
    return INVALID;
  if (i == literal.length() && hasDot)
    return DOUBLE;
  if (i == literal.length())
    return INT;
  if (literal[i] == 'f' && hasDot && i + 1 == literal.length())
    return FLOAT;
  return INVALID;
}

static LiteralType detectType(const std::string &literal) {
  if (literal.empty())
    return INVALID;
  if (literal == "nanf" || literal == "+inff" || literal == "-inff" ||
      literal == "inff")
    return FLOAT;
  if (literal == "nan" || literal == "+inf" || literal == "-inf" ||
      literal == "inf")
    return DOUBLE;
  if (isChar(literal))
    return CHAR;

  LiteralType type = detectNumber(literal);
  if (type == INVALID)
    return INVALID;

  // A number that doesn't fit its own type is handled as a double, one that
  // doesn't even fit a double is invalid
  double value = std::strtod(literal.c_str(), 0);
  if (isInf(value))
    return INVALID;
  if (type == INT && !fitsInt(value))
    return DOUBLE;
  if (type == FLOAT && !fitsFloat(value))
    return DOUBLE;
  return type;
}

// Whole numbers get ".0" so that 42 is shown as 42.0
static std::string toString(double value, int precision) {
  std::ostringstream os;
  os.precision(precision);
  os << value;
  std::string str = os.str();
  if (!isNan(value) && !isInf(value) &&
      str.find_first_of(".e") == std::string::npos)
    str += ".0";
  return str;
}

static void printChar(double value) {
  std::cout << "char: ";
  if (!fitsChar(value)) {
    std::cout << "impossible";
  } else {
    char c = static_cast<char>(value);
    if (std::isprint(static_cast<unsigned char>(c)))
      std::cout << "'" << c << "'";
    else
      std::cout << "Non displayable";
  }
  std::cout << std::endl;
}

static void printInt(double value) {
  std::cout << "int: ";
  if (!fitsInt(value))
    std::cout << "impossible";
  else
    std::cout << static_cast<int>(value);
  std::cout << std::endl;
}

static void printFloat(double value) {
  std::cout << "float: ";
  if (!fitsFloat(value))
    std::cout << "impossible";
  else
    std::cout << toString(static_cast<double>(static_cast<float>(value)),
                          std::numeric_limits<float>::digits10)
              << "f";
  std::cout << std::endl;
}

static void printDouble(double value, int precision) {
  std::cout << "double: " << toString(value, precision) << std::endl;
}

// Every int, float and char fits in a double without losing anything, so the
// printers take a double and check the range of their own type. The double
// is shown with the precision of the original type, so 4.2f stays 4.2
static void printAll(double value, int precision) {
  printChar(value);
  printInt(value);
  printFloat(value);
  printDouble(value, precision);
}

void ScalarConverter::convert(const std::string &literal) {
  switch (detectType(literal)) {
  case CHAR: {
    // Either a or 'a'
    char c = literal[0];
    if (literal.length() == 3)
      c = literal[1];
    printAll(static_cast<double>(c), std::numeric_limits<double>::digits10);
    break;
  }
  case INT: {
    int i = static_cast<int>(std::strtol(literal.c_str(), 0, 10));
    printAll(static_cast<double>(i), std::numeric_limits<double>::digits10);
    break;
  }
  case FLOAT: {
    float f = static_cast<float>(std::strtod(literal.c_str(), 0));
    printAll(static_cast<double>(f), std::numeric_limits<float>::digits10);
    break;
  }
  case DOUBLE:
    printAll(std::strtod(literal.c_str(), 0),
             std::numeric_limits<double>::digits10);
    break;
  case INVALID:
    std::cout << "char: impossible" << std::endl
              << "int: impossible" << std::endl
              << "float: impossible" << std::endl
              << "double: impossible" << std::endl;
    break;
  }
}
