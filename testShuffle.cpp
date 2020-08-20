//
// Created by srigun on 8/3/20.
//

#include <cmath>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "shuffle.h"
#include "testShuffleHelper.h"

/** Tests for shuffle algorithm
 * 0) reset shuffle -> DONE
 * 1) No fatal failure -> DONE
 * 2) Unique and not in the same order as input/reset state -> DONE
 * 3) Corner cases: zero elements, 1 element, assert on repeating elements -> DONE
 * 4) Fair probability -> DONE
 *      100 -> 10000 -> buckets at each index -
 *          At 0th index [0->~100, 1->~100 ...]
 */

TEST(Shuffle, reset) {
  std::vector<int> list{3, 4, 2, 1};
  std::vector<int> copy_of_list{3,4,2,1};
  Shuffle shuffle1(list);
  auto shuffled_vec = shuffle1.DoShuffle();
  shuffled_vec = shuffle1.Reset();
  EXPECT_THAT(shuffled_vec, testing::ElementsAre(3, 4, 2, 1));
}

TEST(Shuffle, check_fatal_exit) {
  std::vector<int> list{3, 4, 2, 1};
  Shuffle shuffle1(list);
  EXPECT_NO_FATAL_FAILURE(shuffle1);
}

// Observation: After N shuffles, where N is the size of the list, repeats the
// pattern
// TODO brace vs (), i.e copy constructor vs list initialization
TEST(Shuffle, shuffling_quotient) {
  constexpr std::size_t N = 100;
  std::vector<int> input{CreateShuffleTestVector(N)};
  std::vector<int> original_input_copy{input};
  Shuffle shuffle1{input};
  auto output = shuffle1.DoShuffle();

  int total_matches = std::inner_product(output.cbegin(), output.cend(),
                                         original_input_copy.cbegin(), 0,
                                         std::plus<>(), std::equal_to<>());

  std::cout << "total matches " << total_matches << std::endl;
  const auto expected_matching_quotient = 1.0f;
  float actual_matching_quotient =
      (static_cast<float>(N - total_matches) / ((float)(N)));
  EXPECT_NEAR(actual_matching_quotient, expected_matching_quotient, 0.25);
}

// Corner cases: zero elements, 1 element, assert on repeating elements
TEST(Shuffle, CornerCasesZeroElement) {
  std::vector<int> list{};
  testing::internal::CaptureStdout();
  Shuffle shuffle1{list};
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "zero elements. Please give a non-zero vector\n");
}

TEST(Shuffle, CornerCasesOneElement) {
  constexpr std::size_t N = 1;
  std::vector<int> input{CreateShuffleTestVector(N)};
  std::vector<int> original_input_copy{input};
  testing::internal::CaptureStdout();

  Shuffle shuffle1{input};
  std::string std_output = testing::internal::GetCapturedStdout();
  auto output = shuffle1.DoShuffle();

  EXPECT_EQ(std_output, "only one element, nothing to shuffle\n");
}


TEST(Shuffle, FairProbability) {
  constexpr std::size_t kN = 5;
  constexpr std::size_t kTotalSamples = 10000;
  std::vector<int> input{CreateShuffleTestVector(kN)};

  Shuffle shuffle_1{input};
  std::vector<std::vector<int>> buckets(kN, std::vector<int>(kN, 0));
  for (int i = 0; i < kTotalSamples; ++i) {
    auto output = shuffle_1.DoShuffle();
    for (auto j = 0; j < output.size(); j++) {
      auto temp = output[j];
      buckets[j][temp] += 1;
    }
  }

  float error_margin_ration = 0.05;
  std::vector<std::vector<float>> acceptance_ration_vec( kN,
                                                        std::vector<float>(kN, 0));
  // Collect into buckets
  for (auto i = 0; i < buckets.size(); i++) {
    for (auto j = 0; j < buckets[i].size(); j++) {
      float occurance_ratio =
          (buckets[i][j] / ((float)(kTotalSamples) / (float)kN));
      float error_ratio = std::abs((1 - occurance_ratio));
      std::cout << error_ratio << " ";
      EXPECT_NEAR(error_ratio, 0.05, 0.15);
    }
    std::cout << "\n";
  }
}
// std::move example
// https://godbolt.org/z/rK9G66
