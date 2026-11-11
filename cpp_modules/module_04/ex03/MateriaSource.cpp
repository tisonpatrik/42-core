#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void) {
  for (int i = 0; i < 4; i++)
    this->templates[i] = 0;
}

MateriaSource::MateriaSource(const MateriaSource &other) {
  for (int i = 0; i < 4; i++)
    this->templates[i] = 0;
  this->copyTemplates(other);
}

MateriaSource &MateriaSource::operator=(const MateriaSource &other) {
  if (this != &other) {
    this->clearTemplates();
    this->copyTemplates(other);
  }
  return *this;
}

MateriaSource::~MateriaSource(void) { this->clearTemplates(); }

void MateriaSource::clearTemplates(void) {
  for (int i = 0; i < 4; i++) {
    delete this->templates[i];
    this->templates[i] = 0;
  }
}

void MateriaSource::copyTemplates(const MateriaSource &other) {
  for (int i = 0; i < 4; i++) {
    if (other.templates[i])
      this->templates[i] = other.templates[i]->clone();
  }
}

// Keeps the Materia it gets and deletes it later, so `learnMateria(new Ice())`
// doesn't leak. When the memory is full, the Materia is deleted right away.
void MateriaSource::learnMateria(AMateria *m) {
  if (!m)
    return;
  for (int i = 0; i < 4; i++) {
    if (this->templates[i] == m)
      return;
  }
  for (int i = 0; i < 4; i++) {
    if (!this->templates[i]) {
      this->templates[i] = m;
      return;
    }
  }
  delete m;
}

AMateria *MateriaSource::createMateria(std::string const &type) {
  for (int i = 0; i < 4; i++) {
    if (this->templates[i] && this->templates[i]->getType() == type)
      return this->templates[i]->clone();
  }
  return 0;
}
