#include "Data.hpp"
#include "Serializer.hpp"

#include <iostream>

static void printTestName(const char *name) {
  std::cout << std::endl << "=== " << name << " ===" << std::endl;
}

static void testRoundTrip(void) {
  printTestName("testRoundTrip");

  // Arrange
  Data data;
  data.id = 42;
  data.name = "answer";

  // Act
  uintptr_t raw = Serializer::serialize(&data);
  Data *ptr = Serializer::deserialize(raw);

  // Assert: prints 1, the pointer is the same, then "42 answer"
  std::cout << (ptr == &data) << std::endl;
  std::cout << ptr->id << " " << ptr->name << std::endl;
}

static void testRawIsAddress(void) {
  printTestName("testRawIsAddress");

  // Arrange
  Data data;

  // Act
  uintptr_t raw = Serializer::serialize(&data);

  // Assert: the number and the address are the same value
  std::cout << std::hex << "0x" << raw << std::dec << std::endl;
  std::cout << &data << std::endl;
}

int main(void) {
  testRoundTrip();
  testRawIsAddress();
  return 0;
}
