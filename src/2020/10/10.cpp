#include "../2020.hpp"
using namespace std;

static vector<uint32_t> sort_adapters(const vector<string> &input) {
  vector<uint32_t> data;
  data.push_back(0);  // charger
  for (size_t i = 0; i < input.size(); i++) {
    data.push_back(stoi(input[i]));
  }
  sort(data.begin(), data.end());
  return data;
}

const std::string y2020::solve_10a(const std::vector<std::string> &input) {
  vector<uint32_t> data = sort_adapters(const_cast<std::vector<std::string>&>(input));

  size_t ones = 0;
  size_t threes = 0;
  for (size_t i = 1; i < data.size(); i++) {
    if ((data[i] - data[i - 1]) == 3) {
      ++threes;
    } else if ((data[i] - data[i - 1]) == 1) {
      ++ones;
    }
  }
  ++threes;  // device
  return to_string(threes * ones);
}

#if 0  // never use recursion here!
static size_t arrangements(int32_t n, vector<uint32_t>::iterator begin,
                           vector<uint32_t>::iterator end) {
  if (n < 0) return 0;
  if (n == 0) return 1;
  vector<uint32_t>::iterator pos = find(begin, end, n);
  if (pos == end) {
    return 0;
  } else {
    return arrangements(n - 1, begin, pos) +
           arrangements(n - 2, begin, pos) +
           arrangements(n - 3, begin, pos);
  }
}
#endif

static size_t arrangements(vector<uint32_t> &num) {
  size_t size = num.size();
  vector<size_t> value(num[size - 1], 0);

  value[0] = 1;  // 0 is guaranteed to exist.
  for (size_t i = 1; i < size; i++) {
    if (num[i] == 1) {
      value[1] = 1;
    } else if (num[i] == 2) {
      value[2] = value[0] + value[1];
    } else {
      value[num[i]] = value[num[i] - 1] + value[num[i] - 2] + value[num[i] - 3];
    }
  }
  return value[num[size - 1]];
}

const std::string y2020::solve_10b(const std::vector<std::string> &input) {
  vector<uint32_t> data = sort_adapters(const_cast<std::vector<std::string>&>(input));
  return to_string(arrangements(data));
}