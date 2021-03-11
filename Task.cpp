#include "Task.hpp"
#include <filesystem>
#include <cassert>
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;
using namespace std::chrono;

Task::Task(string id, solution_t solver){
  _setId(id);
  _time = 0;
  this->solve = solver;
}

const string Task::execute(string id, solution_t solver) {
  _setId(id);
  _time = 0;
  this->solve = solver;
  _input.clear();
  _result.clear();

  cout << "\nTask " << _id << ":" << endl;
  
  read_input();
  benchmark();

  if (check()) {
    celebrate();
    cout << "Execution took " << _time << " microseconds." << endl;
  } else {
    celibate();
  }
  return _result;
}

void Task::read_input() {
  string path = inputPath();
  ifstream ifs(path);
  int i = 0;
  string line;

  while (getline(ifs, line)) {
    _input.push_back(line);
  }

  assert(_input.size() != 0);
}

void Task::celebrate() {
  cout << "Task " << _id << " solved! Result = " << _result << "." << endl;

  auto answer = rightAnswerPath();
  if (!filesystem::exists(answer)) {
    auto ofs = ofstream(answer);
    ofs << _result;
  }
}

void Task::celibate() {
  cout << "Solution for task " << _id << " is incorrect." << endl;
  cout << "Try something other than " << _result << "." << endl;

  string errors = wrongAnswerPath();
  auto ofs = ofstream(errors,ofstream::app);
  ofs << _result << endl;
}

int64_t Task::benchmark() {
  auto start = high_resolution_clock::now();
  _result = solve(_input);
  auto end = high_resolution_clock::now();
  _time = duration_cast<microseconds>(end - start).count();
  return _time;
}

const string Task::getId() {
  assert(_id.length() == 3);
  return _id.substr(0, 2);
}

const char Task::getPartId() {
  assert(_id.length() == 3);
  return _id.at(2);
}

inline void Task::_setId(const string id) {
  assert(id.length() == 3);
  assert(id.at(2) == 'a' || id.at(2) == 'b');
  assert(id.at(0) >= '0' && id.at(0) <= '2');
  assert(id.at(1) >= '0' && id.at(1) <= '9');
  assert(id.at(0) != '2' || id.at(1) <= '5');

  _id = id;
}

//TODO: add auto check as alternative
bool Task::check() {
  const string right_path = rightAnswerPath();
  const string wrong_path = wrongAnswerPath();
  ifstream ifs;
  string answer;

  if (_result == ERROR_STRING) return false;

  if (filesystem::exists(right_path)) {
    ifs = ifstream(right_path);
    getline(ifs, answer);
    if (_result == answer ) return true;
    return false;
  } 

  if (filesystem::exists(wrong_path)) {
    ifs = ifstream(wrong_path);
    while (getline(ifs,answer)) {
      if (_result == answer ) return false;
    }
  }
  //manually check for answer
  cout << "Result is " << _result << ".\n";
  cout << "Please manually check it at https://adventofcode.com/";
  cout << YEAR << "/day/" << stoi(getId()) << "." << endl;
  cout << "Is result correct? (y/n)" << endl;

  char c;
  while(true) {
    cin.get(c);
    if (c == 'n' || c == 'N') return false;
    if (c == 'y' || c == 'Y') return true;
    cout << "Failed to recognize symbol, please type 'y' or 'n'." << endl;
  }
}
