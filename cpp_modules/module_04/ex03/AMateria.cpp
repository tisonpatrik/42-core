#include "AMateria.hpp"

AMateria::AMateria(void) : type("") {}

AMateria::AMateria(std::string const &type) : type(type) {}

AMateria::AMateria(const AMateria &other) : type(other.type) {}

// Copying the type doesn't make sense, an Ice stays an Ice
AMateria &AMateria::operator=(const AMateria &other) {
  (void)other;
  return *this;
}

AMateria::~AMateria(void) {}

std::string const &AMateria::getType() const { return this->type; }

void AMateria::use(ICharacter &target) { (void)target; }
