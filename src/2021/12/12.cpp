// Puzzle is available at https://adventofcode.com/2021/day/12
// Keywords: regex, path search
#include "../2021.hpp"
#include "../../utils.hpp"
#include <functional>
#include <regex>
using namespace std;

class Cave {  
 public:
  Cave(const string &name): _name{name} {
    getType(name);
  }
  ~Cave() {}
  enum class CaveType{
    BIG,
    SMALL,
    START,
    END
  };
  vector<uint> neighbors;
  string _name;
  CaveType _type;
 private:
  void getType(string name) {
    if (name == "start") {
      _type = CaveType::START;
    } else if (name == "end") {
      _type = CaveType::END;
    } else if (('A' <= name[0]) && (name[0] <= 'Z')) {
      _type = CaveType::BIG;
    } else if (('a' <= name[0]) && (name[0] <= 'z')) {
      _type = CaveType::SMALL;
    } else {
      cout << "Parsing error: " << name << endl;
    }
  }
};

static int findOrAddCave(vector<Cave> &caves, string name) {
  int pos = -1;
  size_t size = caves.size();
  for(int i = 0; i < size; i++) {
    if (caves[i]._name == name) {
      pos = i;
      break;
    }
  }
  if (pos == -1) {
    caves.push_back(Cave(name));
    pos = size;
  }
  return pos;
}

static void addCavePair(vector<Cave> &caves, const string &name1, const string &name2) {
  int pos1 = findOrAddCave(caves, name1);
  int pos2 = findOrAddCave(caves, name2);
  caves[pos1].neighbors.push_back(pos2);
  caves[pos2].neighbors.push_back(pos1);
}

static size_t countPaths(vector<Cave> &caves, vector<bool> markedCaves, int start, int end, bool hasBonus) {
  size_t count = 0;
  if (caves[start]._type != Cave::CaveType::BIG) {
      markedCaves[start] = true;
  }
  if (start == end) {
    count = 1;
  } else {
    for (auto it = caves[start].neighbors.begin(); it != caves[start].neighbors.end(); it++) {
      if (!markedCaves[*it]) {
          count += countPaths(caves, markedCaves, *it, end, hasBonus);
      } else if (hasBonus && (caves[*it]._type == Cave::CaveType::SMALL)) {
          count += countPaths(caves, markedCaves, *it, end, false);
      }
    }
  }
  return count;
}

static const string solve(vector<string> &input, bool hasBonus) {
    vector<Cave> caves;
  regex reg(R"(([A-Za-z]+)-([A-Za-z]+))");
  smatch match;
  for (int i = 0; i < input.size(); i++) {
    regex_match(input[i], match, reg);
    addCavePair(caves, match[1].str(), match[2].str());
  }

  //FIXME: unsafe
  int start = findOrAddCave(caves, "start");
  int end = findOrAddCave(caves, "end");

  vector<bool> markedCaves(caves.size(), false);

  size_t count = countPaths(caves, markedCaves, start, end, hasBonus);
  return to_string(count);
}

const std::string y2021::solve_12a(const std::vector<std::string> &input) {
  return solve(const_cast<std::vector<std::string>&>(input), false);
}

const std::string y2021::solve_12b(const std::vector<std::string> &input) {
  return solve(const_cast<std::vector<std::string>&>(input), true);
}