#include <iostream>
#include <vector>

#include "doctest/doctest.h"
#include "util/util.h"

TEST_CASE("section should") {
  std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto vec2 = std::vector<int>(vec1.begin()+5, vec1.end());
  // vec2.insert(vec2.end(), vec1.begin(), vec1.end()-5);

  // for (auto i : vec2) {
  //   std::cout << i << " ";
  // }
  // std::cout << std::endl;

  // std::vector<int> vec2 = vec1;
  // std::cout << &vec1 << std::endl;
  // std::cout << &vec2 << std::endl;
}
