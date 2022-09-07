#include "../2020.hpp"
using namespace std;

#define TWENTY_EIGHT_ZEROS "0000000000000000000000000000"

class IDecoder {
 public:
  size_t count() {
    size_t sum = 0;
    for (auto &i : _mem) {
      sum += i.second;
    }
    return sum;
  }

 protected:
  string _mask;
  map<size_t, size_t> _mem;
  virtual void decode(smatch &match) = 0;
  void init(vector<string> &input) {
    for (size_t i = 0; i < input.size(); i++) {
      smatch match;
      if (regex_match(input[i], match, regex(R"(mask = ([X10]{36}))"))) {
        _mask = TWENTY_EIGHT_ZEROS + match[1].str();
      } else if (regex_match(input[i], match,
                             regex(R"(mem\[([0-9]+)\] = ([0-9]+))"))) {
        decode(match);
      } else {
        cout << "String not recognized: " << input[i] << endl;
      }
    }
  }
};

class DecoderA : public IDecoder {
 public:
  explicit DecoderA(vector<string> input) { init(input); }
  ~DecoderA() {}

 private:
  void decode(smatch &match) override {
    _mem.insert_or_assign(stoi(match[1].str()),
                          applyMask(stoi(match[2].str())));
  }
  size_t applyMask(size_t num) {
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
class DecoderB : public IDecoder {
 public:
  explicit DecoderB(vector<string> input) { init(input); }
  ~DecoderB() {}

 private:
  void decode(smatch &match) override {
    const string addrMask = getAddrMask(stoi(match[1].str()));
    auto addresses = getAddresses(addrMask);
    size_t value = stoi(match[2].str());
    for (auto &addr : addresses) {
      _mem.insert_or_assign(addr, value);
    }
  }
  const string getAddrMask(size_t num) {
    string masked;
    bitset<SIZE_WIDTH> b(num);

    for (size_t i = 0; i < SIZE_WIDTH; i++) {
      if (_mask.at(i) == '1') {
        masked.push_back('1');
      } else if (_mask.at(i) == 'X') {
        masked.push_back('X');
      } else {
        if (b.test(SIZE_WIDTH - i - 1)) {
          masked.push_back('1');
        } else {
          masked.push_back('0');
        }
      }
    }
    return masked;
  }

  vector<size_t> getAddresses(const string &mask) {
    vector<size_t> addresses(1, 0);
    vector<size_t> tmp;

    for (size_t i = 0; i < SIZE_WIDTH; i++) {
      if (mask.at(i) == '1') {
        for (auto &&addr : addresses) {
          addr += pow(2, SIZE_WIDTH - i - 1);
        }
      } else if (mask.at(i) == 'X') {
        tmp.clear();
        for (auto &&addr : addresses) {
          tmp.push_back(addr + pow(2, SIZE_WIDTH - i - 1));
        }
        addresses.insert(addresses.end(), tmp.begin(), tmp.end());
      }
    }
    return addresses;
  }
};

std::string y2020::solve_14a(const std::vector<std::string> &input) {
  DecoderA prog(input);
  return to_string(prog.count());
}

std::string y2020::solve_14b(const std::vector<std::string> &input) {
  DecoderB prog(input);
  return to_string(prog.count());
}
