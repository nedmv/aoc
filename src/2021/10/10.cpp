// Puzzle is available at https://adventofcode.com/2021/day/10
// Keywords:
#include "../../utils.hpp"
#include "../2021.hpp"
using namespace std;

static int getErrorScore(char c) {
  int score = 0;
  switch (c) {
    case ')':
      score = 3;
      break;
    case ']':
      score = 57;
      break;
    case '}':
      score = 1197;
      break;
    case '>':
      score = 25137;
      break;
  }
  return score;
}

static int getCompletionScore(char c) {
  int score = 0;
  switch (c) {
    case '(':
      score = 1;
      break;
    case '[':
      score = 2;
      break;
    case '{':
      score = 3;
      break;
    case '<':
      score = 4;
      break;
  }
  return score;
}

static bool isPairMatching(char begin, char end) {
  bool isMatching = false;
  if ((begin == '(') && (end == ')')) {
    isMatching = true;
  } else if ((begin == '{') && (end == '}')) {
    isMatching = true;
  } else if ((begin == '[') && (end == ']')) {
    isMatching = true;
  } else if ((begin == '<') && (end == '>')) {
    isMatching = true;
  }
  return isMatching;
}

static size_t countCompletionScore(vector<char> &openedChunks) {
  size_t score = 0;

  for (auto rit = openedChunks.rbegin(); rit != openedChunks.rend(); rit++) {
    score *= 5;
    score += getCompletionScore(*rit);
  }
  return score;
}

std::string y2021::solve_10a(const std::vector<std::string> &input) {
  uint score = 0;
  for (size_t i = 0; i < input.size(); i++) {
    vector<char> openedChunks;
    for (size_t j = 0; j < input[i].size(); j++) {
      if (input[i][j] == '(' || input[i][j] == '[' || input[i][j] == '{' ||
          input[i][j] == '<') {
        openedChunks.push_back(input[i][j]);
      } else {
        if ((openedChunks.size() != 0) &&
            isPairMatching(openedChunks.back(), input[i][j])) {
          openedChunks.pop_back();
        } else {
          score += getErrorScore(input[i][j]);
          break;
        }
      }
    }
  }
  return to_string(score);
}

std::string y2021::solve_10b(const std::vector<std::string> &input) {
  vector<size_t> scores;
  for (size_t i = 0; i < input.size(); i++) {
    vector<char> openedChunks;
    for (size_t j = 0; j < input[i].size(); j++) {
      if (input[i][j] == '(' || input[i][j] == '[' || input[i][j] == '{' ||
          input[i][j] == '<') {
        openedChunks.push_back(input[i][j]);
      } else {
        if ((openedChunks.size() != 0) &&
            isPairMatching(openedChunks.back(), input[i][j])) {
          openedChunks.pop_back();
        } else {
          break;
        }
      }
      if ((j == input[i].size() - 1) && (openedChunks.size() != 0)) {
        scores.push_back(countCompletionScore(openedChunks));
      }
    }
  }
  sort(scores.begin(), scores.end());
  return to_string(scores[(scores.size() - 1) / 2]);
}
