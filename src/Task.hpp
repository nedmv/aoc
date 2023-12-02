#pragma once
#include <cstdio>
#include <string>
#include <vector>
/**
 * @brief Pointer to eligible Task::solve() method.
 *
 */
typedef std::string (*solution_t)(const std::vector<std::string> &);

/**
 * @brief Filename of puzzle input.
 * Relative path to file will be <year>/<day>/INPUT
 */
#define DEFAULT_INPUT "input"

/**
 * @brief File extension for right answers.
 * Relative path to file will be <year>/<day>/<Task::_id>.<chosen_ext>
 *
 */
#define RIGHT_ANSWER_EXT ".right"

/**
 * @brief File extension for wrong answers.
 * Relative path to file will be <year>/<day>/<Task::_id>.<chosen_ext>
 *
 */
#define WRONG_ANSWER_EXT ".wrong"

/**
 * @brief This string is used as certainly incorrect solver output.
 *
 */
#define ERROR_STRING "ERROR"

class Task {
 public:
  /**
   * @brief Construct a new Task object
   *
   */
  Task() = default;

  /**
   * @brief Construct a new Task object with given _id and solver.
   *
   * @param id puzzle id. String with length = 3.
   * Includes day and part id.
   * Day must be two digits (from "01" to "25").
   * Part id must be 'a' for first part and 'b' for second.
   * Examples: "05b", "23a".
   * @param solver Pointer to used solve() function.
   * Function must take vector of strings as argument and return single string.
   */
  Task(const std::string &id, solution_t solver);

  /**
   * @brief Execute given solver and check result.
   *
   * @param id puzzle id. String with length = 3.
   * Includes day and part id.
   * Day must be two digits (from "01" to "25").
   * Part id must be 'a' for first part and 'b' for second.
   * Examples: "05b", "23a".
   * @param solver Pointer to chosen solve() method.
   * @return std::string Execution result.
   */
  std::string execute(const std::string &id, solution_t solver);

  /**
   * @brief Problem solution. Receives array of strings, returns result.
   *
   * @return int Result.
   */
  solution_t solve = nullptr;

  /**
   * @brief Copy contents of input file into array of strings.
   *
   */
  void read_input();

  /**
   * @brief Check acquired result.
   * @return bool True, if solution was correct.
   */
  bool check();

  /**
   * @brief Print celebration message. Called if check() was successful.
   *
   */
  void celebrate();

  /**
   * @brief Called if check() failed.
   *
   */
  void celibate();

  /**
   * @brief Measure time of executing this->solve().
   *
   * @return time_t Time (in microseconds).
   */
  time_t benchmark();

  /**
   * @brief Run task n times and gather time statistics.
   *
   * @param id Task id
   * @param solver Chosen solver
   * @param n Times to run
   */
  void multirun(const std::string &id, solution_t solver, size_t n);

  /**
   * @brief Get task id.
   *
   * @return string Task day
   */
  std::string getId() const;

  /**
   * @brief Get task part id.
   *
   * @return char
   * 'a' for part one, 'b' for part two.
   */
  char getPartId() const;

  /**
   * @brief Set puzzle year. It is used to determine relative path to puzzle files.
   * 
   * @param year 
   */
  void setYear(int year);

  /**
   * @brief Set input file. It is used to determine relative path to puzzle files.
   * 
   * @param filename Input filename, relative for puzzle folder 
   */
  void setFilename(const std::string &filename);

  /**
   * @brief Prepend filename with relative path to puzzle dir.
   *
   * @param filename name of file
   * @return string relative path
   */
  inline std::string puzzleDirPath(const std::string &filename) {
    return "puzzles/" + _year + "/" + getId() + "/" + filename;
  }

  inline std::string inputPath() {
    return puzzleDirPath(_filename);
  }

  inline std::string rightAnswerPath() {
    return puzzleDirPath(_filename + '.' + _id + RIGHT_ANSWER_EXT);
  }

  inline std::string wrongAnswerPath() {
    return puzzleDirPath(_filename + '.' + _id + WRONG_ANSWER_EXT);
  }

 private:
  /**
   * @brief Set task id.
   * This setter is intentionally private,
   * as id should be set only once for class instance.
   *
   * @param id std::string (length must be 3).
   */
  inline void _setId(const std::string &id);

  std::string _year;
  std::string _filename = DEFAULT_INPUT;

  // TODO: consider using a struct for id.
  /**
   * @brief Puzzle id.
   * First two symbols contain id of the task. Example: "01", "25".
   * Last symbol contains part id. It equals 'a' for the first part of task
   * and 'b' for the second part.
   *
   */
  std::string _id;

  /**
   * @brief Pointer to array of strings, which was acquired by read_input().
   *
   */
  std::vector<std::string> _input;

  /**
   * @brief Task result.
   *
   */
  std::string _result;
};
