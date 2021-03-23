#include "../2020.hpp"
using namespace std;

class Field {
 public:
  Field(string &input) {
    smatch match;
    if (regex_match(input, match,
                regex(R"(([^:]+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+))"))) {
      _name = match[1].str();
      _min1 = stoi(match[2].str());
      _max1 = stoi(match[3].str());
      _min2 = stoi(match[4].str());
      _max2 = stoi(match[5].str());
    } else {
      cout << "Match failed: " << input << endl;
    }
  }
  ~Field() {}
  bool inRange(uint32_t x) {
    return ((x >= _min1) && (x <= _max1)) || ((x >= _min2) && (x <= _max2));
  }

 private:
  string _name;
  uint32_t _min1;
  uint32_t _max1;
  uint32_t _min2;
  uint32_t _max2;
};

vector<bool> checkRanges(uint32_t x, vector<Field> &fields) {
  size_t size = fields.size();
  vector<bool> result(size);

  for (size_t i = 0; i < size; ++i) {
    result[i] = fields[i].inRange(x);
  }
  return result;
}

bool inRanges(uint32_t x, vector<Field> &fields) {
  for (bool check : checkRanges(x, fields)) {
    if (check) return true;
  }
  return false;
}

const std::string y2020::solve_16a(std::vector<std::string> input) {
  vector<Field> fields;
  size_t i = 0;

  while (!input[i].empty()) {
    fields.push_back(Field(input[i]));
    i++;
  }

  while (input[i] != "nearby tickets:") {
    i++;
  } 
  i++;

  string s;
  size_t begin;
  size_t end;
  size_t num;
  size_t sum = 0;

  for (i; i < input.size(); i++) {
    s = input[i];
    begin = 0;
    end = s.find(",", begin);
    while (true) {
      num = stoi(s.substr(begin, end - begin));
      cout << num << " ";
      if (!inRanges(num, fields)) {
        sum+=num;
      }
      if (end == s.npos) {
        cout << endl;
        break;
      }  
      begin = end + 1;
      end = s.find(",", begin);
    }
  }
  return to_string(sum);
}

const std::string y2020::solve_16b(std::vector<std::string> input) {
  return ERROR_STRING;
}
