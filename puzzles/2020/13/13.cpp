// Puzzle is available at https://adventofcode.com/2020/day/13
#include "../2020.hpp"
using namespace std;

std::string y2020::solve_13a(const std::vector<std::string> &input) {
  size_t time = stoi(input[0]);
  string s = input[1];
  vector<size_t> buses;

  size_t begin = 0;
  size_t end = s.find(",");

  while (end != string::npos) {
    if (s.at(begin) != 'x') {
      buses.push_back(stoi(s.substr(begin, end - begin)));
    }
    begin = end + 1;
    end = s.find(",", begin);
  }

  size_t min = SIZE_MAX;
  size_t min_id = 0;

  for (size_t i = 0; i < buses.size(); i++) {
    size_t delay = buses[i] - time % buses[i];
    if (delay < min) {
      min = delay;
      min_id = buses[i];
    }
  }
  return to_string(min * min_id);
}

struct Bus {
  size_t num;
  size_t offset;
};

std::string y2020::solve_13b(const std::vector<std::string> &input) {
  string s = input[1];
  vector<Bus> buses;  // first = bus number, second = timestamp offset

  size_t begin = 0;
  size_t end = s.find(",");
  size_t offset = 0;
  Bus tmp;

  while (true) {
    if (s.at(begin) != 'x') {
      tmp.num = stoi(s.substr(begin, end - begin));
      tmp.offset = offset;
      buses.push_back(tmp);
    }
    if (end == string::npos) break;
    offset++;
    begin = end + 1;
    end = s.find(",", begin);
  }

  sort(buses.begin(), buses.end(), [](Bus a, Bus b) { return a.num > b.num; });

  size_t time = buses[0].num - buses[0].offset;
  size_t step = buses[0].num;
  for (size_t i = 1; i < buses.size(); i++) {
    while ((time + buses[i].offset) % buses[i].num != 0) {
      time += step;
    }
    step *= buses[i].num;
  }
  return to_string(time);
}