#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal{
protected:
    std::string type;

public:
    Animal(void);
    Animal(const Animal &other);
    Animal &operator=(const Animal &other);
    virtual ~Animal(void);
    void makeSound();
};

class Dog: public Animal {
    public:
    Dog(void);
    Dog(const Dog &other);
    Dog &operator = (const Dog &other);
    virtual ~Dog(void);
    void makeSound();

};

class Cat: public Animal {
    public:
    Cat(void);
    Cat(const Cat &other);
    Cat &operator = (const Cat &other);
    virtual ~Cat(void);
    void makeSound();

};

#endif
