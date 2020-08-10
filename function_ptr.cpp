//
// Created by srigun on 8/8/20.
//

#include <iostream>
#include <string>
#include <functional>
#include <map>

// Define fp
template<typename T>
using fcn = std::function<T()>;
using fcn2 = std::string();
//template <typename T>

class A {
  public:
    int getInt(){
      return 0;
    }

    std::string getString(){
        std::string ret_str = "asd";
        return ret_str;
    }

    template<typename T>
    std::function<T()> return_function_ptr()
    {
        return this.get<T>;
    }

    template<typename T>
    void get(){

    }

    template<>
    std::string get<std::string>(){
        return "hello";
    }

    template<>
    int get<int>(){
        return 100;
    }

};


class B : public A {

  public:
    template<typename T>
    std::function<T()> getFunctor() {
       //fcn<std::string> s{this->getString()};
        //fcn<std::string> i{&getStringOutside};
        auto ret = A::return_function_ptr<T>();
        return ret;
    }

};


int main()
{
    B b;
    auto fctr_string = b.getFunctor<std::string>();
    auto str_val     = fctr_string();
    auto fctr_int    = b.getFunctor<std::string>();
    auto int_val     = fctr_int();
    std::cout << "str_val = " << str_val << "\n";
    std::cout << "int_val = " << int_val << "\n";
}