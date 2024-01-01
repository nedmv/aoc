// Puzzle is available at https://adventofcode.com/2023/day/22
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

struct Range {
  int l;
  int r;
};

struct Brick {
  Range x, y, z;

  bool intersects(Brick &other) {
    for (int a = x.l; a <= x.r; ++a) {
      if (other.x.l <= a && a <= other.x.r) {
        for (int b = y.l; b <= y.r; ++b) {
          if (other.y.l <= b && b <= other.y.r) {
            for (int c = z.l; c <= z.r; ++c) {
              if (other.z.l <= c && c <= other.z.r) {
                return true;
              }
            }
          }
        }
      }
    }
    return false;
  }

  bool supports(Brick &other) {
    if (z.r + 1 == other.z.l) {
      for (int a = x.l; a <= x.r; ++a) {
        if (other.x.l <= a && a <= other.x.r) {
          for (int b = y.l; b <= y.r; ++b) {
            if (other.y.l <= b && b <= other.y.r) {
              return true;
            }
          }
        }
      }
    }
    return false;
  }

  void print() {
    cout << "x: " << x.l << " " << x.r << ", y: " << y.l << " " << y.r
         << ", z: " << z.l << " " << z.r << endl;
  }
};

std::string y2023::solve_22a(const std::vector<std::string> &input) {
  long long ans = 0;

  vector<Brick> bricks;

  for (const auto &l : input) {
    auto nums = ints(l);

    Brick b;

    b.x.l = nums[0];
    b.x.r = nums[3];
    b.y.l = nums[1];
    b.y.r = nums[4];
    b.z.l = nums[2];
    b.z.r = nums[5];

    bricks.push_back(b);
  }

  sort(bricks.begin(), bricks.end(),
       [](const auto &l, const auto &r) { return l.z.l < r.z.l; });

  int n = bricks.size();

  bool all_stopped = false;
  while (!all_stopped) {
    all_stopped = true;
    for (int i = 0; i < bricks.size(); ++i) {
      if (bricks[i].z.l == 1) {
        continue;
      }

      --bricks[i].z.l;
      --bricks[i].z.r;
      bool stop = false;
      for (int j = 0; j < n; ++j) {
        if (i == j) {
          continue;
        }
        if (bricks[i].intersects(bricks[j])) {
          ++bricks[i].z.l;
          ++bricks[i].z.r;
          stop = true;
          break;
        }
      }
      if (!stop) {
        all_stopped = false;
      }
    }
  }

  vector<vector<bool>> support(n, vector(n, false));

  for (int i = 0; i < bricks.size(); ++i) {
    for (int j = i + 1; j < bricks.size(); ++j) {
      if (bricks[i].supports(bricks[j])) {
        support[i][j] = true;
      } else if (bricks[j].supports(bricks[i])) {
        support[j][i] = true;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    bool used = false;
    for (int j = 0; j < n; ++j) {
      if (support[i][j]) {
        bool supported = false;
        for (int k = 0; k < n; ++k) {
          if (k == i) {
            continue;
          }
          if (support[k][j]) {
            supported = true;
            break;
          }
        }
        if (!supported) {
          used = true;
          break;
        }
      }
    }
    if (!used) {
      ++ans;
    }
  }

  return to_string(ans);
}

std::string y2023::solve_22b(const std::vector<std::string> &input) {
  long long ans = 0;

  vector<Brick> bricks;

  for (const auto &l : input) {
    auto nums = ints(l);

    Brick b;

    b.x.l = nums[0];
    b.x.r = nums[3];
    b.y.l = nums[1];
    b.y.r = nums[4];
    b.z.l = nums[2];
    b.z.r = nums[5];

    bricks.push_back(b);
  }

  sort(bricks.begin(), bricks.end(),
       [](const auto &l, const auto &r) { return l.z.l < r.z.l; });

  int n = bricks.size();

  bool all_stopped = false;
  while (!all_stopped) {
    all_stopped = true;
    for (int i = 0; i < bricks.size(); ++i) {
      if (bricks[i].z.l == 1) {
        continue;
      }

      --bricks[i].z.l;
      --bricks[i].z.r;
      bool stop = false;
      for (int j = 0; j < n; ++j) {
        if (i == j) {
          continue;
        }
        if (bricks[i].intersects(bricks[j])) {
          ++bricks[i].z.l;
          ++bricks[i].z.r;
          stop = true;
          break;
        }
      }
      if (!stop) {
        all_stopped = false;
      }
    }
  }

  vector<vector<bool>> support(n, vector(n, false));

  for (int i = 0; i < bricks.size(); ++i) {
    for (int j = 0; j < bricks.size(); ++j) {
      if (i == j) {
        continue;
      }
      if (bricks[j].supports(bricks[i])) {
        support[i][j] = true;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    auto sup = support;
    queue<int> q;
    q.push(i);
    int falling = 0;
    vector<bool> seen(n, false);
    seen[i] = true;
    while (!q.empty()) {
      auto e = q.front();
      q.pop();
      for (int k = 0; k < n; ++k) {
        if (!sup[k][e]) {
          continue;
        }
        sup[k][e] = false;
        if (!seen[k]) {
          bool supported = false;
          for (int a = 0; a < n; ++a) {
            if (sup[k][a]) {
              supported = true;
            }
          }
          if (!supported) {
            seen[k] = true;
            ++falling;
            q.push(k);
          }
        }
      }
    }
    ans += falling;
  }

  return to_string(ans);
}
