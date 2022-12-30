// Puzzle is available at https://adventofcode.com/2022/day/15
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

struct Sensor {
  int x;
  int y;
  int b_x;
  int b_y;
  int beakon_distance;
  Sensor(int x, int y, int b_x, int b_y) : x(x), y(y), b_x(b_x), b_y(b_y) {
    beakon_distance = abs(b_x - x) + abs(b_y - y);
  }

  int distance(int a, int b) const { return abs(x - a) + abs(y - b); }
  bool closer(int a, int b) const { return distance(a, b) <= beakon_distance; }

  vector<int> overlay(int row) const {
    int cells = beakon_distance - distance(x, row);
    vector<int> result;
    if (cells < 0) {
      result.push_back(cells);
      return result;
    }

    result.push_back(cells * 2 + 1);
    result.push_back(x - cells);
    result.push_back(x + cells);
    if (b_y == row && b_x >= result[1] && b_y <= result[2]) {
      result.push_back(b_x);
    }
    return result;
  }
};

int count_row_with_overlay(const vector<Sensor> &sensor, int row, int x_min,
                           int x_max) {
  vector<vector<int>> overlay;
  set<int> beakons;
  for (int i = 0; i < sensor.size(); i++) {
    vector<int> tmp = sensor[i].overlay(row);

    if (tmp[0] >= 0) {
      vector<int> dist;
      dist.push_back(tmp[1]);
      dist.push_back(tmp[2]);
      overlay.push_back(dist);
    }
    if (tmp.size() == 4) {
      beakons.insert(tmp[3]);
    }
  }

  auto compare = [](vector<int> &l, vector<int> &r) {
    return (l[0] < r[0]) || ((l[0] == r[0]) && (l[1] < r[1]));
  };
  sort(overlay.begin(), overlay.end(), compare);

  set<int> removed;

  for (int i = 0; i < overlay.size(); ++i) {
    if (removed.contains(i)) {
      continue;
    }
    for (int j = i + 1; j < overlay.size(); ++j) {
      if (!removed.contains(j) && overlay[i][1] >= overlay[j][0]) {
        if (overlay[i][1] < overlay[j][1]) {
          overlay[i][1] = overlay[j][1];
        }
        removed.insert(j);
      } else {
        break;
      }
    }
  }

  vector<vector<int>> lines;
  for (int i = 0; i < overlay.size(); ++i) {
    if (!removed.contains(i)) {
      lines.push_back(overlay[i]);
    }
  }

  int count = 0;
  for (auto line : lines) {
    count += (line[1] - line[0] + 1);
    for (auto b : beakons) {
      if (b >= line[0] && b <= line[1]) {
        --count;
      }
    }
  }

  return count;
}

int clamp(int val, int min, int max) {
  if (val < min) {
    return min;
  }
  if (val > max) {
    return max;
  }
  return val;
}

long long check_row(const vector<Sensor> &sensor, int row, int x_min,
                    int x_max) {
  vector<vector<int>> overlay;
  unordered_set<int> beakons;
  for (int i = 0; i < sensor.size(); i++) {
    vector<int> tmp = sensor[i].overlay(row);

    if (tmp[0] >= 0) {
      vector<int> dist;
      dist.push_back(clamp(tmp[1], x_min, x_max));
      dist.push_back(clamp(tmp[2], x_min, x_max));
      overlay.push_back(dist);
    }
    if (tmp.size() == 4) {
      beakons.insert(tmp[3]);
    }
  }

  auto compare = [](const vector<int> &l, const vector<int> &r) {
    return (l[0] < r[0]) || ((l[0] == r[0]) && (l[1] < r[1]));
  };
  sort(overlay.begin(), overlay.end(), compare);

  unordered_set<int> removed;

  for (int i = 0; i < overlay.size(); ++i) {
    if (removed.contains(i)) {
      continue;
    }
    for (int j = i + 1; j < overlay.size(); ++j) {
      if (!removed.contains(j) && overlay[i][1] >= overlay[j][0]) {
        if (overlay[i][1] < overlay[j][1]) {
          overlay[i][1] = overlay[j][1];
        }
        removed.insert(j);
      } else {
        break;
      }
    }
  }

  vector<vector<int>> lines;
  for (int i = 0; i < overlay.size(); ++i) {
    if (!removed.contains(i)) {
      lines.push_back(overlay[i]);
    }
  }

  if (lines.size() > 1) {
    for (int i = 1; i < lines.size(); ++i) {
      for (long long pos = lines[i - 1][1] + 1; pos < lines[i][0]; pos++) {
        if (!beakons.contains(pos)) {
          return pos;
        }
      }
    }
  }
  return -1;
}

std::string y2022::solve_15a(const std::vector<std::string> &input) {
  vector<Sensor> s;
  for (int i = 0; i < input.size(); ++i) {
    regex reg(
        R"(Sensor at x=([-]*[0-9]+), y=([-]*[0-9]+): closest beacon is at x=([-]*[0-9]+), y=([-]*[0-9]+))");
    smatch m;
    if (regex_match(input[i], m, reg)) {
      s.push_back(Sensor(ToInt(m[1]), ToInt(m[2]), ToInt(m[3]), ToInt(m[4])));
    }
  }

  int x_min = INT_MAX;
  int y_min = INT_MAX;

  int x_max = INT_MIN;
  int y_max = INT_MIN;

  for (const auto &sensor : s) {
    x_min = min(x_min, sensor.x);
    x_min = min(x_min, sensor.b_x);

    x_max = max(x_max, sensor.x);
    x_max = max(x_max, sensor.b_x);

    y_min = min(y_min, sensor.y);
    y_min = min(y_min, sensor.b_y);

    y_max = max(y_max, sensor.y);
    y_max = max(y_max, sensor.b_y);
  }
  return to_string(count_row_with_overlay(s, 2000000, x_min, x_max));
}

std::string y2022::solve_15b(const std::vector<std::string> &input) {
  vector<Sensor> s;
  for (int i = 0; i < input.size(); ++i) {
    regex reg(
        R"(Sensor at x=([-]*[0-9]+), y=([-]*[0-9]+): closest beacon is at x=([-]*[0-9]+), y=([-]*[0-9]+))");
    smatch m;
    if (regex_match(input[i], m, reg)) {
      s.push_back(Sensor(ToInt(m[1]), ToInt(m[2]), ToInt(m[3]), ToInt(m[4])));
    }
  }

  long long result;
  for (int row = 0; row <= 4000000; row++) {
    long long tmp = check_row(s, row, 0, 4000000);
    if (tmp >= 0) {
      // cout << "x = " << tmp << ", y = " << row << endl;
      result = 4000000 * tmp + row;
      break;
    }
    if (row % 100000 == 0) {
      cout << row << endl;
    }
  }
  return to_string(result);
}
