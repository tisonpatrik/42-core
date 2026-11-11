#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "AMateria.hpp"
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
private:
  AMateria *templates[4];

  void clearTemplates(void);
  void copyTemplates(const MateriaSource &other);

public:
  MateriaSource(void);
  MateriaSource(const MateriaSource &other);
  MateriaSource &operator=(const MateriaSource &other);
  ~MateriaSource(void);

  void learnMateria(AMateria *m);
  AMateria *createMateria(std::string const &type);
};

#endif
