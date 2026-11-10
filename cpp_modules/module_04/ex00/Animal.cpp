#include "Animal.hpp"

#include <iostream>

Animal:: Animal(void): type("Animal"){

}

Dog:: Dog(void): Animal(){
    this->type = "Dog";
}

void Dog::makeSound(){
    std::cout << "Haf!" << std::endl;
}


Cat:: Cat(void): Animal(){
    this->type = "Cat";
}

void Cat::makeSound(){
    std::cout << "Mnaou!" << std::endl;
}
