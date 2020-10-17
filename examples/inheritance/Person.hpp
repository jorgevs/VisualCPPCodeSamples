#pragma once

#include <string>
#include <iostream>

class Person {

private:
    int age;
    std::string name;
    std::string lastName;

public:
    Person(std::string name, std::string lastName, int age);

    ~Person();

    int getAge();

    std::string getName();
};
