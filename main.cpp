#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <bitset> //day 5

#include "Task.hpp"

using namespace std;

#define ERROR_STRING "ERROR"

int stoiWrap(const string &str) { return stoi(str); }

//
// DAY 1
//

const string solve_01a(vector<string> input) {
  size_t size = input.size();
  vector<int> data(size);
  transform(input.begin(), input.end(), data.begin(), stoiWrap);

  for (size_t i = 0; i < size; i++) {
    for (size_t j = i + 1; j < size; j++) {
      if ((data[i] + data[j]) == 2020) return to_string(data[i] * data[j]);
    }
  }
  return ERROR_STRING;
}

const string solve_01b(vector<string> input) {
  size_t size = input.size();
  vector<int> data(size);
  transform(input.begin(), input.end(), data.begin(), stoiWrap);

  for (size_t i = 0; i < size; i++) {
    for (size_t j = i + 1; j < size; j++) {
      for (size_t k = j + 1; k < size; k++) {  // stick to the plan!
        if ((data[i] + data[j] + data[k]) == 2020) {
          return to_string(data[i] * data[j] * data[k]);
        }
      }
    }
  }
  return ERROR_STRING;
}

//
// DAY 2
//

const string solve_02a(vector<string> input) {
  // groups: 1 - min, 2 - max, 3 - char, 4 - string
  regex reg(R"(^([0-9]+)-([0-9]+)\s([a-z]?):\s([a-z]+)$)");
  smatch groups;
  size_t correct_passwords = 0;
  for (size_t i = 0; i < input.size(); i++) {
    regex_match(input[i], groups, reg);
    size_t num =
        count(groups[4].first, groups[4].second, groups[3].str().at(0));
    if ((num >= stoi(groups[1].str())) && (num <= stoi(groups[2].str()))) {
      correct_passwords++;
    }
  }
  return to_string(correct_passwords);
}

const string solve_02b(vector<string> input) {
  // groups: 1 - pos 1, 2 - pos 2, 3 - char, 4 - string
  regex reg(R"(^([0-9]+)-([0-9]+)\s([a-z]?):\s([a-z]+)$)");
  smatch groups;
  size_t correct_passwords = 0;
  for (size_t i = 0; i < input.size(); i++) {
    regex_match(input[i], groups, reg);
    size_t pos1 = stoi(groups[1].str()) - 1;
    size_t pos2 = stoi(groups[2].str()) - 1;
    char c = groups[3].str().at(0);
    string str = groups[4].str();

    if (!(str.at(pos1) == c) != !(str.at(pos2) == c)) {
      correct_passwords++;
    }
  }
  return to_string(correct_passwords);
}

//
// DAY 3
//

class Toboggan {
 public:
  Toboggan() : _x{0}, _y{0} {}
  Toboggan(int x, int y) : _x{x}, _y{y} {}
  ~Toboggan() {}

  bool move(int x, int y, size_t width, size_t height) {
    int x_new = _x + x;
    int y_new = _y + y;

    if ((x_new < 0) || (y_new < 0) || (y_new >= height)) return false;

    if (x_new >= width) x_new -= width;

    _x = x_new;
    _y = y_new;
    return true;
  }

  int getX() { return _x; }

  int getY() { return _y; }

 private:
  int _x;
  int _y;
};

size_t count_trees(vector<string> &input, int moveX, int moveY) {
  size_t height = input.size();
  size_t width = input[0].length();
  size_t trees = 0;
  Toboggan t = Toboggan();

  while (t.move(moveX, moveY, width, height)) {
    if (input[t.getY()].at(t.getX()) == '#') trees++;
  }

  return trees;
}

const string solve_03a(vector<string> input) {
  return to_string(count_trees(input, 3, 1));
}

const string solve_03b(vector<string> input) {
  size_t result = 1;
  result *= count_trees(input, 1, 1);
  result *= count_trees(input, 3, 1);
  result *= count_trees(input, 5, 1);
  result *= count_trees(input, 7, 1);
  result *= count_trees(input, 1, 2);
  return to_string(result);
}

//
// DAY 4
//

const string solve_04a(vector<string> input) {
  string data = string();
  size_t fields;
  size_t valid_passports = 0;

  for (int i = 0; i < input.size(); i++) {
    if (!(input[i].empty())) {
      data.append(input[i]);
    } else {
      fields = count(data.begin(), data.end(), ':');
      if (fields > 8) return ERROR_STRING;
      if (fields == 8) valid_passports++;
      if ((fields == 7) && (!regex_search(data, regex("cid")))) {
        valid_passports++;
      }
      data.clear();
    }
  }

  return to_string(valid_passports);
}

int16_t ToInt(ssub_match m) {
  return stoi(m.str());
}

// input should end with empty string for correct processing
const string solve_04b(vector<string> input) {
  string data = string();
  size_t valid_passports = 0;
  smatch match;
  for (int i = 0; i < input.size(); i++) {
    if (input[i].empty()) {
      if (!(regex_search(data, match, regex(R"(byr:([0-9]+)[ $])"))) ||
          (ToInt(match[1]) < 1920) || (ToInt(match[1]) > 2002)) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, match, regex(R"(iyr:([0-9]+)[ $])"))) ||
          (ToInt(match[1]) < 2010) || (ToInt(match[1]) > 2020)) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, match, regex(R"(eyr:([0-9]+)[ $])"))) ||
          (ToInt(match[1]) < 2020) || (ToInt(match[1]) > 2030)) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, match, regex(R"(hgt:([0-9]+)(cm|in)[ $])"))) ||
          (ToInt(match[1]) < 59) || (ToInt(match[1]) > 193) ||
          ((ToInt(match[1]) < 150) && (match[2].str() == "cm")) ||
          ((ToInt(match[1]) > 76) && (match[2].str() == "in"))) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, regex(R"(hcl:#[0-9a-f]{6}[ $])")))) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, regex(R"(ecl:(amb|blu|brn|gry|grn|hzl|oth)[ $])")))) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, regex(R"(pid:[0-9]{9}[ $])")))) {
        data.clear();
        continue;
      }
      data.clear();
      valid_passports++;
    } else {
      data.append(input[i]);
      data.append(" ");
    }
  }
  return to_string(valid_passports);
}

//
// DAY 5
// 

ulong count_seat_id(string input) {
  string row = input.substr(0, 7);
  string col = input.substr(7, 3);
  replace(row.begin(), row.end(), 'F', '0');
  replace(row.begin(), row.end(), 'B', '1');
  replace(col.begin(), col.end(), 'L', '0');
  replace(col.begin(), col.end(), 'R', '1');
  return bitset<8>(row).to_ulong() * 8 + bitset<8>(col).to_ulong();
}

const string solve_05a(vector<string> input) {
  ulong max_id = 0;
  ulong current_id = 0;
  for (size_t i = 0; i<input.size(); i++) {
    current_id = count_seat_id(input[i]);
    if (current_id > max_id) max_id = current_id;
  }
  return to_string(max_id);
}

const string solve_05b(vector<string> input) {
  ulong current_id = 0;
  //could use 05a output, but independence is more valuable 
  const uint16_t max_id = 128*8 - 1; 
  ulong min_id = max_id;
  bitset<max_id> b;
  b.set();
  for (size_t i = 0; i<input.size(); i++) {
    current_id = count_seat_id(input[i]);
    b[current_id] = false;
    if (current_id < min_id) min_id = current_id;
  }
  b = b >> min_id;
  return to_string(b._Find_first() + min_id);
}

int main() {
  Task t = Task();
  t.execute("01a", solve_01a);
  t.execute("01b", solve_01b);

  t.execute("02a", solve_02a);
  t.execute("02b", solve_02b);

  t.execute("03a", solve_03a);
  t.execute("03b", solve_03b);

  t.execute("04a", solve_04a);
  t.execute("04b", solve_04b);

  t.execute("05a", solve_05a);
  t.execute("05b", solve_05b);
  return 0;
}