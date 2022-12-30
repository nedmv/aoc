// Puzzle is available at https://adventofcode.com/2022/day/17
// Keywords:
#include "../2022.hpp"
#include "../../../src/utils.hpp"
using namespace std;

const vector<vector<string>> rocks = {
  {"####"}, 
  {".#.", "###", ".#."}, 
  {"###", "..#", "..#"}, 
  {"#", "#", "#", "#"}, 
  {"##", "##"}};

long long tall(const string &s, long long items) {
  vector<string> room(13*(items/5 + 1), "#.......#");
  // vector<string> room(30, "#.......#");
  long long last_floor = 0;
  room[0] = "#########";
  long long floor = 1;
  int gas = 0;
  for (int i = 0; i < items; i++) {

    const vector<string> rock = rocks[i%5];

    bool stopped = false;
    long long x = 3;
    long long y = floor + 3;
    while(!stopped) {
          if ((gas%s.size()) == 0 && (i%5) == 4) {
      cout << i << endl;
    } //1720
      int moves = 0;
      bool show_last_move = false;

      if (s[gas%s.size()] == '>') {
        bool move = true;
        bool show_last_move = false;
        for (int row = 0; row < rock.size(); row++) {
          for (int col = 0; col < rock[row].size(); col++) {
            if (rock[row][col] == '#' && room[y + row][x + col + 1] == '#') {
              move = false;
              break;
            }
          }
        } 
        if (move) {
            ++x;
        }
      } else {
        bool move = true;
        for (int row = 0; row < rock.size(); row++) {
          for (int col = 0; col < rock[row].size(); col++) {
            if (rock[row][col] == '#' && room[y + row][x + col - 1] == '#') {
              move = false;
              break;
            }
          }
        }
        if (move) {
          --x;
        }
      }
      gas++;

      for (int row = 0; row < rock.size(); row++) {
        for (int col = 0; col < rock[row].size(); col++) {
          if (rock[row][col] == '#' && room[y + row - 1][x + col] == '#') {
              stopped = true;
              break;
            }
        }
      }
      if (gas%s.size() == 0) {
         show_last_move = true;
      }
      if (!stopped) {
        --y;
        ++moves;
      } else {
        floor = max(floor, y + (int)rock.size());
        for (int row = 0; row < rock.size(); row++) {
           for (int col = 0; col < rock[row].size(); col++) {
            if (rock[row][col] == '#') {
              room[y+row][x+col] = rock[row][col];
            }
           }
        }
      }
    }

  }
  return floor-1;
}

std::string y2022::solve_17a(const std::vector<std::string> &input) {
  return to_string(tall(input[0], 2022));
}

std::string y2022::solve_17b(const std::vector<std::string> &input) {
  long long rocks = 1000000000000;

  // time to get really dirty
  long long result = (rocks / 1720) * 2738 + tall(input[0], rocks % 1720);

  return to_string(result);
}
