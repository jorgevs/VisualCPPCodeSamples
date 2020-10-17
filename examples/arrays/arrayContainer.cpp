#include <array>
#include <algorithm>
#include <iterator>
#include <iostream>

int main(void) {
    std::array<int, 10> intArray = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array<std::string, 6> strArray = {"jorge", "silvia", "beto", "miguel", "janos", "mamin"};

    // container operations are supported
    std::sort(intArray.begin(), intArray.end());
    std::reverse_copy(strArray.begin(), strArray.end(), std::ostream_iterator<std::string>(std::cout, " "));

    std::cout << '\n';

    // ranged for loop is supported
    for (const auto &s: strArray) {
        std::cout << s << ' ';
    }

    return 0;
}