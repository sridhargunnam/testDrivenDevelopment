//
// Created by srigun on 8/3/20.
//

#include "shuffle.h"

void CallShuffle(){

    // Init an array with set 1, 2, and 3.
    std::vector<int> nums{1,2,3};
    Solution solution(nums);

    // Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
    auto result = solution.shuffle();
    for (auto i:result){
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Resets the array back to its original configuration [1,2,3].
    solution.reset();

    // Returns the random shuffling of array [1,2,3].
    solution.shuffle();



}