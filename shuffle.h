//
// Created by srigun on 8/3/20.
//

#ifndef TDD_SHUFFLE_H
#define TDD_SHUFFLE_H

#include <cassert>
#include <vector>
#include<algorithm>
#include<set>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;
class Shuffle final {
private:
    vector<int> original;
    vector<int> current;
    std::unique_ptr<vector<int>> orig_ref;
public:
    Shuffle(vector<int> &nums) : orig_ref{std::make_unique<vector<int>>(nums)}  {
        if(nums.size() > 5) {
            assert(nums.size() > 5);
        }

        srand(time(NULL));
        for(auto i: nums) {
            original.push_back(i);
            current.push_back(i);
        }
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        for(auto i=0; i<original.size(); i++)
            (*orig_ref)[i] = original[i];
        return *orig_ref;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        return  shuffle_(current);
    }

    vector<int> shuffle_(vector<int> current){
        vector<int> temp;
        set<int> track;

        int n = current.size();
        while(temp.size() < current.size()){
            int index = rand() % (n);
            if(track.find(index+1) == track.end()){
                track.insert(index+1);
                temp.push_back(current[index]);
            }
        }
        assert((*orig_ref).size() == temp.size());
        for( auto i = 0; i< (*orig_ref).size(); i++){
            (*orig_ref)[i] = temp[i];
        }
        return (*orig_ref);
    }

};

void CallShuffle();

#endif //TDD_SHUFFLE_H
