// Puzzle is available at https://adventofcode.com/2022/day/16
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

struct Valve {
  string name;
  int rate;
  vector<string> tunnels;
};

map<string, map<int, map<int, int>>> dp;

int act(map<string, Valve> &valves, set<string> opened, string current,
        int turn, int score) {
  if (turn == 29) {
    return score;
  }
  if (dp.find(current) != dp.end() &&
      dp[current].find(turn) != dp[current].end() &&
      dp[current][turn].find(score) != dp[current][turn].end()) {
    return dp[current][turn][score];
  }
  vector<int> scores;
  if (!opened.contains(current) && valves[current].rate > 0) {
    set<string> copy = opened;
    copy.insert(current);
    scores.push_back(act(valves, copy, current, turn + 1,
                         score + valves[current].rate * (29 - turn)));
  }
  for (auto tunnel : valves[current].tunnels) {
    scores.push_back(act(valves, opened, tunnel, turn + 1, score));
  }
  sort(scores.rbegin(), scores.rend());
  dp[current][turn][score] = scores[0];
  return scores[0];
}

std::string y2022::solve_16a(const std::vector<std::string> &input) {
  map<string, Valve> valves;
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].empty()) {
      break;
    }
    string name = input[i].substr(6, 2);
    Valve v;
    v.name = name;
    v.rate = stoi(input[i].substr(23, input[i].find(';') - 23));
    int pos = input[i].find("tunnels lead to valves ");

    if (pos != -1) {
      pos += 23;
      while (pos < input[i].size()) {
        v.tunnels.push_back(input[i].substr(pos, 2));
        pos += 4;
      }
    } else {
      pos = input[i].find("tunnel leads to valve ");
      pos += 22;
      v.tunnels.push_back(input[i].substr(pos, 2));
    }

    valves[name] = v;
  }
  for (auto v : valves) {
    cout << v.second.name << endl;
    for (auto t : v.second.tunnels) {
      cout << " " << t;
    }
    cout << "\n";
  }
  return to_string(act(valves, set<string>(), "AA", 0, 0));
}

map<string, map<int, map<int, int>>> dp2;

int act2(map<string, Valve> &valves, set<string> opened, string current,
         string backup, int turn, int score, bool useCurrent) {
  if (turn == 25) {
    return score;
  }
  string marker = (current < backup) ? current + backup : backup + current;

  int t = useCurrent ? turn : turn + 50;

  if (dp2.find(marker) != dp2.end() &&
      dp2[marker].find(t) != dp2[marker].end() &&
      dp2[marker][t].find(score) != dp2[marker][t].end()) {
    return dp[marker][turn][score];
  }

  vector<int> scores;
  if (useCurrent) {
    if (!opened.contains(current) && valves[current].rate > 0) {
      set<string> copy = opened;
      copy.insert(current);
      scores.push_back(act2(valves, copy, current, backup, turn,
                            score + valves[current].rate * (25 - turn), false));
    }
    for (auto tunnel : valves[current].tunnels) {
      scores.push_back(
          act2(valves, opened, tunnel, backup, turn, score, false));
    }
  } else {
    if (!opened.contains(backup) && valves[backup].rate > 0) {
      set<string> copy = opened;
      copy.insert(backup);
      scores.push_back(act2(valves, copy, current, backup, turn + 1,
                            score + valves[backup].rate * (25 - turn), true));
    }
    for (auto tunnel : valves[backup].tunnels) {
      scores.push_back(
          act2(valves, opened, current, tunnel, turn + 1, score, true));
    }
  }
  sort(scores.rbegin(), scores.rend());
  dp2[marker][t][score] = scores[0];
  return scores[0];
}

std::string y2022::solve_16b(const std::vector<std::string> &input) {
  map<string, Valve> valves;
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].empty()) {
      break;
    }
    string name = input[i].substr(6, 2);
    Valve v;
    v.name = name;
    v.rate = stoi(input[i].substr(23, input[i].find(';') - 23));
    int pos = input[i].find("tunnels lead to valves ");

    if (pos != -1) {
      pos += 23;
      while (pos < input[i].size()) {
        v.tunnels.push_back(input[i].substr(pos, 2));
        pos += 4;
      }
    } else {
      pos = input[i].find("tunnel leads to valve ");
      pos += 22;
      v.tunnels.push_back(input[i].substr(pos, 2));
    }

    valves[name] = v;
  }
  int result = act2(valves, set<string>(), "AA", "AA", 0, 0, true);
  return to_string(result);
}
