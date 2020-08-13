//
// Created by srigun on 8/3/20.
//

#include "shuffle.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <numeric> // for iota
#include <algorithm> // shuffle
#include <random> // random_device
/** TODO: Write tests for shuffle algorithm
 * 0) reset shuffle
 * 1) No fatal failure
 * 2) Unique and not in the same order as input/reset state
 * 3) Corner cases: zero elements, 1 element, assert on repeating elements
 * 4) Fair probability
 *      100 -> 10000 -> buckets at each index -
 *          At 0th index [0->~100, 1->~100 ...]
 */

TEST(Shuffle, DISABLED_reset) {
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

TEST(Shuffle, DISABLED_check_fatal_exit){
    //Shuffle shuffle1(std::reference_wrapper<std::vector<int>>({3,4,2,1}));
    std::vector<int> list{3, 4, 2, 1};
    Shuffle shuffle1(list);
    EXPECT_NO_FATAL_FAILURE(shuffle1);

    std::cout << "\n";
    // TODO check if vector is passed by value or reference independent of & in the definition
}

// Observation: After N shuffles, where N is the size of the list, repeats the pattern
TEST(Shuffle, shuffling_quotient){
    constexpr std::size_t N=1000;
    std::vector<int> input(N);
    std::iota(input.begin(),input.end(),1);
    std::vector<int> original{input};

    std::shuffle(input.begin(),input.end(), std::mt19937{std::random_device{}()});
    Shuffle shuffle1{input};
    shuffle1.shuffle();

    int total_matches = std::inner_product(input.cbegin(), input.cend(), original.cbegin(), 0,
                                            std::plus<>(), std::equal_to<>());

    std::cout << "total matches " << total_matches << std::endl;
    const auto expected_matching_quotient = 1.0f;
    float actual_matching_quotient = ( static_cast<float>(N-total_matches) / ((float)(N)) );
    EXPECT_NEAR(actual_matching_quotient, expected_matching_quotient, 0.05);
}