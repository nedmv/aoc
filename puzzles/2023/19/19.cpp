// Puzzle is available at https://adventofcode.com/2023/day/19
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

struct Part {
  long long x;
  long long m;
  long long a;
  long long s;
};

struct Rule {
  char type;
  bool less;
  long long val;
  string next;
};

struct Workflow {
  string name;
  vector<Rule> rules;
  string next(const Part &p) {
    for (const auto &r : rules) {
      long long val = 0;
      switch (r.type) {
        case 'x':
          val = p.x;
          break;
        case 'm':
          val = p.m;
          break;
        case 'a':
          val = p.a;
          break;
        case 's':
          val = p.s;
          break;
        case 'o':
          return r.next;
      }
      if (r.less) {
        if (val < r.val) {
          return r.next;
        }
      } else {
        if (val > r.val) {
          return r.next;
        }
      }
    }
    return rules.back().next;
  }
};

struct PartRange {
  long long x_min;
  long long x_max;
  long long m_min;
  long long m_max;
  long long a_min;
  long long a_max;
  long long s_min;
  long long s_max;
  bool valid() {
    if (x_max < x_min || m_max < m_min || a_max < a_min || s_max < s_min) {
      return false;
    }
    return true;
  }
  void print() {
    cout << "x: " << x_max << " " << x_min;
    cout << ", m: " << m_max << " " << m_min;
    cout << ", a: " << a_max << " " << a_min;
    cout << ", s: " << s_max << " " << s_min;
    cout << ", valid: " << valid() << endl;
  }
};

struct NewRanges {
  PartRange ok;
  PartRange fail;
};

struct Split {
  long long l_min = 4001;
  long long l_max = 0;
  long long r_min = 4001;
  long long r_max = 0;
};

Split split_range(long long l, long long r, long long val, bool less) {
  Split s;
  if (l == val) {
    if (!less) {
      s.l_min = val;
      s.l_max = val;
      s.r_min = val + 1;
      s.r_max = r;
    } else {
      s.r_min = val;
      s.r_max = r;
    }
  } else if (r == val) {
    if (less) {
      s.l_min = l;
      s.l_max = val - 1;
      s.r_min = val;
      s.r_max = val;
    } else {
      s.l_min = l;
      s.l_max = val;
    }
  } else if (l > val) {
    s.r_min = l;
    s.r_max = r;
  } else if (r < val) {
    s.l_min = l;
    s.l_max = r;
  } else {
    if (less) {
      s.l_min = l;
      s.l_max = val - 1;
      s.r_min = val;
      s.r_max = r;
    } else {
      s.l_min = l;
      s.l_max = val;
      s.r_min = val + 1;
      s.r_max = r;
    }
  }
  return s;
}

NewRanges split(PartRange &p, const Rule &r) {  // left -> cond, right != cond
  char type = r.type;
  bool less = r.less;
  long long val = r.val;

  NewRanges result;
  result.ok = p;
  result.fail = p;

  if (type == 'o') {
    result.fail.x_min = 4001;
    return result;
  }
  Split s;
  switch (type) {
    case 'x':
      s = split_range(p.x_min, p.x_max, val, less);
      result.ok.x_min = less ? s.l_min : s.r_min;
      result.ok.x_max = less ? s.l_max : s.r_max;
      result.fail.x_min = less ? s.r_min : s.l_min;
      result.fail.x_max = less ? s.r_max : s.l_max;
      break;
    case 'm':
      s = split_range(p.m_min, p.m_max, val, less);
      result.ok.m_min = less ? s.l_min : s.r_min;
      result.ok.m_max = less ? s.l_max : s.r_max;
      result.fail.m_min = less ? s.r_min : s.l_min;
      result.fail.m_max = less ? s.r_max : s.l_max;
      break;
    case 'a':
      s = split_range(p.a_min, p.a_max, val, less);
      result.ok.a_min = less ? s.l_min : s.r_min;
      result.ok.a_max = less ? s.l_max : s.r_max;
      result.fail.a_min = less ? s.r_min : s.l_min;
      result.fail.a_max = less ? s.r_max : s.l_max;
      break;
    case 's':
      s = split_range(p.s_min, p.s_max, val, less);
      result.ok.s_min = less ? s.l_min : s.r_min;
      result.ok.s_max = less ? s.l_max : s.r_max;
      result.fail.s_min = less ? s.r_min : s.l_min;
      result.fail.s_max = less ? s.r_max : s.l_max;
      break;
  }

  return result;
}

long long check(PartRange &pr, unordered_map<string, Workflow> &workflows,
                string &next) {
  if (next == "R") {
    return 0;
  }
  if (next == "A" && pr.valid()) {
    long long val = (pr.a_max - pr.a_min + 1) * (pr.x_max - pr.x_min + 1) *
                    (pr.m_max - pr.m_min + 1) * (pr.s_max - pr.s_min + 1);
    // pr.print();
    return val;
  }
  long long ans = 0;

  auto p = pr;
  for (auto &r : workflows[next].rules) {
    NewRanges range = split(p, r);
    if (range.ok.valid()) {
      ans += check(range.ok, workflows, r.next);
    }
    if (range.fail.valid()) {
      p = range.fail;
    } else {
      break;
    }
  }
  return ans;
}

std::string y2023::solve_19a(const std::vector<std::string> &input) {
  long long ans = 0;
  unordered_map<string, Workflow> workflows;
  vector<Part> parts;
  bool parse_parts = false;
  for (int i = 0; i < input.size(); ++i) {
    string s = input[i];
    if (s.size() == 0) {
      parse_parts = true;
      continue;
    }
    if (!parse_parts) {
      Workflow w;
      int pos = s.find('{');
      string name = s.substr(0, pos);
      string rules = s.substr(pos + 1, s.size() - pos - 2);
      auto spl = split(rules);

      regex reg(R"(([xmas])([<>])([0-9]+):([a-zAR]+))");
      smatch m;
      for (const auto &l : spl) {
        Rule r;
        if (regex_match(l, m, reg)) {
          r.type = m[1].str()[0];
          r.less = (m[2].str()[0] == '<');
          r.val = stoi(m[3].str());
          r.next = m[4].str();
        } else {
          r.type = 'o';
          r.next = l;
        }
        w.rules.push_back(r);
      }
      workflows[name] = w;
    } else {
      auto nums = ints(input[i]);
      Part p;
      p.x = nums[0];
      p.m = nums[1];
      p.a = nums[2];
      p.s = nums[3];
      parts.push_back(p);
    }
  }

  for (const auto &p : parts) {
    string name = "in";
    while (name != "R" && name != "A") {
      name = workflows[name].next(p);
    }
    if (name == "A") {
      ans += p.x + p.m + p.a + p.s;
    }
  }
  return to_string(ans);
}

std::string y2023::solve_19b(const std::vector<std::string> &input) {
  long long ans = 0;
  unordered_map<string, Workflow> workflows;
  for (int i = 0; i < input.size(); ++i) {
    string s = input[i];
    if (s.size() == 0) {
      break;
    }
    Workflow w;
    int pos = s.find('{');
    string name = s.substr(0, pos);
    string rules = s.substr(pos + 1, s.size() - pos - 2);
    auto spl = split(rules);

    regex reg(R"(([xmas])([<>])([0-9]+):([a-zAR]+))");
    smatch m;
    for (const auto &l : spl) {
      Rule r;
      if (regex_match(l, m, reg)) {
        r.type = m[1].str()[0];
        r.less = (m[2].str()[0] == '<');
        r.val = stoi(m[3].str());
        r.next = m[4].str();
      } else {
        r.type = 'o';
        r.next = l;
      }
      w.rules.push_back(r);
    }
    workflows[name] = w;
  }

  PartRange pr{1, 4000, 1, 4000, 1, 4000, 1, 4000};
  string start = "in";
  return to_string(check(pr, workflows, start));
}