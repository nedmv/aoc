#include "../2020.hpp"
using namespace std;

enum Operation { ACC, JMP, NOP };
class Instruction {
 public:
  ~Instruction(){};
  Instruction(const string &input, int &acc) : wasExecuted{false}, acc{acc} {
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
      acc += _num;
    }
    wasExecuted = true;
    return next;
  }
  bool reverseOp() {
    if (_op == NOP) {
      _op = JMP;
      return true;
    }
    if (_op == JMP) {
      _op = NOP;
      return true;
    }
    return false;
  }
  bool wasExecuted;
  int &acc;

 private:
  Operation _op;
  int _num;
};

static vector<Instruction> readProgram(const vector<string> &input, int &acc) {
  vector<Instruction> instructions;
  for (size_t i = 0; i < input.size(); i++) {
    Instruction cmd(input[i], acc);
    instructions.push_back(cmd);
  }
  return instructions;
}

/**
 * @brief Run program.

 *
 * @param instructions given instructions set
 * @return true if terminates normally, false otherwise
 */
bool runProgram(vector<Instruction> &instructions) {
  instructions[0].acc = 0;
  int num = 0;
  size_t size = instructions.size();
  while ((num >= 0) && (num < size) && (!instructions[num].wasExecuted)) {
    num += instructions[num].execute();
  }
  if (num == size) return true;
  return false;
}

std::string y2020::solve_08a(const std::vector<std::string> &input) {
  int acc = 0;
  vector<Instruction> instructions = readProgram(const_cast<std::vector<std::string>&>(input), acc);
  runProgram(instructions);
  return to_string(acc);
}

std::string y2020::solve_08b(const std::vector<std::string> &input) {
  int acc = 0;
  vector<Instruction> instructions = readProgram(const_cast<std::vector<std::string>&>(input), acc);
  size_t size = instructions.size();

  for (size_t i = 0; i < size; i++) {
    if (instructions[i].reverseOp()) {
      if (runProgram(instructions)) return to_string(acc);
      instructions[i].reverseOp();
      for (size_t j = 0; j < size; j++) {
        instructions[j].wasExecuted = false;
      }
    }
  }
  return ERROR_STRING;
}