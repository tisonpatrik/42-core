#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

// Only a static method, so every constructor is private: nobody can create
// a ScalarConverter
class ScalarConverter {
private:
  ScalarConverter(void);
  ScalarConverter(const ScalarConverter &other);
  ScalarConverter &operator=(const ScalarConverter &other);
  ~ScalarConverter(void);

public:
  static void convert(const std::string &literal);
};

#endif
