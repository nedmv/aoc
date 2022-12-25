// Puzzle is available at https://adventofcode.com/2022/day/24
// Keywords: BFS
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

static const vector<int> dirs = {0, 1, 0, -1, 0};

struct Blizzard {
  int row;
  int col;
  int dir;
};

class WeatherMap {
  vector<Blizzard> blizzards_;
  vector<vector<bool>> safety_;
  int rows_;
  int cols_;
  int turn_ = 0;

 public:
  WeatherMap(int rows, int cols, const vector<Blizzard> &blizzards)
      : blizzards_(blizzards), rows_(rows), cols_(cols){};
  bool within_borders(int row, int col) const {
    return (row >= 0) && (row < rows_) && (col >= 0) && (col < cols_);
  }
  bool safe(int row, int col) {
    return within_borders(row, col) && safety_[row][col];
  }
  int get_turn() const { return turn_; }
  void update() {
    ++turn_;

    safety_ = vector<vector<bool>>(rows_, vector<bool>(cols_, true));
    for (int i = 0; i < rows_; i++) {  // walls
      safety_[i][0] = false;
      safety_[i][cols_ - 1] = false;
    }
    for (int i = 0; i < cols_; i++) {  // walls
      safety_[0][i] = false;
      safety_[rows_ - 1][i] = false;
    }
    safety_[0][1] = true;                  // start
    safety_[rows_ - 1][cols_ - 2] = true;  // finish

    for (auto &b : blizzards_) {
      int new_row = b.row + dirs[b.dir];
      int new_col = b.col + dirs[b.dir + 1];
      if (new_row == 0) {
        new_row = rows_ - 2;
      } else if (new_col == 0) {
        new_col = cols_ - 2;
      } else if (new_row == rows_ - 1) {
        new_row = 1;
      } else if (new_col == cols_ - 1) {
        new_col = 1;
      }
      b.row = new_row;
      b.col = new_col;
      safety_[new_row][new_col] = false;
    }
  }
};

int bfs(vector<int> start, vector<int> end, int start_turn, WeatherMap &w) {
  deque<vector<int>> q;
  q.push_back({start[0], start[1], start_turn});  // row, col, turn
  set<vector<int>> visited;

  while (!q.empty()) {
    vector<int> cur = q.front();
    q.pop_front();
    int next_turn = cur[2] + 1;

    if (w.get_turn() != next_turn) {  // turn is always increased by 1
      w.update();
      visited.clear();
    }

    if (!visited.contains({cur[0], cur[1]}) &&
        w.safe(cur[0], cur[1])) {  // wait
      visited.insert({cur[0], cur[1]});
      q.push_back({cur[0], cur[1], next_turn});
    }

    for (int i = 3; i >= 0; --i) {
      int row = cur[0] + dirs[i];
      int col = cur[1] + dirs[i + 1];
      if (w.safe(row, col)) {
        if ((row == end[0]) && (col == end[1])) {
          return next_turn;
        }
        if (!visited.contains({row, col})) {
          visited.insert({row, col});
          q.push_back({row, col, next_turn});
        }
      }
    }
  }
  return INT_MIN;
}

vector<Blizzard> get_blizzards(const vector<string> &input) {
  vector<Blizzard> blizzards;
  for (int row = 0; row < input.size(); row++) {
    if (input[row].empty()) {
      break;
    }
    for (int col = 0; col < input[0].size(); col++) {
      char c = input[row][col];
      if (c == '>' || c == '<' || c == '^' || c == 'v') {
        Blizzard b;
        b.row = row;
        b.col = col;
        switch (c) {
          case '>':
            b.dir = 0;
            break;
          case 'v':
            b.dir = 1;
            break;
          case '<':
            b.dir = 2;
            break;
          case '^':
            b.dir = 3;
            break;
        }
        blizzards.push_back(b);
      }
    }
  }
  return blizzards;
}

std::string y2022::solve_24a(const std::vector<std::string> &input) {
  int rows = input.size();
  while (input[rows - 1].empty()) {
    --rows;
  }
  int cols = input[0].size();
  auto blizzards = get_blizzards(input);
  WeatherMap w(rows, cols, blizzards);

  vector<int> start = {0, 1};
  vector<int> end = {rows - 1, cols - 2};

  int result = bfs(start, end, 0, w);
  return to_string(result);
}

std::string y2022::solve_24b(const std::vector<std::string> &input) {
  int rows = input.size();
  while (input[rows - 1].empty()) {
    --rows;
  }
  int cols = input[0].size();
  auto blizzards = get_blizzards(input);
  WeatherMap w(rows, cols, blizzards);

  vector<int> start = {0, 1};
  vector<int> end = {rows - 1, cols - 2};
  int result = 0;
  result = bfs(start, end, result, w);
  result = bfs(end, start, result, w);
  result = bfs(start, end, result, w);

  return to_string(result);
}
