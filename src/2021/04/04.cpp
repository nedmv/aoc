// Puzzle is available at https://adventofcode.com/2021/day/04
// Keywords:
#include <algorithm>
#include <regex>

#include "../2021.hpp"
#include "../../utils.hpp"
using namespace std;

/**
 * @brief Storage class for 5x5 bingo board and it's status.
 *
 */
class BingoBoard {
 public:
  BingoBoard(const std::vector<std::string> &input, size_t startPos)
      : _marked{5, vector<bool>(5, false)} {
    _board = parseBoard(input, startPos);
  }

  ~BingoBoard() {}

  uint markAndCheckScore(int num) {
    uint score = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (_board[i][j] == num) {
          _marked[i][j] = true;
          if((++_markedCounter >= 5) && checkForVictory()) {
            score = countVictoryScore(num);
          }
          break;
        }
      }
    }
    return score;
  }

  void printBoard() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        cout << _board[i][j];
        if (_marked[i][j]) {
          cout << "+";
        }
        cout << " ";
      }
      cout << "\n";
    }
    cout << "\n";
  }

  bool won = false;

 private:
  vector<vector<int>> _board;
  vector<vector<bool>> _marked;
  size_t _markedCounter = 0;

  bool checkForVictory() {
    // check rows
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
        if (!_marked[i][j]) {
          break;
        }
        if (j == 4) {
          won = true;
          return true;
        }
      }
    }
    // check columns
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
        if (!_marked[j][i]) {
          break;
        }
        if (j == 4) {
          won = true;
          return true;
        }
      }
    }
    return false;
  }

  uint countVictoryScore(int lastNum) {
    uint unmarkedSum = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (!_marked[i][j]) {
          unmarkedSum += _board[i][j];
        }
      }
    }
    return unmarkedSum * lastNum;
  }

  vector<vector<int>> parseBoard(const std::vector<std::string> &input,
                                 size_t startPos) {
    vector<vector<int>> result;
    for (size_t i = startPos; i < startPos + 5; i++) {
      smatch match;
      vector<int> row;
      string line = input[i];
      while (regex_search(line, match, regex(R"(([0-9]+))"))) {
        row.push_back(stoi(match[1].str()));
        line = match.suffix().str();
      }
      result.push_back(row);
    }
    return result;
  }
};

vector<BingoBoard> initBoards(const std::vector<std::string> &input) {
  vector<BingoBoard> boards;
  size_t startPos = 2;  // first board start
  while (startPos <= input.size()) {
    boards.push_back(BingoBoard(input, startPos));
    startPos += 6;
  }
  return boards;
}

const std::string y2021::solve_04a(const std::vector<std::string> &input) {
  vector<int> pattern = parseLineOfNumbers(input[0]);
  vector<BingoBoard> boards = initBoards(input);
  uint score = 0;
  for (size_t i = 0; i < pattern.size(); i++) {
    for (int j = 0; j < boards.size(); j++) {
      score = boards[j].markAndCheckScore(pattern[i]);
      if (score != 0) {
        break;
      };
    }
  }
  return to_string(score);
}

const std::string y2021::solve_04b(const std::vector<std::string> &input) {
  vector<int> pattern = parseLineOfNumbers(input[0]);
  vector<BingoBoard> boards = initBoards(input);

  uint lastScore = 0;
  for (size_t i = 0; i < pattern.size(); i++) {
    for (int j = 0; j < boards.size(); j++) {
      if (!boards[j].won) {
        uint score = boards[j].markAndCheckScore(pattern[i]);
        if (score != 0) {
          lastScore = score;
        }
      }
    }
  }
  return to_string(lastScore);
}
