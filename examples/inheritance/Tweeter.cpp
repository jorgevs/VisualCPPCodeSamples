#include "Tweeter.hpp"

Tweeter::Tweeter(std::string name, std::string lastName, int age, int numTweets) :
        Person(name, lastName, age), numTweets(numTweets) {
    std::cout << "Running Tweeter constructor" << std::endl;
}

Tweeter::~Tweeter() {
    std::cout << "Running Tweeter destructor" << std::endl;
}

int Tweeter::getNumTweets() {
    return this->numTweets;
}


int main(){
    Tweeter tweeter("Jorge", "Vazquez", 41, 999);
    std::cout << "Name: " << tweeter.getName() << ", Age: " << tweeter.getAge() << ", numTweets: " << tweeter.getNumTweets() << std::endl;
}