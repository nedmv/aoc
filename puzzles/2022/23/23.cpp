// Puzzle is available at https://adventofcode.com/2022/day/23
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

vector<vector<int>> neighbors = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
                                 {1, 1},   {1, 0},  {1, -1}, {0, -1}};
vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool check_dir(const vector<string> &m, int row, int col, int dir) {
  switch (dir) {
    case 0:
      if ((m[row - 1][col - 1] == '.') && (m[row - 1][col] == '.') &&
          (m[row - 1][col + 1] == '.')) {
        return true;
      }
      return false;
    case 1:
      if ((m[row + 1][col - 1] == '.') && (m[row + 1][col] == '.') &&
          (m[row + 1][col + 1] == '.')) {
        return true;
      }
      return false;
    case 2:
      if ((m[row - 1][col - 1] == '.') && (m[row][col - 1] == '.') &&
          (m[row + 1][col - 1] == '.')) {
        return true;
      }
      return false;
    case 3:
      if ((m[row - 1][col + 1] == '.') && (m[row][col + 1] == '.') &&
          (m[row + 1][col + 1] == '.')) {
        return true;
      }
      return false;
    default:
      break;
  }
  return false;
}

vector<int> choose_dir(const vector<string> &m, int row, int col,
                       int first_dir) {
  vector<bool> results(4, false);
  int dir = first_dir;
  for (int i = 0; i < 4; ++i) {
    results[dir] = check_dir(m, row, col, dir);
    dir = (dir + 1) % 4;
  }
  if (results[0] && results[1] && results[2] && results[3]) {
    return {row, col};
  }
  for (int i = 0; i < 4; ++i) {
    int dir = (first_dir + i) % 4;
    if (results[dir]) {
      return {row + dirs[dir][0], col + dirs[dir][1]};
    }
  }
  return {row, col};
}

std::string y2022::solve_23a(const std::vector<std::string> &input) {
  int turns = 10;
  vector<string> m;

  for (int i = 0; i < turns; i++) {
    string s;
    s.append(input[0].size() + 2 * turns, '.');
    m.push_back(s);
  }
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].empty()) {
      break;
    }
    string s;
    s.append(turns, '.');
    s.append(input[i]);
    s.append(turns, '.');
    m.push_back(s);
  }
  for (int i = 0; i < turns; i++) {
    string s;
    s.append(input[0].size() + 2 * turns, '.');
    m.push_back(s);
  }

  int first_dir = 0;
  for (int turn = 0; turn < turns; turn++) {
    vector<vector<vector<int>>> proposed_moves(
        m.size(), vector<vector<int>>(m[0].size()));
    vector<vector<int>> plans(m.size(), vector<int>(m[0].size(), 0));
    auto copy = m;
    for (int row = 0; row < m.size(); ++row) {
      for (int col = 0; col < m[0].size(); ++col) {
        if (m[row][col] == '#') {
          proposed_moves[row][col] = choose_dir(m, row, col, first_dir);
          plans[proposed_moves[row][col][0]][proposed_moves[row][col][1]]++;
        }
      }
    }
    for (int row = 0; row < m.size(); ++row) {
      for (int col = 0; col < m[0].size(); ++col) {
        if (m[row][col] == '#') {
          if (plans[proposed_moves[row][col][0]][proposed_moves[row][col][1]] ==
              1) {
            copy[row][col] = '.';
            copy[proposed_moves[row][col][0]][proposed_moves[row][col][1]] =
                '#';
          }
        }
      }
    }
    m = copy;
    first_dir = (first_dir + 1) % 4;
  }

  int row_max = m.size() - 1;
  int row_min = 0;
  int col_max = m[0].size() - 1;
  int col_min = 0;

  for (int row = 0; row < m.size(); ++row) {
    if (m[row].find('#') == string::npos) {
      row_min++;
    } else {
      break;
    }
  }
  for (int row = m.size() - 1; row >= 0; --row) {
    if (m[row].find('#') == string::npos) {
      row_max--;
    } else {
      break;
    }
  }
  for (int col = 0; col < m[0].size(); ++col) {
    bool found = false;
    for (int row = row_min; row <= row_max; ++row) {
      if (m[row][col] == '#') {
        found = true;
        break;
      }
    }
    if (!found) {
      col_min++;
    } else {
      break;
    }
  }

  for (int col = m[0].size() - 1; col >= 0; --col) {
    bool found = false;
    for (int row = row_max; row >= row_min; --row) {
      if (m[row][col] == '#') {
        found = true;
        break;
      }
    }
    if (!found) {
      col_max--;
    } else {
      break;
    }
  }
  int count = 0;
  for (int row = row_min; row <= row_max; ++row) {
    for (int col = col_min; col <= col_max; ++col) {
      if (m[row][col] == '.') {
        ++count;
      }
    }
  }
  return to_string(count);
}

std::string y2022::solve_23b(const std::vector<std::string> &input) {
  int turns = 1000;
  vector<string> m;

  for (int i = 0; i < turns; i++) {
    string s;
    s.append(input[0].size() + 2 * turns, '.');
    m.push_back(s);
  }
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].empty()) {
      break;
    }
    string s;
    s.append(turns, '.');
    s.append(input[i]);
    s.append(turns, '.');
    m.push_back(s);
  }
  for (int i = 0; i < turns; i++) {
    string s;
    s.append(input[0].size() + 2 * turns, '.');
    m.push_back(s);
  }

  int first_dir = 0;
  for (int turn = 0; turn < turns; turn++) {
    vector<vector<vector<int>>> proposed_moves(
        m.size(), vector<vector<int>>(m[0].size()));
    vector<vector<int>> plans(m.size(), vector<int>(m[0].size(), 0));
    auto copy = m;
    for (int row = 0; row < m.size(); ++row) {
      for (int col = 0; col < m[0].size(); ++col) {
        if (m[row][col] == '#') {
          proposed_moves[row][col] = choose_dir(m, row, col, first_dir);
          plans[proposed_moves[row][col][0]][proposed_moves[row][col][1]]++;
        }
      }
    }
    for (int row = 0; row < m.size(); ++row) {
      for (int col = 0; col < m[0].size(); ++col) {
        if (m[row][col] == '#') {
          if (plans[proposed_moves[row][col][0]][proposed_moves[row][col][1]] ==
              1) {
            copy[row][col] = '.';
            copy[proposed_moves[row][col][0]][proposed_moves[row][col][1]] =
                '#';
          }
        }
      }
    }
    if (m == copy) {
      return to_string(turn + 1);
    }
    m = copy;
    first_dir = (first_dir + 1) % 4;
  }
  return ERROR_STRING;
}
