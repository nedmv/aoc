// Puzzle is available at https://adventofcode.com/2020/day/4
// Keywords: regex
#include "../2020.hpp"
#include "../../../src/utils.hpp"
using namespace std;

std::string y2020::solve_04a(const std::vector<std::string> &input) {
  string data = string();
  size_t fields;
  size_t valid_passports = 0;

  for (int i = 0; i < input.size(); i++) {
    if (!(input[i].empty())) {
      data.append(input[i]);
    } else {
      fields = count(data.begin(), data.end(), ':');
      if (fields > 8) return ERROR_STRING;
      if (fields == 8) valid_passports++;
      if ((fields == 7) && (!regex_search(data, regex("cid")))) {
        valid_passports++;
      }
      data.clear();
    }
  }

  return to_string(valid_passports);
}

// input should end with empty string for correct processing
std::string y2020::solve_04b(const std::vector<std::string> &input) {
  string data = string();
  size_t valid_passports = 0;
  smatch match;
  for (int i = 0; i < input.size(); i++) {
    if (input[i].empty()) {
      if (!(regex_search(data, match, regex(R"(byr:([0-9]+)[ $])"))) ||
          (ToInt(match[1]) < 1920) || (ToInt(match[1]) > 2002)) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, match, regex(R"(iyr:([0-9]+)[ $])"))) ||
          (ToInt(match[1]) < 2010) || (ToInt(match[1]) > 2020)) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, match, regex(R"(eyr:([0-9]+)[ $])"))) ||
          (ToInt(match[1]) < 2020) || (ToInt(match[1]) > 2030)) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, match, regex(R"(hgt:([0-9]+)(cm|in)[ $])"))) ||
          (ToInt(match[1]) < 59) || (ToInt(match[1]) > 193) ||
          ((ToInt(match[1]) < 150) && (match[2].str() == "cm")) ||
          ((ToInt(match[1]) > 76) && (match[2].str() == "in"))) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, regex(R"(hcl:#[0-9a-f]{6}[ $])")))) {
        data.clear();
        continue;
      }
      if (!(regex_search(data,
                         regex(R"(ecl:(amb|blu|brn|gry|grn|hzl|oth)[ $])")))) {
        data.clear();
        continue;
      }
      if (!(regex_search(data, regex(R"(pid:[0-9]{9}[ $])")))) {
        data.clear();
        continue;
      }
      data.clear();
      valid_passports++;
    } else {
      data.append(input[i]);
      data.append(" ");
    }
  }
  return to_string(valid_passports);
}
