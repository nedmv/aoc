// Puzzle is available at https://adventofcode.com/2023/day/7
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

const vector<char> cards = {'A', 'K', 'Q', 'J', 'T', '9', '8',
                            '7', '6', '5', '4', '3', '2'};

int get_rank(const string &hand) {
  unordered_map<char, int> m;
  for (const auto c : hand) {
    ++m[c];
  }
  vector<int> val;
  for (const auto [k, v] : m) {
    val.push_back(v);
  }
  sort(val.rbegin(), val.rend());

  if (val[0] == 5) {
    return 7;
  } else if (val[0] == 4) {
    return 6;
  } else if (val[0] == 3 && val[1] == 2) {
    return 5;
  } else if (val[0] == 3) {
    return 4;
  } else if (val[0] == 2 && val[1] == 2) {
    return 3;
  } else if (val[0] == 2) {
    return 2;
  } else {
    return 1;
  }
  return 0;
}

struct Game {
  int rank;
  int val;
  string hand;
};

int pos(char search) {
  for (int i = 0; i < cards.size(); ++i) {
    if (search == cards[i]) {
      return i;
    }
  }
  return cards.size();
}

std::string y2023::solve_07a(const std::vector<std::string> &input) {
  long long ans = 0;

  vector<vector<Game>> games(8, vector<Game>());
  for (const auto &line : input) {
    if (line.size() == 0) {
      break;
    }

    Game g;
    g.hand = line.substr(0, 5);
    g.val = stoi(line.substr(6));
    int rank = get_rank(g.hand);
    games[rank].push_back(g);
  }

  int rank = 1;

  for (int i = 1; i <= 7; ++i) {
    sort(games[i].begin(), games[i].end(), [](const Game &l, const Game &r) {
      vector<int> pos_l(5);
      vector<int> pos_r(5);
      for (int i = 0; i < 5; ++i) {
        pos_l[i] = pos(l.hand[i]);
        pos_r[i] = pos(r.hand[i]);
        if (pos_l[i] < pos_r[i]) {
          return false;
        }
        if (pos_l[i] > pos_r[i]) {
          return true;
        }
      }
      return false;
    });

    for (int j = 0; j < games[i].size(); ++j) {
      ans += rank * games[i][j].val;
      ++rank;
    }
  }
  return to_string(ans);
}

const vector<char> cards2 = {'A', 'K', 'Q', 'T', '9', '8', '7',
                             '6', '5', '4', '3', '2', 'J'};
int pos2(char search) {
  for (int i = 0; i < cards2.size(); ++i) {
    if (search == cards2[i]) {
      return i;
    }
  }
  return cards2.size();
}

int get_rank2(const string &hand) {
  unordered_map<char, int> m;
  for (const auto c : hand) {
    ++m[c];
  }
  int jokers = 0;
  if (m.contains('J')) {
    jokers = m['J'];
    m['J'] = 0;
  }

  vector<int> val;
  for (const auto [k, v] : m) {
    val.push_back(v);
  }
  sort(val.rbegin(), val.rend());
  val[0] += jokers;

  if (val[0] == 5) {
    return 7;
  } else if (val[0] == 4) {
    return 6;
  } else if (val[0] == 3 && val[1] == 2) {
    return 5;
  } else if (val[0] == 3) {
    return 4;
  } else if (val[0] == 2 && val[1] == 2) {
    return 3;
  } else if (val[0] == 2) {
    return 2;
  } else {
    return 1;
  }
  return 0;
}

std::string y2023::solve_07b(const std::vector<std::string> &input) {
  long long ans = 0;

  vector<vector<Game>> games(8, vector<Game>());
  for (const auto &line : input) {
    if (line.size() == 0) {
      break;
    }

    Game g;
    g.hand = line.substr(0, 5);
    g.val = stoi(line.substr(6));
    int rank = get_rank2(g.hand);
    games[rank].push_back(g);
  }

  int rank = 1;

  for (int i = 1; i <= 7; ++i) {
    sort(games[i].begin(), games[i].end(), [](const Game &l, const Game &r) {
      vector<int> pos_l(5);
      vector<int> pos_r(5);
      for (int i = 0; i < 5; ++i) {
        pos_l[i] = pos2(l.hand[i]);
        pos_r[i] = pos2(r.hand[i]);
        if (pos_l[i] < pos_r[i]) {
          return false;
        }
        if (pos_l[i] > pos_r[i]) {
          return true;
        }
      }
      return false;
    });

    for (int j = 0; j < games[i].size(); ++j) {
      ans += rank * games[i][j].val;
      ++rank;
    }
  }
  return to_string(ans);
}
