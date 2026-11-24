#include "Serializer.hpp"

Serializer::Serializer(void) {}

Serializer::Serializer(const Serializer &) {}

Serializer &Serializer::operator=(const Serializer &) { return *this; }

Serializer::~Serializer(void) {}

// A pointer and an integer are unrelated types, only reinterpret_cast can
// turn the bits of one into the other
uintptr_t Serializer::serialize(Data *ptr) {
  return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw) {
  return reinterpret_cast<Data *>(raw);
}
