// Puzzle is available at https://adventofcode.com/2020/day/5
// Keywords: std::replace, bitset
#include "../2020.hpp"
using namespace std;

static ulong count_seat_id(string input) {
  string row = input.substr(0, 7);
  string col = input.substr(7, 3);
  replace(row.begin(), row.end(), 'F', '0');
  replace(row.begin(), row.end(), 'B', '1');
  replace(col.begin(), col.end(), 'L', '0');
  replace(col.begin(), col.end(), 'R', '1');
  return bitset<8>(row).to_ulong() * 8 + bitset<8>(col).to_ulong();
}

const std::string y2020::solve_05a(std::vector<std::string> input) {
  ulong max_id = 0;
  ulong current_id = 0;
  for (size_t i = 0; i < input.size(); i++) {
    current_id = count_seat_id(input[i]);
    if (current_id > max_id) max_id = current_id;
  }
  return to_string(max_id);
}

const std::string y2020::solve_05b(std::vector<std::string> input) {
  ulong current_id = 0;
  // could use 05a output, but independence is more valuable
  const uint16_t max_id = 128 * 8 - 1;
  ulong min_id = max_id;
  bitset<max_id> b;
  b.set();
  for (size_t i = 0; i < input.size(); i++) {
    current_id = count_seat_id(input[i]);
    b[current_id] = false;
    if (current_id < min_id) min_id = current_id;
  }
  b = b >> min_id;
  return to_string(b._Find_first() + min_id);
}
