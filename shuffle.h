//
// Created by srigun on 8/3/20.
//

#ifndef TDD_SHUFFLE_H
#define TDD_SHUFFLE_H

#include <cassert>
#include <vector>
#include <set>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <numeric> // for iota
#include <algorithm> // shuffle
#include <random>
#include <chrono>

using namespace std;
// TODO why smart pointers do deep copy in the constructor
// https://stackoverflow.com/questions/43259311/create-shared-ptr-without-copying-instance/43261967
class [[maybe_unused]] ShuffleSmart final {
private:
    vector<int> original_for_reset;
    std::shared_ptr<vector<int>> current_p;
    //std::unique_ptr<vector<int>> orig_ref;
public:
 ShuffleSmart(vector<int> &nums) :  current_p{std::make_shared<vector<int>>(nums)} {

        if(nums.empty()){
            std::cout << "zero elements. Please give a non-zero vector" << std::endl;
            return;
        }

        for(auto i: nums) {
            original_for_reset.push_back(i);
        }

    }

    /** Resets the array to its original configuration and return it. */
    [[nodiscard]] vector<int>& reset() {
        for(auto i=0; i<original_for_reset.size(); i++)
            (*current_p.get())[i] = original_for_reset[i];
        return *current_p.get();
    }

    /** Returns a random shuffling of the array. */
    [[nodiscard]] vector<int>& shuffle() {
        set<int> track;
        int n = (*current_p.get()).size();
        srand(time(NULL));
        for(int i=0; i< (*current_p.get()).size(); i++){
            int index1 = rand() % (n);
            int index2 = rand() % (n);
            std::swap((*current_p.get())[index1], (*current_p.get())[index2]);
        }
        return *current_p;
    }

};


class Shuffle final {
private:
    vector<int> original_for_reset_;
    vector<int> * current_p_;
    //std::unique_ptr<vector<int>> orig_ref;
public:
    Shuffle(vector<int> &nums) : current_p_{&nums} {

        if(nums.empty()){
            std::cout << "zero elements. Please give a non-zero vector" << "\n";
            return;
        }

        if(nums.size() == 1){
            std::cout << "only one element, nothing to shuffle" << "\n";
            return;
        }

        for(auto i: nums) {
          original_for_reset_.push_back(i);
        }

    }

    /** Resets the array to its original configuration and return it. */
    [[nodiscard]] vector<int>& Reset() {
        for(auto i=0; i< original_for_reset_.size(); i++)
            (*current_p_)[i] = original_for_reset_[i];
        return *current_p_;
    }

    /** Returns a random shuffling of the array. */
    [[nodiscard]] vector<int>& DoShuffle() {
        set<int> track;
        int n = (*current_p_).size();
        srand(time(NULL));
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle((*current_p_).begin(), (*current_p_).end(),  std::default_random_engine(seed));
        return *current_p_;
    }
};

#endif //TDD_SHUFFLE_H
