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

using namespace std;
class Solution {
    vector<int> original;
    vector<int> current;
public:
    Solution(vector<int>& nums) {
        srand(time(NULL));
        current = nums;
        for(auto i: nums)
            original.push_back(i);
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        for(auto i=0; i<original.size(); i++)
            current[i] = original[i];
        return current;
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
        return temp;
    }

};

void CallShuffle();

#endif //TDD_SHUFFLE_H
