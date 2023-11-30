// Puzzle is available at https://adventofcode.com/2022/day/19
// Keywords:
#include "../2022.hpp"
#include "../../../src/utils.hpp"

#include <algorithm>
#include <atomic>
#include <cassert>
// #include <execution>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;





int check(const vector<int> &b, vector<int> robots, vector<int> res, int turn, unordered_map<int, unordered_map<int, unordered_map<int, int>>> &dp) {
  if (turn >= 24) {
    return res[3]; //geodes
  }

  int robot_sum = robots[0] + 100 * robots[1] + 10000 * robots[2] + 1000000 * robots[3];
  int res_sum = res[0] + 100 * res[1] + 10000 * res[2] + 1000000 * res[3];
  if (dp.contains(turn) && dp[turn].contains(robot_sum) && dp[turn][robot_sum].contains(res_sum)) {
    return dp[turn][robot_sum][res_sum];
  }
  // if (dp.contains(turn) && dp[turn].contains(robots) && dp[turn][robots].contains(res)) {
  //   return dp[turn][robots][res];
  // }
  // if (dp.contains(turn)) {
  //   return dp[turn];
  // }
  vector<int> results;
  // cout << turn << " " << endl;

  if (res[2] >= b[6] && res[0] >= b[5]) { //build geode
    auto res_copy = res;
    res_copy[2] -= b[6];
    res_copy[0] -= b[5];
    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }
    auto r_copy = robots;
    ++r_copy[3];
    results.push_back(check(b, r_copy, res_copy, turn+1, dp));
  }
  if (res[1] >= b[4] && res[0] >= b[3]) {// build obs
    auto res_copy = res;
    res_copy[1] -= b[4];
    res_copy[0] -= b[3];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[2];
    results.push_back(check(b, r_copy, res_copy, turn+1, dp));
  }
  if (res[0] >= b[2]) { // build clay
    auto res_copy = res;
    res_copy[0] -= b[2];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[1];
    results.push_back(check(b, r_copy, res_copy, turn+1, dp));
  }
  if (res[0] >= b[1]) { // build ore
    auto res_copy = res;
    res_copy[0] -= b[1];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[0];
    results.push_back(check(b, r_copy, res_copy, turn+1, dp));
  }
  vector<int> res_copy = res;
  for (int i = 0; i < res.size(); ++i) { //no build
    res_copy[i] += robots[i];
  }
  results.push_back(check(b, robots, res_copy, turn+1, dp));

  sort(results.rbegin(), results.rend());
  dp[turn][robot_sum][res_sum] = results[0];
  // cout << results.size() << endl;
  return results[0];
}

int check2(const vector<int> &b, vector<int> robots, vector<int> res, int turn, unordered_map<int, unordered_map<int, unordered_map<int, int>>> &dp) {
  if (turn >= 32) {
    return res[3]; //geodes
  }

  int robot_sum = robots[0] + 100 * robots[1] + 10000 * robots[2] + 1000000 * robots[3];
  int res_sum = res[0] + 100 * res[1] + 10000 * res[2] + 1000000 * res[3];
  if (dp.contains(turn) && dp[turn].contains(robot_sum) && dp[turn][robot_sum].contains(res_sum)) {
    return dp[turn][robot_sum][res_sum];
  }
  // if (dp.contains(turn) && dp[turn].contains(robots) && dp[turn][robots].contains(res)) {
  //   return dp[turn][robots][res];
  // }
  // if (dp.contains(turn)) {
  //   return dp[turn];
  // }
  vector<int> results;
  // cout << turn << " " << endl;

  if (res[2] >= b[6] && res[0] >= b[5]) { //build geode
    auto res_copy = res;
    res_copy[2] -= b[6];
    res_copy[0] -= b[5];
    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }
    auto r_copy = robots;
    ++r_copy[3];
    results.push_back(check2(b, r_copy, res_copy, turn+1, dp));
  }
  if (res[1] >= b[4] && res[0] >= b[3] && robots[2] < b[6]) {// build obs
    auto res_copy = res;
    res_copy[1] -= b[4];
    res_copy[0] -= b[3];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[2];
    results.push_back(check2(b, r_copy, res_copy, turn+1, dp));
  }
  if (res[0] >= b[2] && robots[1] < b[4]) { // build clay
    auto res_copy = res;
    res_copy[0] -= b[2];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[1];
    results.push_back(check2(b, r_copy, res_copy, turn+1, dp));
  }
  if (res[0] >= b[1] && robots[0] < max(max(max(b[5], b[3]), b[2]), b[1])) { // build ore
    auto res_copy = res;
    res_copy[0] -= b[1];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[0];
    results.push_back(check2(b, r_copy, res_copy, turn+1, dp));
  }
  vector<int> res_copy = res;
  for (int i = 0; i < res.size(); ++i) { //no build
    res_copy[i] += robots[i];
  }
  results.push_back(check2(b, robots, res_copy, turn+1, dp));

  sort(results.rbegin(), results.rend());
  dp[turn][robot_sum][res_sum] = results[0];
  // cout << results.size() << endl;
  return results[0];
}

struct Snapshot {
  vector<int> bp;
  vector<int> robots;
  vector<int> res;
  bool operator<(const Snapshot& other) const {
      int robot_sum = robots[0] + 100 * robots[1] + 10000 * robots[2] + 1000000 * robots[3];
      int res_sum = res[0] + 100 * res[1] + 10000 * res[2] + 1000000 * res[3];
      int other_robot_sum = other.robots[0] + 100 * other.robots[1] + 10000 * other.robots[2] + 1000000 * other.robots[3];
      int other_res_sum = other.res[0] + 100 * other.res[1] + 10000 * other.res[2] + 1000000 * other.res[3];
      // return (robot_sum + res_sum) < (other_robot_sum + other_res_sum);
      return robot_sum < other_robot_sum;
  }
};

// int check16(const vector<int> &b, vector<int> robots, vector<int> res, int turn, unordered_map<int, unordered_map<int, unordered_map<int, int>>> &dp) {
//   if (turn >= ) {
//     return res[3]; //geodes
//   }

//   int robot_sum = robots[0] + 100 * robots[1] + 10000 * robots[2] + 1000000 * robots[3];
//   int res_sum = res[0] + 100 * res[1] + 10000 * res[2] + 1000000 * res[3];
//   if (dp.contains(turn) && dp[turn].contains(robot_sum) && dp[turn][robot_sum].contains(res_sum)) {
//     return dp[turn][robot_sum][res_sum];
//   }
//   // if (dp.contains(turn) && dp[turn].contains(robots) && dp[turn][robots].contains(res)) {
//   //   return dp[turn][robots][res];
//   // }
//   // if (dp.contains(turn)) {
//   //   return dp[turn];
//   // }
//   vector<int> results;
//   // cout << turn << " " << endl;

//   if (res[2] >= b[6] && res[0] >= b[5]) { //build geode
//     auto res_copy = res;
//     res_copy[2] -= b[6];
//     res_copy[0] -= b[5];
//     for (int i = 0; i < res_copy.size(); ++i) {
//       res_copy[i] += robots[i];
//     }
//     auto r_copy = robots;
//     ++r_copy[3];
//     results.push_back(check16(b, r_copy, res_copy, turn+1, dp));
//   } else if (res[1] >= b[4] && res[0] >= b[3]) {// build obs
//     auto res_copy = res;
//     res_copy[1] -= b[4];
//     res_copy[0] -= b[3];

//     for (int i = 0; i < res_copy.size(); ++i) {
//       res_copy[i] += robots[i];
//     }

//     auto r_copy = robots;
//     ++r_copy[2];
//     results.push_back(check16(b, r_copy, res_copy, turn+1, dp));
//   } else if (res[0] >= b[2]) { // build clay
//     auto res_copy = res;
//     res_copy[0] -= b[2];

//     for (int i = 0; i < res_copy.size(); ++i) {
//       res_copy[i] += robots[i];
//     }

//     auto r_copy = robots;
//     ++r_copy[1];
//     results.push_back(check16(b, r_copy, res_copy, turn+1, dp));
//   } else if (res[0] >= b[1]) { // build ore
//     auto res_copy = res;
//     res_copy[0] -= b[1];

//     for (int i = 0; i < res_copy.size(); ++i) {
//       res_copy[i] += robots[i];
//     }

//     auto r_copy = robots;
//     ++r_copy[0];
//     results.push_back(check16(b, r_copy, res_copy, turn+1, dp));
//   } else {
//     vector<int> res_copy = res;
//     for (int i = 0; i < res.size(); ++i) { //no build
//       res_copy[i] += robots[i];
//     }
//     results.push_back(check16(b, robots, res_copy, turn+1, dp));
//   }

//   sort(results.rbegin(), results.rend());
//   dp[turn][robot_sum][res_sum] = results[0];
//   // cout << results.size() << endl;
//   return results[0];
// }


int check16(const vector<int> &b, vector<int> robots, vector<int> res, int turn, unordered_map<int, unordered_map<int, unordered_map<int, int>>> &dp) {
  if (turn >= 16) {
    return res[3]; //geodes
  }

  int robot_sum = robots[0] + 100 * robots[1] + 10000 * robots[2] + 1000000 * robots[3];
  int res_sum = res[0] + 100 * res[1] + 10000 * res[2] + 1000000 * res[3];
  if (dp.contains(turn) && dp[turn].contains(robot_sum) && dp[turn][robot_sum].contains(res_sum)) {
    return dp[turn][robot_sum][res_sum];
  }
  // if (dp.contains(turn) && dp[turn].contains(robots) && dp[turn][robots].contains(res)) {
  //   return dp[turn][robots][res];
  // }
  // if (dp.contains(turn)) {
  //   return dp[turn];
  // }
  vector<int> results;
  // cout << turn << " " << endl;

  if (res[2] >= b[6] && res[0] >= b[5]) { //build geode
    auto res_copy = res;
    res_copy[2] -= b[6];
    res_copy[0] -= b[5];
    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }
    auto r_copy = robots;
    ++r_copy[3];
    results.push_back(check16(b, r_copy, res_copy, turn+1, dp));
  } 
  if (res[1] >= b[4] && res[0] >= b[3]) {// build obs
    auto res_copy = res;
    res_copy[1] -= b[4];
    res_copy[0] -= b[3];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[2];
    results.push_back(check16(b, r_copy, res_copy, turn+1, dp));
  } 
  if (res[0] >= b[2]) { // build clay
    auto res_copy = res;
    res_copy[0] -= b[2];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[1];
    results.push_back(check16(b, r_copy, res_copy, turn+1, dp));
  } 
  if (res[0] >= b[1]) { // build ore
    auto res_copy = res;
    res_copy[0] -= b[1];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[0];
    results.push_back(check16(b, r_copy, res_copy, turn+1, dp));
  } 
  {
    vector<int> res_copy = res;
    for (int i = 0; i < res.size(); ++i) { //no build
      res_copy[i] += robots[i];
    }
    results.push_back(check16(b, robots, res_copy, turn+1, dp));
  }

  sort(results.rbegin(), results.rend());
  dp[turn][robot_sum][res_sum] = results[0];
  // cout << results.size() << endl;
  return results[0];
}

vector<Snapshot> snap16(const vector<int> &b, vector<int> robots, vector<int> res, int turn, unordered_map<int, unordered_map<int, unordered_map<int, int>>> &dp) {
  if (turn >= 16) {
    Snapshot s;
    s.bp = b;
    s.res = res;
    s.robots = robots;
    vector<Snapshot> vec;
    vec.push_back(s);
    return vec;
  }

  // int robot_sum = robots[0] + 100 * robots[1] + 10000 * robots[2] + 1000000 * robots[3];
  // int res_sum = res[0] + 100 * res[1] + 10000 * res[2] + 1000000 * res[3];
  // if (dp.contains(turn) && dp[turn].contains(robot_sum) && dp[turn][robot_sum].contains(res_sum)) {
  //   return dp[turn][robot_sum][res_sum];
  // }
  // if (dp.contains(turn) && dp[turn].contains(robots) && dp[turn][robots].contains(res)) {
  //   return dp[turn][robots][res];
  // }
  // if (dp.contains(turn)) {
  //   return dp[turn];
  // }
  vector<Snapshot> results;
  // cout << turn << " " << endl;

  if (res[2] >= b[6] && res[0] >= b[5]) { //build geode
    auto res_copy = res;
    res_copy[2] -= b[6];
    res_copy[0] -= b[5];
    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }
    auto r_copy = robots;
    ++r_copy[3];
    auto snap = snap16(b, r_copy, res_copy, turn+1, dp);
    results.insert(results.end(), snap.begin(), snap.end());
  } 
  if (res[1] >= b[4] && res[0] >= b[3]) {// build obs
    auto res_copy = res;
    res_copy[1] -= b[4];
    res_copy[0] -= b[3];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[2];
    auto snap = snap16(b, r_copy, res_copy, turn+1, dp);
    results.insert(results.end(), snap.begin(), snap.end());
  } 
  if (res[0] >= b[2]) { // build clay
    auto res_copy = res;
    res_copy[0] -= b[2];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[1];
    auto snap = snap16(b, r_copy, res_copy, turn+1, dp);
    results.insert(results.end(), snap.begin(), snap.end());
  } 
  if (res[0] >= b[1]) { // build ore
    auto res_copy = res;
    res_copy[0] -= b[1];

    for (int i = 0; i < res_copy.size(); ++i) {
      res_copy[i] += robots[i];
    }

    auto r_copy = robots;
    ++r_copy[0];
    auto snap = snap16(b, r_copy, res_copy, turn+1, dp);
    results.insert(results.end(), snap.begin(), snap.end());
  } 
  {
    vector<int> res_copy = res;
    for (int i = 0; i < res.size(); ++i) { //no build
      res_copy[i] += robots[i];
    }
    auto snap = snap16(b, robots, res_copy, turn+1, dp);
      results.insert(results.end(), snap.begin(), snap.end());
  }


  // dp[turn][robot_sum][res_sum] = results[0];
  // cout << results.size() << endl;
  return results;
}


std::string y2022::solve_19a(const std::vector<std::string> &input) {
  vector<vector<int>> prints; //0-num, 1-ore cost in ore, 2-clay cost in ore, 3-obsidian cost in ore, 4-obs cost in clay, 5-geode cost in ore, 6-geode cost in obs
  for (int i = 0; i < input.size(); ++i) {
    prints.push_back(ints(input[i]));
  }

  int qual = 0;
  for (auto p: prints) {
    for (int i = 0; i < p.size(); ++i) {
      cout << p[i] << " ";
    }
    cout << endl;
    vector<int> robots(4, 0);
    robots[0]++;
    vector<int> res(4, 0);
    unordered_map<int, unordered_map<int, unordered_map<int, int>>> dp;
    int cur = check2(p, robots, res, 0, dp);
    qual += p[0] * cur;
    cout << "Finished " << p[0] << " " << cur << endl; 
  }
  return to_string(qual);
}

std::string y2022::solve_19b(const std::vector<std::string> &input) {
vector<vector<int>> prints; //0-num, 1-ore cost in ore, 2-clay cost in ore, 3-obsidian cost in ore, 4-obs cost in clay, 5-geode cost in ore, 6-geode cost in obs
  for (int i = 0; i < 3; ++i) {
    prints.push_back(ints(input[i]));
  }

  int qual = 1;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < prints[i].size(); ++j) {
      cout << prints[i][j] << " ";
    }
    cout << endl;
    vector<int> robots(4, 0);
    robots[0]++;
    vector<int> res(4, 0);
    // map<int, map<vector<int>, map<vector<int>, int>>> dp;
    unordered_map<int, unordered_map<int, unordered_map<int, int>>> dp;
    int cur = check2(prints[i], robots, res, 0, dp);
    qual *= cur;
    cout << "Finished " << prints[i][0] << " " << cur << endl; 

    
  }
  return to_string(qual);
}
