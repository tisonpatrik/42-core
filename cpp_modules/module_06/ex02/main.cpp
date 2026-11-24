#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

Base *generate(void) {
  static bool seeded = false;
  if (!seeded) {
    std::srand(std::time(0));
    seeded = true;
  }
  switch (std::rand() % 3) {
  case 0:
    return new A();
  case 1:
    return new B();
  default:
    return new C();
  }
}

// A failed dynamic_cast to a pointer returns NULL
void identify(Base *p) {
  if (dynamic_cast<A *>(p) != NULL)
    std::cout << "A" << std::endl;
  else if (dynamic_cast<B *>(p) != NULL)
    std::cout << "B" << std::endl;
  else if (dynamic_cast<C *>(p) != NULL)
    std::cout << "C" << std::endl;
  else
    std::cout << "Unknown type" << std::endl;
}

static void printType(const A &) { std::cout << "A" << std::endl; }

static void printType(const B &) { std::cout << "B" << std::endl; }

static void printType(const C &) { std::cout << "C" << std::endl; }

// A reference can't be NULL, so a failed dynamic_cast to a reference throws
// std::bad_cast instead, which is a std::exception
template <typename T> static bool printIfType(Base &p) {
  try {
    printType(dynamic_cast<T &>(p));
    return true;
  } catch (std::exception &) {
    return false;
  }
}

void identify(Base &p) {
  if (!printIfType<A>(p) && !printIfType<B>(p) && !printIfType<C>(p))
    std::cout << "Unknown type" << std::endl;
}

static void printTestName(const char *name) {
  std::cout << std::endl << "=== " << name << " ===" << std::endl;
}

static void testKnownTypes(void) {
  printTestName("testKnownTypes");

  // Arrange
  A a;
  B b;
  C c;

  // Act + Assert: "A", "A", "B", "B", "C", "C"
  identify(&a);
  identify(a);
  identify(&b);
  identify(b);
  identify(&c);
  identify(c);
}

static void testGenerate(void) {
  printTestName("testGenerate");

  for (int i = 0; i < 5; i++) {
    // Arrange
    Base *base = generate();

    // Act + Assert: both lines name the same random type
    identify(base);
    identify(*base);

    delete base;
  }
}

static void testUnknownType(void) {
  printTestName("testUnknownType");

  // Arrange
  Base base;

  // Act + Assert: "Unknown type" twice, a plain Base is none of A, B, C
  identify(&base);
  identify(base);
}

int main(void) {
  testKnownTypes();
  testGenerate();
  testUnknownType();
  return 0;
}
