// Puzzle is available at https://adventofcode.com/2023/day/25
// Keywords:
#include "../2023.hpp"
#include "../../../src/utils.hpp"
using namespace std;

struct Component {
  int id;
  vector<string> con;
};

struct DisjointSet {
  vector<int> parent;
  vector<int> size;

  DisjointSet(int n) {
    parent = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
    size = vector<int>(n, 1);
  }

  int find(int x) {
    if (parent[x] == x) {
      return x;
    }
    return parent[x] = find(parent[x]);
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y) {
      return false;
    }

    if (size[x] < size[y]) {
      swap(x, y);
    }
    parent[y] = x;
    size[x] += size[y];
    return true;
  }
};

std::string y2023::solve_25a(const std::vector<std::string> &input) {
  long long ans = 0;
  unordered_map<string, Component> comp;
  int id = 0;
  for (auto &l: input) {
    string name = l.substr(0, 3);
    Component c;
    c.id = id++;
    c.con = split(l.substr(5), " ");
    comp[name] = c;
  }

  unordered_set<string> insertions;
  for (const auto &[k, v]: comp) {
    for (const auto &c: v.con) {
      if (!comp.contains(c)) {
        insertions.insert(c);
      }
    }
  }
  for (const auto &i: insertions) {
    Component c;
    c.id = id++;
    comp[i] = c;
  }

  int n = comp.size();
  vector<pair<int, int>> edges;
  for (const auto &[k, v]: comp) {
    for (const auto &c: v.con) {
      edges.push_back(make_pair(v.id, comp[c].id));
    }
  }

  srand(time(0));
  int it_count = 0;
  while (true) {
    ++it_count;
    auto edge = edges;
    DisjointSet ds(n);
    int count = n;

    while (count > 2) {
      int pos = rand() % edge.size();
      if (ds.unite(edge[pos].first, edge[pos].second)) {
        --count;
      }
      edge.erase(edge.begin()+pos);
    }

    int removals = 0;

    for (const auto &[a, b]: edges) {
      if (ds.find(a) != ds.find(b)) {
        ++removals;
        if (removals > 3) {
          break;
        }
      }
    }

    if (removals == 3) {
      int first_size = ds.size[ds.find(0)];
      ans = first_size * (n - first_size);
      cout << "total iterations: " << it_count << endl;
      break;
    }
  }
  return to_string(ans);
}