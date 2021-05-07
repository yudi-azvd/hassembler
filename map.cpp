#include <iostream>
#include <map>

std::string strToIntMapToString(std::map<std::string, int> map) {
  std::string finalString = "[";
  for (auto & pair : map) {
    finalString.append(pair.first + ": " + std::to_string(pair.second) + ", ");
  }
  return finalString + "]";
}


int main() {
  std::map<std::string, int> my_map = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
  };

  std::cout << "map 1st print" << std::endl;
  std::cout << strToIntMapToString(my_map) << std::endl;

  int a = my_map["random_string"];

  std::cout << "a: "<< a << std::endl;

  std::cout << "\nmap 1st print" << std::endl;
  std::cout << strToIntMapToString(my_map) << std::endl;

  int b = my_map.at("second random_string");

  std::cout << "b: "<< b << std::endl;

  std::cout << "\nmap 1st print" << std::endl;
  std::cout << strToIntMapToString(my_map) << std::endl;

  return 0;
}