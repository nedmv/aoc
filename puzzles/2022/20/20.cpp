// Puzzle is available at https://adventofcode.com/2022/day/20
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

long long grove_sum(const std::vector<std::string> &input, int times = 1,
                    long long key = 1) {
  vector<long long> nums;
  for (int i = 0; i < input.size(); i++) {
    if (!input[i].empty()) {
      nums.push_back(stoll(input[i]));
    }
  }
  long long size = nums.size();

  for (int i = 0; i < size; ++i) {
    nums[i] *= key;
  }

  vector<long long> mix = nums;

  vector<long long> poses;
  for (long long i = 0; i < nums.size(); i++) {
    poses.push_back(i);
  }

  for (int turn = 0; turn < times; turn++) {
    for (int i = 0; i < size; i++) {
      long long steps = nums[i];
      long long n = steps;
      long long pos = poses[i];
      long long newPos = 0;

      if (steps == 0) {
        continue;
      }

      newPos = (pos + steps % (size - 1)) % (size - 1);
      if (newPos < 0) {
        newPos += size - 1;
      }

      if (newPos >= size && steps > 0) {
        newPos++;
      }
      if (newPos <= 0 && steps < 0) {
        newPos--;
      }
      newPos %= size;
      if (newPos < 0) {
        newPos += size;
      }

      if (newPos < pos) {
        for (int k = pos; k > newPos; --k) {
          swap(mix[k], mix[k - 1]);
        }
        for (long long k = 0; k < size; ++k) {
          if (newPos <= poses[k] && poses[k] < pos) {
            poses[k]++;
          }
        }
      }
      if (newPos > pos) {
        for (long long k = pos; k < newPos; ++k) {
          swap(mix[k], mix[k + 1]);
        }
        for (long long k = 0; k < size; ++k) {
          if (newPos >= poses[k] && poses[k] > pos) {
            poses[k]--;
          }
        }
      }
      poses[i] = newPos;
    }
  }

  int pos = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (mix[i] == 0) {
      pos = i;
      break;
    }
  }

  long long n1 = mix[(pos + 1000) % nums.size()];
  long long n2 = mix[(pos + 2000) % nums.size()];
  long long n3 = mix[(pos + 3000) % nums.size()];
  long long s = n1 + n2 + n3;
  return s;
}

std::string y2022::solve_20a(const std::vector<std::string> &input) {
  return to_string(grove_sum(input));
}

std::string y2022::solve_20b(const std::vector<std::string> &input) {
  return to_string(grove_sum(input, 10, 811589153));
}