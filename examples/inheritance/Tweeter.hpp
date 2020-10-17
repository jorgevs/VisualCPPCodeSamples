#pragma once

#include "../Classes/Person.hpp"
#include <string>

class Tweeter : public Person {

private:
    int numTweets;

public:
    Tweeter(std::string name, std::string lastName, int age, int numTweets);

    ~Tweeter();

    int getNumTweets();
};
