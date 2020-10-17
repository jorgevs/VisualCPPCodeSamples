#include <iostream>
#include <string>

int main() {

    std::cout << "Hello CMake." << std::endl;

    int length = 15;
    for (size_t i = 0; i < length; i++) {
        std::cout << "XXXXXXXX" << std::endl;
    }

    std::string strHello = "Hello, world!";
    int helloLength = strHello.length();
    std::cout << strHello << " has the following number of characters: " << helloLength << std::endl;

    return 0;
}