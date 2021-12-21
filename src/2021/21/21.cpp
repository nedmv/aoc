// Puzzle is available at https://adventofcode.com/2021/day/21
// Keywords:
#include "../../utils.hpp"
#include "../2021.hpp"
using namespace std;

const std::string y2021::solve_21a(std::vector<std::string> input) {
  size_t die = 1;
  size_t score1 = 0;
  size_t score2 = 0;
  size_t pos1 = 10;  // FIXME: load input from file
  size_t pos2 = 1;
  size_t rolls = 0;
  bool isFirst = true;

  while ((score1 < 1000) && (score2 < 1000)) {
    size_t move = 0;
    for (size_t i = 0; i < 3; i++) {
      move += die;
      if (die < 100) {
        die++;
      } else {
        die = 1;
      }
      rolls++;
    }
    if (isFirst) {
      pos1 += move;
      if (pos1 > 10) {
        pos1 = pos1 % 10;
      }
      if (pos1 == 0) {
        pos1 = 10;
      }
      score1 += pos1;
      isFirst = false;
    } else {
      pos2 += move;
      if (pos2 > 10) {
        pos2 = pos2 % 10;
      }
      if (pos2 == 0) {
        pos2 = 10;
      }
      score2 += pos2;
      isFirst = true;
    }
  }
  size_t losingScore = (score1 < score2) ? score1 : score2;
  return to_string(rolls * losingScore);
}

const std::string y2021::solve_21b(std::vector<std::string> input) {
  vector<vector<vector<vector<size_t>>>> state(
      10, vector<vector<vector<size_t>>>(
              10, vector<vector<size_t>>(21, vector<size_t>(21, 0))));
  // FIXME: load input from file
  state[0][1][0][0] = 1;  // start

  vector<size_t> moveProbability = {0, 0, 0, 1, 3, 6, 7, 6, 3, 1};

  // state[4][8][0][0] = 1; // test

  bool isFirstPlayerTurn = true;
  size_t wins1 = 0;
  size_t wins2 = 0;

  while (true) {
    bool finished = true;
    vector<vector<vector<vector<size_t>>>> newState(
        10, vector<vector<vector<size_t>>>(
                10, vector<vector<size_t>>(21, vector<size_t>(21, 0))));

    for (size_t pos1 = 0; pos1 <= 9; pos1++) {
      for (size_t pos2 = 0; pos2 <= 9; pos2++) {
        for (size_t score1 = 0; score1 <= 20; score1++) {
          for (size_t score2 = 0; score2 <= 20; score2++) {
            size_t currentState = state[pos1][pos2][score1][score2];
            if (currentState != 0) {
              finished = false;
              for (size_t roll = 3; roll <= 9; roll++) {
                if (isFirstPlayerTurn) {
                  newState[(pos1 + roll) % 10][pos2][score1][score2] +=
                      currentState * moveProbability[roll];
                } else {
                  newState[pos1][(pos2 + roll) % 10][score1][score2] +=
                      currentState * moveProbability[roll];
                }
              }
            }
          }
        }
      }
    }

    if (finished) {  // game already ended for all universes
      break;
    }

    state = newState;  // save state after rolls

    newState =
        vector(10, vector<vector<vector<size_t>>>(
                       10, vector<vector<size_t>>(21, vector<size_t>(21, 0))));

    size_t wins = 0;
    for (size_t pos1 = 0; pos1 <= 9; pos1++) {
      for (size_t pos2 = 0; pos2 <= 9; pos2++) {
        for (size_t score1 = 0; score1 <= 20; score1++) {
          for (size_t score2 = 0; score2 <= 20; score2++) {
            size_t currentState = state[pos1][pos2][score1][score2];
            if (currentState != 0) {
              size_t newScore;
              if (isFirstPlayerTurn) {
                newScore = pos1 + score1;
                if (pos1 == 0) {
                  newScore += 10;
                }
              } else {
                newScore = pos2 + score2;
                if (pos2 == 0) {
                  newScore += 10;
                }
              }
              if (newScore > 20) {
                wins += currentState;
                // new state would not contain this universes
              } else {
                if (isFirstPlayerTurn) {
                  newState[pos1][pos2][newScore][score2] += currentState;
                } else {
                  newState[pos1][pos2][score1][newScore] += currentState;
                }
              }
            }
          }
        }
      }
    }

    state = newState;  // save state after counting scores

    if (isFirstPlayerTurn) {
      wins1 += wins;
      isFirstPlayerTurn = false;
    } else {
      wins2 += wins;
      isFirstPlayerTurn = true;
    }
  }
  return to_string(max(wins1, wins2));
}