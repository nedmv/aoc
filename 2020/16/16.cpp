#include "../2020.hpp"
using namespace std;

class Field {
 public:
  Field(string &input) {
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

bool checkRanges(vector<uint32_t> &values, vector<Field> &fields, vector<vector<bool>> &checks) {
  size_t size = fields.size();
  size_t counter;
  uint32_t value;
  for (size_t i = 0; i < size; ++i) {
    value = values[i];
    counter = 0;
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

void mergeChecks(vector<vector<bool>> &in, vector<vector<bool>> &merged) {
  size_t size = in.size();
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (in[i][j] != merged[i][j]) {
        merged[i][j] = false;
      }
    }
  }
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
  Ticket(string s) {
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

const std::string y2020::solve_16b(std::vector<std::string> input) {
  vector<Field> fields;
  size_t i = 0;

  while (!input[i].empty()) {
    fields.push_back(Field(input[i]));
    i++;
  }

  i += 2;

  auto myTicket = loadTicket(input[i]);
  size_t size = myTicket.size();

  i += 3;

  vector<uint32_t> ticket;

  vector<vector<bool>> possibleChecks(size, vector<bool>(size, true));
  vector<vector<bool>> currentChecks(size, vector<bool>(size, false));

  for (i; i < input.size(); i++) {
    ticket = loadTicket(input[i]);
    if (checkRanges(ticket, fields, currentChecks)) {

    }

  }

  return ERROR_STRING;
}
