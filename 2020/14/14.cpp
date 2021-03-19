#include "../2020.hpp"
using namespace std;

#define TWENTY_EIGHT_ZEROS "0000000000000000000000000000"

class Program {
 public:
  void init(vector<string> input) {
    for (size_t i = 0; i < input.size(); i++) {
      smatch match;
      if (regex_match(input[i], match, regex(R"(mask = ([X10]{36}))"))) {
        _mask = TWENTY_EIGHT_ZEROS + match[1].str();
      } else if (regex_match(input[i], match, regex(R"(mem\[([0-9]+)\] = ([0-9]+))"))) {
        _mem.insert_or_assign(stoi(match[1].str()), apply_mask(stoi(match[2].str())));
      } else {
        cout << "String not recognized: " << input[i] << endl;
      }
    }    
  }

  size_t count() {
    size_t sum = 0;
    for (auto &i : _mem) {
      //cout << i.second << endl;
      sum += i.second;
    }
    return sum;
  }

 private: 
  string _mask;
  map<size_t, size_t> _mem;

  size_t apply_mask(size_t num) {
    bitset<SIZE_WIDTH> b(num);
    for (size_t i = 0; i < SIZE_WIDTH; i++) { 
      if (_mask.at(i) == '1') {
        b.set(SIZE_WIDTH - i - 1); 
      } else if (_mask.at(i) == '0') {
        b.reset(SIZE_WIDTH - i - 1);
      }
    }
    return b.to_ulong();
  }
};

const std::string y2020::solve_14a(std::vector<std::string> input){
  Program prog;
  prog.init(input);

  return to_string(prog.count());
}

const std::string y2020::solve_14b(std::vector<std::string> input){


  return ERROR_STRING;
}

