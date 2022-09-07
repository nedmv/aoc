#include "../2020.hpp"
using namespace std;

class Field {
 public:
  explicit Field(string &input) {
    smatch match;
    if (regex_match(
            input, match,
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
  bool inRange(uint32_t x) {
    return ((x >= _min1) && (x <= _max1)) || ((x >= _min2) && (x <= _max2));
  }

  const string getName() {
    return _name;
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

bool checkRanges(const vector<uint32_t> &values, vector<Field> &fields, vector<vector<bool>> &checks) {
  size_t size = fields.size();
  for (size_t i = 0; i < size; ++i) {
    uint32_t value = values[i];
    size_t counter = 0;
    for (size_t j = 0; j < size; ++j) {
      if (fields[j].inRange(value)) {
        checks[i][j] = true;
        counter++;
      }
    }
    if (!counter) return false;
  }
  return true;
}

class Checklist {
  public:
  explicit Checklist(size_t size):
    _checks{vector(size, vector<bool>(size, true))},
    _counters{vector(size, size)} {}
  ~Checklist() {}

  bool merge(const Checklist &list) {
    size_t size = _checks.size();
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        if (_checks[i][j] != list._checks[i][j]) {
          _checks[i][j] = false;
          _counters[i]--;
        }
      }
      cout << _counters[i] << ' ';
    }
    cout << endl;
    return check_counters();
  }

  bool check_counters() { 
    for (auto &c : _counters) {
      if (c != 1) return false;
    }
    return true;
    }

  vector<size_t> getDepartureIndices(vector<Field> &fields) {
    vector<size_t> result;
    for (size_t i = 0; i < fields.size(); i++) {
      if (fields[i].getName().find("departure") != string::npos) {
        for (size_t j = 0; j < _checks.size(); j++) {
          if (_checks[i][j]) { 
            result.push_back(j);
          }
        }
      }
    }
    return result;
  }

  bool checkRanges(vector<uint32_t> values, vector<Field> &fields) {
  size_t size = fields.size();
  for (size_t i = 0; i < size; ++i) {
    uint32_t value = values[i];
    _counters[i] = 0;
    for (size_t j = 0; j < size; ++j) {
      if (fields[j].inRange(value)) {
        _checks[i][j] = true;
        _counters[i]++;
      } else {
        _checks[i][j] = false;
      }
    }
    if (!_counters[i]) return false;
  }
  return true;
}
  protected:
    vector<vector<bool>> _checks;
    vector<size_t> _counters;
};

bool inRanges(uint32_t x, vector<Field> &fields) {
  for (bool check : checkRanges(x, fields)) {
    if (check) return true;
  }
  return false;
}

std::string y2020::solve_16a(const std::vector<std::string> &input) {
  vector<Field> fields;
  size_t i = 0;

  while (!input[i].empty()) {
    fields.push_back(Field(const_cast<std::string &>(input[i])));
    i++;
  }

  while (input[i] != "nearby tickets:") {
    i++;
  }
  i++;

  string s;
  size_t num;
  size_t sum = 0;

  for (; i < input.size(); i++) {
    s = input[i];
    size_t begin = 0;
    size_t end = s.find(",", begin);
    while (true) {
      num = stoi(s.substr(begin, end - begin));
      cout << num << " ";
      if (!inRanges(num, fields)) {
        sum += num;
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

class Ticket {
 public:
  explicit Ticket(string s) {
    size_t begin = 0;
    size_t end = s.find(",", begin);
    while (true) {
      _values.push_back(stoi(s.substr(begin, end - begin)));
      if (end == s.npos) {
        break;
      }
      begin = end + 1;
      end = s.find(",", begin);
    }
  }
  bool isValid(vector<Field> &fields) {
    for (auto &value : _values) {
      if (!inRanges(value, fields)) {
        return false;
      }
    }
    return true;
  }

 private:
  vector<uint32_t> _values;
};

vector<uint32_t> loadTicket(string &s) {
  vector<uint32_t> result;
  size_t begin = 0;
  size_t end = s.find(",", begin);
  while (true) {
    result.push_back(stoi(s.substr(begin, end - begin)));
    if (end == s.npos) {
      break;
    }
    begin = end + 1;
    end = s.find(",", begin);
  }
  return result;
}

std::string y2020::solve_16b(const std::vector<std::string> &input) {
  vector<Field> fields;
  size_t i = 0;

  while (!input[i].empty()) {
    fields.push_back(Field(const_cast<std::string &>(input[i])));
    i++;
  }

  i += 2;

  auto myTicket = loadTicket(const_cast<std::string &>(input[i]));
  size_t size = myTicket.size();

  i += 3;

  Checklist possibleChecks(size);
  Checklist currentChecks(size);

  for (; i < input.size(); i++) {
    if (currentChecks.checkRanges(loadTicket(const_cast<std::string &>(input[i])), fields) 
        && possibleChecks.merge(currentChecks)) {
          break;
    }
  }

  auto indices = possibleChecks.getDepartureIndices(fields);
  size_t result = 1;
  for (size_t k = 0; k < indices.size(); k++) {
    result *= myTicket[indices[k]];
  }

  return to_string(result);
}
