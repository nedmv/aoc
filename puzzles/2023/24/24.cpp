// Puzzle is available at https://adventofcode.com/2023/day/24
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

struct Vec2 {
  double x;
  double y;
};

struct Vec {
  double x;
  double y;
  double z;
};

struct Stone {
  Vec pos;
  Vec vel;
};

struct Mat {
  double a11;
  double a12;
  double a21;
  double a22;
};

bool intersect_xy(const Stone &s1, const Stone &s2, Vec area_min,
                  Vec area_max) {
  vector<vector<double>> m(2, vector<double>(2, 0));
  m[0][0] = s1.vel.x;
  m[1][0] = s1.vel.y;
  m[0][1] = -s2.vel.x;
  m[1][1] = -s2.vel.y;

  Vec2 v;
  v.x = s2.pos.x - s1.pos.x;
  v.y = s2.pos.y - s1.pos.y;

  Vec2 t;

  auto diff = m[1][0] / m[0][0];
  m[1][0] = 0.;
  m[1][1] -= m[0][1] * diff;
  v.y -= v.x * diff;
  t.y = v.y / m[1][1];
  m[0][1] *= t.y;
  t.x = (v.x - m[0][1]) / m[0][0];

  if (t.x < 0 || t.y < 0) {
    // cout << "meet in the past " << t.x << " " << t.y << endl;
    return false;
  }
  Vec2 p = {s1.pos.x + s1.vel.x * t.x, s1.pos.y + s1.vel.y * t.x};

  if (p.x < area_min.x || p.x > area_max.x || p.y < area_min.y ||
      p.y > area_max.y) {
    // cout << "meet outside " << p.x << " " << p.y << endl;
    return false;
  }

  // cout << "correct " << p.x << " " << p.y << endl;
  return true;
}

std::string y2023::solve_24a(const std::vector<std::string> &input) {
  long long ans = 0;

  vector<Stone> stones;

  for (const auto &l : input) {
    if (l.size() == 0) {
      break;
    }
    auto s = signed_ints(l);
    Stone st;
    st.pos.x = s[0];
    st.pos.y = s[1];
    st.pos.z = s[2];
    st.vel.x = s[3];
    st.vel.y = s[4];
    st.vel.z = s[5];
    stones.push_back(st);
  }

  Vec area_min = {200000000000000, 200000000000000, 0};
  Vec area_max = {400000000000000, 400000000000000, 0};

  int n = stones.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (intersect_xy(stones[i], stones[j], area_min, area_max)) {
        ++ans;
      }
    }
  }

  return to_string(ans);
}

vector<double> gauss(vector<vector<double>> mat) {
  int m = mat.size();
  int n = mat[0].size();
  int h = 0;
  int k = 0;

  while (h < m && k < n) {
    int i_max = h;
    double maxVal = 0;
    for (int i = h; i < m; ++i) {
      double cur = abs(mat[i][k]);
      if (cur > maxVal) {
        maxVal = cur;
        i_max = i;
      }
    }
    if (maxVal == 0) {
      ++k;
    } else {
      swap(mat[h], mat[i_max]);
      for (int i = h + 1; i < m; ++i) {
        double coeff = mat[i][k] / mat[h][k];
        mat[i][k] = 0;
        for (int j = k + 1; j < n; ++j) {
          mat[i][j] -= coeff * mat[h][j];
        }
      }
      ++h;
      ++k;
    }
  }

#if 0
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
#endif

  vector<double> ans(m);
  for (int i = m - 1; i >= 0; --i) {
    for (int j = i + 1; j < m; ++j) {
      mat[i][n - 1] -= mat[i][j] * ans[j];
    }
    ans[i] = mat[i][n - 1] / mat[i][i];
  }
#if 0
  cout << fixed;
  for (int i = 0; i < m; ++i) {
    cout << ans[i] << " ";
  }
  cout << endl;
#endif
  return ans;
}

vector<double> find_start_pos(const vector<Stone> &stones) {
  vector<vector<double>> m(6, vector<double>(7, 0.));

  m[0][1] = stones[0].vel.z - stones[1].vel.z;
  m[0][2] = stones[1].vel.y - stones[0].vel.y;
  m[1][0] = stones[1].vel.z - stones[0].vel.z;
  m[1][2] = stones[0].vel.x - stones[1].vel.x;
  m[2][0] = stones[0].vel.y - stones[1].vel.y;
  m[2][1] = stones[1].vel.x - stones[0].vel.x;

  m[3][1] = stones[0].vel.z - stones[2].vel.z;
  m[3][2] = stones[2].vel.y - stones[0].vel.y;
  m[4][0] = stones[2].vel.z - stones[0].vel.z;
  m[4][2] = stones[0].vel.x - stones[2].vel.x;
  m[5][0] = stones[0].vel.y - stones[2].vel.y;
  m[5][1] = stones[2].vel.x - stones[0].vel.x;

  m[0][4] = stones[1].pos.z - stones[0].pos.z;
  m[0][5] = stones[0].pos.y - stones[1].pos.y;
  m[1][3] = stones[0].pos.z - stones[1].pos.z;
  m[1][5] = stones[1].pos.x - stones[0].pos.x;
  m[2][3] = stones[1].pos.y - stones[0].pos.y;
  m[2][4] = stones[0].pos.x - stones[1].pos.x;

  m[3][4] = stones[2].pos.z - stones[0].pos.z;
  m[3][5] = stones[0].pos.y - stones[2].pos.y;
  m[4][3] = stones[0].pos.z - stones[2].pos.z;
  m[4][5] = stones[2].pos.x - stones[0].pos.x;
  m[5][3] = stones[2].pos.y - stones[0].pos.y;
  m[5][4] = stones[0].pos.x - stones[2].pos.x;

  m[0][6] =
      stones[0].pos.y * stones[0].vel.z - stones[0].pos.z * stones[0].vel.y -
      stones[1].pos.y * stones[1].vel.z + stones[1].pos.z * stones[1].vel.y;
  m[1][6] =
      stones[0].pos.z * stones[0].vel.x - stones[0].pos.x * stones[0].vel.z -
      stones[1].pos.z * stones[1].vel.x + stones[1].pos.x * stones[1].vel.z;
  m[2][6] =
      stones[0].pos.x * stones[0].vel.y - stones[0].pos.y * stones[0].vel.x -
      stones[1].pos.x * stones[1].vel.y + stones[1].pos.y * stones[1].vel.x;
  m[3][6] =
      stones[0].pos.y * stones[0].vel.z - stones[0].pos.z * stones[0].vel.y -
      stones[2].pos.y * stones[2].vel.z + stones[2].pos.z * stones[2].vel.y;
  m[4][6] =
      stones[0].pos.z * stones[0].vel.x - stones[0].pos.x * stones[0].vel.z -
      stones[2].pos.z * stones[2].vel.x + stones[2].pos.x * stones[2].vel.z;
  m[5][6] =
      stones[0].pos.x * stones[0].vel.y - stones[0].pos.y * stones[0].vel.x -
      stones[2].pos.x * stones[2].vel.y + stones[2].pos.y * stones[2].vel.x;

  return gauss(m);
}

std::string y2023::solve_24b(const std::vector<std::string> &input) {
  vector<Stone> stones;

  for (int i = 0; i < 3; ++i) {
    auto &l = input[i];
    auto s = signed_ints(l);
    Stone st;
    st.pos.x = s[0];
    st.pos.y = s[1];
    st.pos.z = s[2];
    st.vel.x = s[3];
    st.vel.y = s[4];
    st.vel.z = s[5];
    stones.push_back(st);
  }

  vector<double> start = find_start_pos(stones);
  long long ans = 0;
  for (int i = 0; i < 3; ++i) {
    ans += (long long)round(start[i]);
  }
  return to_string(ans);
}
