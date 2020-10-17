#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

int main() {
    vector<int> nums = {0,1, 2, 3, 4, 5, 6};
    nums.push_back(7);
    nums.push_back(8);

    if(nums.empty()){
        printf("nums is empty!");
    }

    //Remove item at position 1
    nums.erase(++nums.begin());

    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] << " ";
    }

    cout << endl;

    for (int n : nums) {
        cout << n << " ";
    }

    return 0;
}