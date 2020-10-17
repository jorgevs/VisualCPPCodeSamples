#include "Person.hpp"

// Constructor
Person::Person(std::string name, std::string lastName, int age) {
    this->name = name;
    this->lastName = lastName;
    this->age = age;

    std::cout << "Running Person constructor" << std::endl;
}

// Destructor
Person::~Person() {
    std::cout << "Running Person destructor" << std::endl;
}

int Person::getAge() {
    return this->age;
}

std::string Person::getName() {
    return this->name + " " + this->lastName;
}

/*int main() {
    Person person("Jorge", "Vazquez", 41);
    std::cout << "Name: " << person.getName() << ", Age: " << person.getAge() << std::endl;
}*/