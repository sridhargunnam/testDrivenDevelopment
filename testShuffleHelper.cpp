//
// Created by srigun on 8/13/20.
//


#include "testShuffleHelper.h"

std::vector<int> CreateShuffleTestVector(const std::size_t N) {
    std::vector<int> input(N,0);
    std::iota(input.begin()+1,input.end(),1);
    //std::shuffle(input.begin(), input.end(), std::mt19937{std::random_device{}()});
//    std::cout << "input addr inside create = " << &input << "\n";
//    std::cout << "input[0]   inside create = " << input[0] << "\n";
//    std::cout << "&input[0]  inside create = " << &input[0] << "\n";
    return input;
}
