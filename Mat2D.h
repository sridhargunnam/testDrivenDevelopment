//
// Created by srigun on 8/19/20.
//

#ifndef TDD__MAT2D_H_
#define TDD__MAT2D_H_
#include <functional>
#include <vector>
/*
template<typename T>
class OutputType {
 private:
  std::vector<T> output_val_;
 public:
  explicit OutputType(const Mat2D<T>& mat2d) : output_val_(mat2d){}

};
*/
template <typename T>
class Mat2D {
 private:
    std::vector<T> pixel_;
    std::size_t rows_;
    std::size_t cols_;

 public:
    Mat2D(const std::vector<T> &pixel_, std::size_t rows, std::size_t cols) {
      this->pixel_ = pixel_;
      this->rows_  = rows;
      this->cols_  = cols;
    }
  //TODO fix it to return appropriate type

    std::vector<T> filter(Mat2D<T> kernel);
};

template<typename T>
using FunctionPtr = std::function < std::vector<T> (Mat2D<T>)>;


// Client code:
//OutputType o;
//o.add((OutputType)conv);

#endif  // TDD__MAT2D_H_
