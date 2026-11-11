#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria {
public:
  Ice(void);
  Ice(const Ice &other);
  Ice &operator=(const Ice &other);
  ~Ice(void);

  AMateria *clone() const;
  void use(ICharacter &target);
};

#endif
