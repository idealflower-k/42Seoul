#include <iostream>
#include <cstdlib>

#include "Array.hpp"

void check(void) { system("leaks array"); }

int main(void) {
  try {
    Array<int> arr1(5);
    Array<char> arr2(5);
    Array<double> arr3(5);

    atexit(check);

    std::cout << "==test int_arr==\n";
    for (unsigned int i = 0; i < arr1.size(); i++) arr1[i] = i;
    for (unsigned int i = 0; i < arr1.size(); i++) std::cout << arr1[i] << " ";
    std::cout << "\n";

    const int test = arr1[1];
    std::cout << "test: " << test << "\n";

    std::cout << "==test char_arr==\n";
    for (unsigned int i = 0; i < arr2.size(); i++)
      arr2[i] = static_cast<char>(i + 'A');
    for (unsigned int i = 0; i < arr2.size(); i++) std::cout << arr2[i] << " ";
    std::cout << "\n";

    std::cout << "==test double_arr==\n";
    for (unsigned int i = 0; i < arr3.size(); i++) arr3[i] = ('a' + i);
    for (unsigned int i = 0; i < arr3.size(); i++)
      std::cout << std::showpoint << arr3[i] << " ";
    std::cout << "\n";

    Array<int> arr4(arr1);
    Array<int> arr5(arr4);

    // std::cout << arr4[0] << "\n";

    arr4 = arr1;
    std::cout << arr4[1] << "\n";

  } catch (std::exception &e) {
    std::cerr << e.what();
  }

  return (0);
}
