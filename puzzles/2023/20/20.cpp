// Puzzle is available at https://adventofcode.com/2023/day/20
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

enum Type {
  NONE,
  BROADCAST,
  FLIPFLOP,
  CONJ,
};

struct Module {
  queue<pair<string, string>> *pulses;
  unordered_map<string, Module> *modules;
  long long *low;
  long long *hi;
  long long l;
  long long h;
  long long *it;
  long long last_it = 0;
  vector<string> outputs;
  bool state;
  unordered_map<string, bool> input_states;
  Type type;
  string name;

  void send_all() {
    for (auto &out : outputs) {
      pulses->push({name, out});
    }
  }

  bool calc_input_state(const string &input) {
    if (type == BROADCAST) {
      return false;
    }
    const auto &m = (*modules)[input];
    switch (m.type) {
      case BROADCAST:
        return false;
      case FLIPFLOP:
        return m.state;
      case CONJ:
        bool pulse = false;
        for (const auto &[k, v] : m.input_states) {
          if (!v) {
            pulse = true;
            break;
          }
        }
        return pulse;
    }
    return false;
  }

  void pulse(const string &input) {
    bool high = calc_input_state(input);
    if (high) {
      (*hi)++;
    } else {
      (*low)++;
    }
    string hl = (high) ? "high" : "low";
    switch (type) {
      case BROADCAST:
        send_all();
        break;
      case FLIPFLOP:
        if (!high) {
          state = !state;
          send_all();
        }
        break;
      case CONJ:
        input_states[input] = high;
        send_all();
        if (high) {
          (*modules)[input].last_it = *it;
        }
        break;
    }
  }
};

static vector<string> search_inputs(
    const unordered_map<string, Module> &modules, const string &name) {
  vector<string> inputs;
  for (const auto &[key, m] : modules) {
    for (const auto &o : m.outputs) {
      if (o == name) {
        inputs.push_back(key);
        break;
      }
    }
  }
  return inputs;
}

std::string y2023::solve_20a(const std::vector<std::string> &input) {
  long long ans = 0;
  unordered_map<string, Module> modules;
  long long low = 0;
  long long high = 0;
  long long it = 1;
  queue<pair<string, string>> q;
  for (const auto &l : input) {
    if (l.size() == 0) {
      break;
    }

    Module m;
    m.modules = &modules;
    m.low = &low;
    m.hi = &high;
    m.it = &it;
    m.pulses = &q;
    m.state = false;

    std::regex word(R"(([a-z]+))");
    auto begin = std::sregex_iterator(l.begin(), l.end(), word);
    auto end = std::sregex_iterator();

    vector<string> names;

    for (std::sregex_iterator i = begin; i != end; ++i) {
      std::smatch match = *i;
      names.push_back(match[1]);
    }

    m.name = names[0];

    for (int i = 1; i < names.size(); ++i) {
      m.outputs.push_back(names[i]);
    }

    if (l[0] == '%') {
      m.type = FLIPFLOP;
    } else if (l[0] == '&') {
      m.type = CONJ;
    } else {
      m.type = BROADCAST;
    }

    modules[m.name] = m;
  }

  for (auto &[k, m] : modules) {
    if (m.type == CONJ) {
      for (const auto &[k2, l] : modules) {
        for (const auto &s : l.outputs) {
          if (s == m.name) {
            m.input_states[l.name] = false;
          }
        }
      }
    }
  }

  Module button;
  button.name = "rx";
  button.modules = &modules;
  button.low = &low;
  button.hi = &high;
  button.pulses = &q;
  modules[button.name] = button;

  for (int i = 0; i < 1000; ++i) {
    q.push({"broadcaster", "broadcaster"});
    while (!q.empty()) {
      auto p = q.front();
      q.pop();
      if (modules.contains(p.second)) {
        modules[p.second].pulse(p.first);
      }
    }
  }

  return to_string(low * high);
}

std::string y2023::solve_20b(const std::vector<std::string> &input) {
  unordered_map<string, Module> modules;
  long long low = 0;
  long long high = 0;
  long long it = 1;
  queue<pair<string, string>> q;
  for (const auto &l : input) {
    if (l.size() == 0) {
      break;
    }

    Module m;
    m.modules = &modules;
    m.low = &low;
    m.hi = &high;
    m.pulses = &q;
    m.state = false;
    m.it = &it;

    std::regex word(R"(([a-z]+))");
    auto begin = std::sregex_iterator(l.begin(), l.end(), word);
    auto end = std::sregex_iterator();

    vector<string> names;

    for (std::sregex_iterator i = begin; i != end; ++i) {
      std::smatch match = *i;
      names.push_back(match[1]);
    }

    m.name = names[0];

    for (int i = 1; i < names.size(); ++i) {
      m.outputs.push_back(names[i]);
    }

    if (l[0] == '%') {
      m.type = FLIPFLOP;
    } else if (l[0] == '&') {
      m.type = CONJ;
    } else {
      m.type = BROADCAST;
    }

    modules[m.name] = m;
  }

  for (auto &[k, m] : modules) {
    if (m.type == CONJ) {
      for (const auto &[k2, l] : modules) {
        for (const auto &s : l.outputs) {
          if (s == m.name) {
            m.input_states[l.name] = false;
          }
        }
      }
    }
  }

  Module button;
  button.name = "rx";
  button.modules = &modules;
  button.low = &low;
  button.hi = &high;
  button.pulses = &q;
  modules[button.name] = button;

  /* Use knowledge about input structure */
  auto first_inputs = search_inputs(modules, "rx");
  auto inputs = search_inputs(modules, first_inputs[0]);

  unordered_map<string, int> cycles;
  while (cycles.size() < 4) {
    q.push({"broadcaster", "broadcaster"});
    while (!q.empty()) {
      auto p = q.front();
      q.pop();
      if (modules.contains(p.second)) {
        modules[p.second].pulse(p.first);
      }
    }
    for (const auto &i : inputs) {
      if (!cycles.contains(i) && modules[i].last_it > 0) {
        cycles[i] = modules[i].last_it;
      }
    }
    ++it;
  }

  long long ans = 1;
  for (const auto &[key, val] : cycles) {
    ans = lcm(ans, val);
  }
  return to_string(ans);
}
