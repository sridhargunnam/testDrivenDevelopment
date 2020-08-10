//
// Created by srigun on 8/3/20.
//

#include "shuffle.h"
#include "gtest/gtest.h"

/** TODO: Write tests for shuffle algorithm
 * 0) reset shuffle
 * 1) No fatal failure
 * 2) Unique and not in the same order as input/reset state
 * 3) Corner cases: zero elements, 1 element, assert on repeating elements
 * 4) Fair probability
 *      100 -> 10000 -> buckets at each index -
 *          At 0th index [0->~100, 1->~100 ...]
 *
 */

TEST(Shuffle, reset) {
    std::vector<int> list{3, 4, 2, 1};
    Shuffle shuffle1(list);
    auto shuffled_vec = shuffle1.shuffle();
    //ASSERT_THAT (shuffled_vec, {3,4,2,1});
    //EXPECT_EQ( {shuffled_vec[0], shuffled_vec[1], shuffled_vec[2],  shuffled_vec[3]}, {3,4,2,1} )
    EXPECT_NE(shuffled_vec[0],3);
    shuffled_vec = shuffle1.reset();
    EXPECT_EQ(shuffled_vec[0], 3);
    }


