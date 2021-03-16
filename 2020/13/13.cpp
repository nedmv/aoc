#include "../2020.hpp"
using namespace std;

const std::string y2020::solve_13a(std::vector<std::string> input) {
  size_t time = stoi(input[0]);
  string s = input[1];
  vector<size_t> buses;

  size_t begin = 0;
  size_t end = s.find(",");

  while (end != s.npos) {
    if (s.at(begin) != 'x') {
      buses.push_back(stoi(s.substr(begin, end - begin)));
    }
    begin = end + 1;
    end = s.find(",", begin);
  };

  size_t min= SIZE_MAX;
  size_t min_id = 0;
  size_t delay;

  for (size_t i = 0; i < buses.size(); i++) {
    delay = buses[i] - time % buses[i];
    if (delay < min) {
      min = delay;
      min_id = buses[i];
    } 
  }
  return to_string(min * min_id);
}


// const std::string y2020::solve_13b(std::vector<std::string> input);