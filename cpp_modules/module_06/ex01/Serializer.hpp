#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"

#include <stdint.h>

// Only static methods, so every constructor is private: nobody can create
// a Serializer
class Serializer {
private:
  Serializer(void);
  Serializer(const Serializer &other);
  Serializer &operator=(const Serializer &other);
  ~Serializer(void);

public:
  static uintptr_t serialize(Data *ptr);
  static Data *deserialize(uintptr_t raw);
};

#endif
