//
// Created by srigun on 8/3/20.
//

#include "shuffle.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
/** TODO: Write tests for shuffle algorithm
 * 0) reset shuffle
 * 1) No fatal failure
 * 2) Unique and not in the same order as input/reset state
 * 3) Corner cases: zero elements, 1 element, assert on repeating elements
 * 4) Fair probability
 *      100 -> 10000 -> buckets at each index -
 *          At 0th index [0->~100, 1->~100 ...]
 */

TEST(Shuffle, reset) {
    std::vector<int> list{3, 4, 2, 1};
    // TODO Why dies vector<int>& not pass by reference here
    Shuffle shuffle1(list);
    list[2] = 99;
    auto shuffled_vec = shuffle1.shuffle();

    //ASSERT_THAT (shuffled_vec, {3,4,2,1});
    //EXPECT_EQ( {shuffled_vec[0], shuffled_vec[1], shuffled_vec[2],  shuffled_vec[3]}, {3,4,2,1} )
    EXPECT_NE(shuffled_vec[0], list[0]);
    shuffled_vec = shuffle1.reset();
    EXPECT_THAT(shuffled_vec, testing::ElementsAre(3,4,2,1));
    }

TEST(Shuffle, check_fatal_exit){
    //Shuffle shuffle1(std::reference_wrapper<std::vector<int>>({3,4,2,1}));
    EXPECT_NO_FATAL_FAILURE(Shuffle({3,4,2,1}));
    Shuffle shuffle1{{3,4,2,1}};
    EXPECT_NO_FATAL_FAILURE(shuffle1.shuffle());
    EXPECT_NO_FATAL_FAILURE(shuffle1.reset());
    std::cout << "\n";
    // TODO check if vector is passed by value or reference independent of & in the definition
}

TEST(Shuffle, check_exceptions){
    //EXPECT_THAT(Shuffle({3,4,2,1,6,5}),             Shuffle({3,4}));
}

// Delete this line later: Test git push https to ssh change