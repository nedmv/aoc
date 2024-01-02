// Puzzle is available at https://adventofcode.com/2023/day/23
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

struct Data {
  int len;
  pair<int, int> pos;
  set<pair<int, int>> visited;
};

bool correct(const vector<vector<char>> &m, pair<int, int> pos) {
  return pos.first >= 0 && pos.first < m.size() && pos.second >= 0 &&
         pos.second < m[0].size() && m[pos.first][pos.second] != '#';
}

std::string y2023::solve_23a(const std::vector<std::string> &input) {
  long long ans = 0;

  auto m = char_map(input);

  pair<int, int> start{0, 1};
  pair<int, int> finish{(int)m.size() - 1, (int)m[0].size() - 2};

  auto cmp = [](const Data &l, const Data &r) { return (l.len < r.len); };
  priority_queue<Data, vector<Data>, decltype(cmp)> q;
  Data d;
  d.len = 0;
  d.pos = start;
  set<pair<int, int>> visited;
  visited.insert(start);
  d.visited = visited;
  q.push(d);
  vector<int> dirs = {1, 0, -1, 0, 1};
  vector<char> downhill = {'v', '<', '^', '>'};
  while (!q.empty()) {
    auto e = q.top();
    q.pop();
    if (e.pos == finish) {
      ans = e.len;
      break;
    }

    int down_dir = -1;
    for (int i = 0; i < 4; ++i) {
      if (downhill[i] == m[e.pos.first][e.pos.second]) {
        down_dir = i;
      }
    }
    if (down_dir >= 0) {
      Data next = e;
      Data prev;
      do {
        pair<int, int> p(next.pos.first + dirs[down_dir],
                         next.pos.second + dirs[down_dir + 1]);
        if (next.visited.contains(p)) {
          break;
        }
        if (correct(m, p)) {
          next.pos = p;
          next.len++;
          next.visited.insert(next.pos);
          prev = next;
        } else {
          q.push(prev);
          break;
        }
      } while (true);
    } else {
      for (int i = 0; i < 4; ++i) {
        pair<int, int> p(e.pos.first + dirs[i], e.pos.second + dirs[i + 1]);

        if (e.visited.contains(p)) {
          continue;
        }
        if (correct(m, p)) {
          Data next = e;
          next.pos = p;
          next.len++;
          next.visited.insert(next.pos);
          q.push(next);
        }
      }
    }
  }

  return to_string(ans);
}

bool is_node(vector<vector<char>> &m, pair<int, int> pos) {
  if (pos.first == 0 && pos.second == 1) {
    return true;  // start
  }
  if (pos.first == m.size() - 1 && pos.second == m[0].size() - 2) {
    return true;  // finish
  }
  if (!correct(m, pos)) {
    return false;
  }
  vector<int> dirs = {1, 0, -1, 0, 1};
  int count = 0;
  for (int i = 0; i < 4; ++i) {
    if (correct(m, make_pair(pos.first + dirs[i], pos.second + dirs[i + 1]))) {
      ++count;
    }
  }

  return count > 2;
}

long long rec(long long id, long long visited, long long len,
              map<long long, map<long long, long long>> &dp,
              vector<vector<long long>> &adj) {
  if (id == adj.size() - 1) {
    return len;  // finish
  }
  visited |= (1LL << id);
  if (dp.contains(id) && dp[id].contains(visited)) {
    return dp[id][visited];
  }
  long long ans = -1;
  for (long long i = 0; i < adj.size(); ++i) {
    if (adj[id][i] > 0 && (((visited >> i) & 1LL) == 0)) {
      long long cur = rec(i, visited, 0, dp, adj);
      if (cur == -1) {
        continue;
      } else {
        ans = max(ans, adj[id][i] + cur);
      }
    }
  }
  if (ans == -1) {
    return -1;
  }
  ans += len;
  return dp[id][visited] = ans;
}

std::string y2023::solve_23b(const std::vector<std::string> &input) {
  long long ans = 0;

  auto m = char_map(input);

  pair<long long, long long> start{0, 1};
  pair<long long, long long> finish{(long long)m.size() - 1,
                                    (long long)m[0].size() - 2};

  vector<long long> dirs = {1, 0, -1, 0, 1};

  long long count = 0;

  vector<pair<long long, long long>> nodes;

  for (long long i = 0; i < m.size(); ++i) {
    for (long long j = 0; j < m[0].size(); ++j) {
      pair<long long, long long> e(i, j);
      if (is_node(m, e)) {
        nodes.push_back(e);
      }
    }
  }

  vector<vector<long long>> dist(nodes.size(),
                                 vector<long long>(nodes.size(), 0));

  for (long long n = 0; n < nodes.size(); ++n) {
    auto node = nodes[n];
    queue<vector<long long>> neigh;
    set<pair<long long, long long>> vis;
    vis.insert({node.first, node.second});
    for (long long i = 0; i < 4; ++i) {
      if (correct(m,
                  make_pair(node.first + dirs[i], node.second + dirs[i + 1]))) {
        neigh.push({1, node.first + dirs[i], node.second + dirs[i + 1],
                    node.first, node.second});
        vis.insert({node.first + dirs[i], node.second + dirs[i + 1]});
      }
    }

    while (!neigh.empty()) {
      auto e = neigh.front();
      neigh.pop();
      long long id = -1;
      pair<long long, long long> cur(e[1], e[2]);
      for (long long i = 0; i < nodes.size(); ++i) {
        if (cur == nodes[i] && i != n) {
          id = i;
          break;
        }
      }
      if (id >= 0) {
        dist[n][id] = e[0];
      } else {
        pair<long long, long long> last(e[3], e[4]);
        for (long long i = 0; i < 4; ++i) {
          pair<long long, long long> p(e[1] + dirs[i], e[2] + dirs[i + 1]);
          if (p != last && correct(m, p) && !vis.contains(p)) {
            vis.insert(p);
            neigh.push(
                {e[0] + 1, e[1] + dirs[i], e[2] + dirs[i + 1], e[1], e[2]});
          }
        }
      }
    }
  }

  set<long long> v;
  map<long long, map<long long, long long>> dp;
  ans = rec(0, 0LL, 0, dp, dist);
  return to_string(ans);
}