#include "../2020.hpp"
using namespace std;

enum Operation { ACC, JMP, NOP };
class Instruction {
 public:
  ~Instruction(){};
  Instruction(const string input, int &acc) : wasExecuted{false}, _acc{acc} {
    smatch match;
    regex_match(input, match, regex(R"((acc|jmp|nop) ([+-][0-9]+))"));
    if (match[1].str() == "acc") {
      _op = ACC;
    } else if (match[1].str() == "jmp") {
      _op = JMP;
    } else {
      _op = NOP;
    }
    _num = stoi(match[2].str());
  }
  int execute() {
    int next = 1;
    if (_op == JMP) {
      next = _num;
    }
    if (_op == ACC) {
      _acc += _num;
    }
    wasExecuted = true;
    return next;
  }
  bool wasExecuted;

 private:
  Operation _op;
  int _num;
  int &_acc;
};

const std::string y2020::solve_08a(std::vector<std::string> input) {
  vector<Instruction> instructions;
  int acc = 0;
  for (size_t i = 0; i < input.size(); i++) {
    Instruction cmd(input[i], acc);
    instructions.push_back(cmd);
  }
  int num = 0;
  while (!instructions[num].wasExecuted) {
    num += instructions[num].execute();
  }
  return to_string(acc);
}