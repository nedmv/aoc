// Puzzle is available at https://adventofcode.com/2020/day/7
#include "../2020.hpp"
using namespace std;

class Bag {
 public:
  Bag(){};
  explicit Bag(const string &input) {
    regex r_name(R"(([a-z ]+) bags contain)");
    regex r_insides(R"( ([0-9]+) ([a-z ]+) bag[s]?[,.])");
    smatch match;
    string str = input;
    regex_search(str, match, r_name);
    _name = match[1].str();
    while (regex_search(str, match, r_insides)) {
      _insides.insert(pair(match[2].str(), stoi(match[1].str())));
      str = match.suffix().str();
    }
  }
  ~Bag(){};
  map<string, size_t> _insides;
  string _name;
};

static inline bool isInsideBag(const string &name, const Bag &bag) {
  auto insides = bag._insides;
  if (insides.find(name) != insides.end()) return true;
  return false;
}

static inline bool isInsideList(const string &name, vector<string> list) {
  if (find(list.begin(), list.end(), name) != list.end()) return true;
  return false;
}

static size_t countPossibleContainers(string name, vector<Bag> &bags) {
  vector<string> list;
  list.push_back(name);
  size_t n_min = 0;
  size_t n_max = list.size();
  do {
    for (size_t n = n_min; n < n_max; n++) {
      for (size_t i = 0; i < bags.size(); i++) {
        if (isInsideBag(list[n], bags[i]) &&
            !isInsideList(bags[i]._name, list)) {
          list.push_back(bags[i]._name);
        }
      }
    }
    n_min = n_max;
    n_max = list.size();
  } while (n_min != n_max);

  list.erase(list.begin());  // remove target bag from result
  return list.size();
}

#if 0  // debug print
ostream &operator<<(ostream &os, Bag &bag) {
  auto print = [](std::pair<string, size_t> p) {
    cout << "  Name: " << p.first << endl;
    cout << "  Value: " << p.second << endl;
  };
  os << "Name: " << bag._name << endl;
  os << "Insides: " << endl;
  auto insides = bag._insides;
  for_each(insides.begin(), insides.end(), print);
  return os;
}
#endif

std::string y2020::solve_07a(const std::vector<std::string> &input) {
  vector<Bag> bags;
  Bag bag;
  for (size_t i = 0; i < input.size(); i++) {
    bag = Bag(input[i]);
    bags.push_back(bag);
  }
  return to_string(countPossibleContainers("shiny gold", bags));
}

static size_t findBagId(const string &name, const vector<Bag> &bags) {
  for (size_t i = 0; i < bags.size(); i++) {
    if (bags[i]._name == name) return i;
  }
  return bags.size();
}

static size_t countInsides(const string &name, vector<Bag> &bags) {
  size_t counter = 1;
  auto insides = bags[findBagId(name, bags)]._insides;
  for (auto const &[key, val] : insides) {
    counter += val * countInsides(key, bags);
  }
  return counter;
}

std::string y2020::solve_07b(const std::vector<std::string> &input) {
  vector<Bag> bags;
  Bag bag;
  for (size_t i = 0; i < input.size(); i++) {
    bag = Bag(input[i]);
    bags.push_back(bag);
  }
  return to_string(countInsides("shiny gold", bags) - 1);
}
