// Puzzle is available at https://adventofcode.com/2023/day/5
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

struct Range {
  long long dst_start;
  long long src_start;
  long long range;
};

long long convert(const vector<Range> &ranges, long long src) {
  for (const auto &r : ranges) {
    if ((r.src_start <= src) && (src < r.src_start + r.range)) {
      return r.dst_start - r.src_start + src;
    }
  }
  return src;
}

std::string y2023::solve_05a(const std::vector<std::string> &input) {
  long long ans;

  vector<long long> seeds = ints(input[0]);
  vector<vector<Range>> m;
  m.push_back(vector<Range>());
  int map_id = 0;
  for (int i = 3; i < input.size(); ++i) {
    if (input[i].size() == 0) {
      ++map_id;
      m.push_back(vector<Range>());
    } else if (isdigit(input[i][0])) {
      auto nums = ints(input[i]);
      Range r = {nums[0], nums[1], nums[2]};
      m[map_id].push_back(r);
    }
  }
  ans = LONG_LONG_MAX;
  for (long long s : seeds) {
    for (const auto &ranges : m) {
      if (ranges.size() > 0) {
        s = convert(ranges, s);
      }
    }
    ans = min(ans, s);
  }

  return to_string(ans);
}

#if 1
vector<Range> convert2(const vector<Range> &ranges, vector<Range> &src) {
  vector<Range> dst;
  for (const auto &r : ranges) {
    vector<Range> next_try;
    for (const auto &s : src) {
      long long start = s.src_start;
      long long end = s.src_start + s.range - 1;
      long long i_min = max(r.src_start, start);
      long long i_max = min(r.src_start + r.range - 1, end);
      long long d_range = i_max - i_min + 1;
      if (d_range > 0) {
        long long d_start = r.dst_start - r.src_start + i_min;
        dst.push_back(Range(0, d_start, d_range));

        if (i_min > start) {
          next_try.push_back(Range(0, start, i_min - start));
        }
        if (i_max < end) {
          next_try.push_back(Range(0, i_max + 1, end - i_max));
        }
      } else {
        next_try.push_back(s);
      }
    }
    src = next_try;
  }
  for (const auto &s : src) {
    dst.push_back(s);
  }
  return dst;
}

std::string y2023::solve_05b(const std::vector<std::string> &input) {
  long long ans;

  vector<long long> seeds = ints(input[0]);

  vector<Range> data;
  for (int i = 0; i < seeds.size(); i += 2) {
    data.push_back(Range(0, seeds[i], seeds[i + 1]));
  }

  vector<vector<Range>> m;
  m.push_back(vector<Range>());
  int map_id = 0;
  for (int i = 3; i < input.size(); ++i) {
    if (input[i].size() == 0) {
      ++map_id;
      m.push_back(vector<Range>());
    } else if (isdigit(input[i][0])) {
      auto nums = ints(input[i]);
      Range r = {nums[0], nums[1], nums[2]};
      m[map_id].push_back(r);
    }
  }
  ans = LONG_LONG_MAX;
  for (const auto &ranges : m) {
    if (ranges.size() > 0) {
      data = convert2(ranges, data);
    }
  }

  for (const auto &r : data) {
    ans = min(ans, r.src_start);
  }

  return to_string(ans);
}

#else  // Bruteforce I wrote because the upper algo used int instead on long long in one place...
std::string y2023::solve_05b(const std::vector<std::string> &input) {
  long long ans;

  vector<long long> seeds = ints(input[0]);

  vector<Range> data;

  long long sum = 0;
  for (int i = 0; i < seeds.size(); i += 2) {
    data.push_back(Range(0, seeds[i], seeds[i + 1]));
    sum += seeds[i + 1];
  }

  vector<vector<Range>> m;
  m.push_back(vector<Range>());
  int map_id = 0;
  for (int i = 3; i < input.size(); ++i) {
    if (input[i].size() == 0) {
      ++map_id;
      m.push_back(vector<Range>());
    } else if (isdigit(input[i][0])) {
      auto nums = ints(input[i]);
      Range r = {nums[0], nums[1], nums[2]};
      m[map_id].push_back(r);
    }
  }
  ans = LONG_LONG_MAX;
  for (const auto &d : data) {
    for (long long i = d.src_start; i < d.src_start + d.range; ++i) {
      long long s = i;
      for (const auto &ranges : m) {
        if (ranges.size() > 0) {
          s = convert(ranges, s);
        }
      }
      ans = min(ans, s);
    }
  }

  return to_string(ans);
}
#endif