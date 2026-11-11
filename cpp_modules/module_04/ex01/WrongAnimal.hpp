#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>

class WrongAnimal {
protected:
  std::string type;

public:
  WrongAnimal(void);
  WrongAnimal(const WrongAnimal &other);
  WrongAnimal &operator=(const WrongAnimal &other);
  virtual ~WrongAnimal(void);

  const std::string &getType(void) const;
  void makeSound(void) const;
};

#endif
