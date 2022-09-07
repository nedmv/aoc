#include "Task.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>

using namespace std;
using namespace std::chrono;

Task::Task(const string &id, solution_t solver) {
  _setId(id);
  this->solve = solver;
}

string Task::execute(const string &id, solution_t solver) {
  _setId(id);
  this->solve = solver;
  _input.clear();
  _result.clear();

  cout << "\nTask " << _year << "-" << _id << ":" << endl;

  read_input();
  time_t time = benchmark();

  if (check()) {
    celebrate();
    cout << "Execution took " << time << " microseconds." << endl;
  } else {
    celibate();
  }
  return _result;
}

void Task::read_input() {
  string path = inputPath();
  ifstream ifs(path);
  assert(ifs.is_open());
  string line;

  while (getline(ifs, line)) {
    _input.push_back(line);
  }

  assert(_input.size() != 0);
}

void Task::celebrate() {
  cout << "Task " << _year << "-" << _id << " solved! Result = " << _result << "." << endl;

  auto answer = rightAnswerPath();
  if (!filesystem::exists(answer)) {
    auto ofs = ofstream(answer);
    ofs << _result;
  }
}

void Task::celibate() {
  cout << "Solution for task "<< _year << "-" << _id << " is incorrect." << endl;
  cout << "Try something other than " << _result << "." << endl;

  string errors = wrongAnswerPath();
  auto ofs = ofstream(errors, ofstream::app);
  ofs << _result << endl;
}

time_t Task::benchmark() {
  auto start = high_resolution_clock::now();
  _result = solve(_input);
  auto end = high_resolution_clock::now();
  time_t time = duration_cast<microseconds>(end - start).count();
  return time;
}

void Task::multirun(const std::string &id, solution_t solver, size_t n) {
  _setId(id);
  this->solve = solver;
  _input.clear();
  _result.clear();
  read_input();
  vector<time_t> bench(n, 0);

  for (size_t i = 0; i < n; i++) {
    bench[i] = benchmark();
  }

  auto results = minmax(bench.begin(), bench.end() - 1);
  time_t max = *results.first;
  time_t min = *results.second;
  // not an accurate average, but results were already rounded to microseconds
  time_t avg = accumulate(bench.begin(), bench.end(), 0) / n;

  cout << "Task " << id << " was executed " << n << " times.\n";
  cout << "Times(microseconds): average = " << avg << ", min = " << min
       << ", max = " << max << "." << endl;
}

string Task::getId() {
  assert(_id.length() == 3);
  return _id.substr(0, 2);
}

char Task::getPartId() {
  assert(_id.length() == 3);
  return _id.at(2);
}

inline void Task::_setId(const string &id) {
  assert(id.length() == 3);
  assert(id.at(2) == 'a' || id.at(2) == 'b');
  assert(id.at(0) >= '0' && id.at(0) <= '2');
  assert(id.at(1) >= '0' && id.at(1) <= '9');
  assert(id.at(0) != '2' || id.at(1) <= '5');

  _id = id;
}

// TODO: add auto check as alternative
bool Task::check() {
  const string right_path = rightAnswerPath();
  const string wrong_path = wrongAnswerPath();
  ifstream ifs;
  string answer;

  if (_result == ERROR_STRING) return false;

  if (filesystem::exists(right_path)) {
    ifs = ifstream(right_path);
    answer.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    if (_result == answer) return true;
    return false;
  }

  if (filesystem::exists(wrong_path)) {
    ifs = ifstream(wrong_path);
    while (getline(ifs, answer)) {
      if (_result == answer) return false;
    }
  }
  // manually check for answer
  cout << "Result is " << _result << ".\n";
  cout << "Please manually check it at https://adventofcode.com/";
  cout << _year << "/day/" << stoi(getId()) << "." << endl;
  cout << "Is result correct? (y/n)" << endl;

  char c;
  while (true) {
    cin.get(c);
    if (c == 'n' || c == 'N') return false;
    if (c == 'y' || c == 'Y') return true;
    cout << "Failed to recognize symbol, please type 'y' or 'n'." << endl;
  }
}

void Task::setYear(int year) {
  _year = to_string(year);
}