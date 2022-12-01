// Puzzle is available at https://adventofcode.com/2020/day/11
#include "../2020.hpp"
using namespace std;

enum seatStatus { FLOOR, EMPTY, TAKEN };

size_t countNeighborsA(const vector<vector<seatStatus>> &data, size_t row,
                       size_t col) {
  size_t result = 0;
  for (size_t i = row - 1; i <= row + 1; i++) {
    for (size_t j = col - 1; j <= col + 1; j++) {
      if ((i == row) && (j == col)) continue;
      if (data[i][j] == TAKEN) result++;
    }
  }
  return result;
}

size_t checkDirection(const vector<vector<seatStatus>> &data, size_t row, size_t col,
                      int row_step, int col_step) {
  size_t rows = data.size();
  size_t cols = data[0].size();
  size_t i = row;
  size_t j = col;
  do {
    i += row_step;
    j += col_step;
    if (data[i][j] == TAKEN) {
      return 1;
    }
    if (data[i][j] == EMPTY) {
      return 0;
    }
  } while ((i > 0) && (j > 0) && (i < rows - 1) && (j < cols - 1));
  return 0;
}

size_t countNeighborsB(const vector<vector<seatStatus>> &data, size_t row,
                       size_t col) {
  size_t result = 0;

  result += checkDirection(data, row, col, -1, 0);  // N
  result += checkDirection(data, row, col, 1, 0);   // S
  result += checkDirection(data, row, col, 0, -1);  // W
  result += checkDirection(data, row, col, 0, 1);   // E

  result += checkDirection(data, row, col, -1, -1);  // NW
  result += checkDirection(data, row, col, 1, -1);   // SW
  result += checkDirection(data, row, col, -1, 1);   // NE
  result += checkDirection(data, row, col, 1, 1);    // SE

  return result;
}

seatStatus rulesA(const vector<vector<seatStatus>> &data, size_t i, size_t j) {
  seatStatus status = data[i][j];
  if ((status == EMPTY) && (countNeighborsA(data, i, j) == 0)) return TAKEN;
  if ((status == TAKEN) && (countNeighborsA(data, i, j) >= 4)) return EMPTY;
  return status;
}

seatStatus rulesB(const vector<vector<seatStatus>> &data, size_t i, size_t j) {
  seatStatus status = data[i][j];
  if ((status == EMPTY) && (countNeighborsB(data, i, j) == 0)) return TAKEN;
  if ((status == TAKEN) && (countNeighborsB(data, i, j) >= 5)) return EMPTY;
  return status;
}

size_t countTakenSeats(const std::vector<std::string> &input,
                       seatStatus rules(const vector<vector<seatStatus>> &, size_t,
                                        size_t)) {
  size_t rows = input.size();
  size_t cols = input[0].size();
  // start from turn 2, when all empty seats become occupied
  vector<vector<seatStatus>> future(rows + 2,
                                    vector<seatStatus>(cols + 2, TAKEN));

  for (size_t i = 0; i < rows + 2; i++) {
    for (size_t j = 0; j < cols + 2; j++) {
      if ((i == 0) || (j == 0) || (i == rows + 1) || (j == cols + 1)) {
        future[i][j] = FLOOR;
      } else if (input[i - 1].at(j - 1) == '.') {
        future[i][j] = FLOOR;
      }
    }
  }

  vector<vector<seatStatus>> current;
  do {
    current = future;
    for (size_t i = 1; i <= rows; i++) {
      for (size_t j = 1; j <= cols; j++) {
        future[i][j] = rules(current, i, j);
      }
    }
  } while (current != future);

  size_t result = 0;
  for (size_t i = 1; i < rows + 1; i++) {
    for (size_t j = 1; j < cols + 1; j++) {
      if (current[i][j] == TAKEN) result++;
    }
  }
  return result;
}

std::string y2020::solve_11a(const std::vector<std::string> &input) {
  return to_string(countTakenSeats(input, rulesA));
}

std::string y2020::solve_11b(const std::vector<std::string> &input) {
  return to_string(countTakenSeats(input, rulesB));
}