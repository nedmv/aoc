#pragma once
#include <cstdio>
#include <vector>
#include <string>

/**
 * @brief Pointer to eligible Task::solve() method.
 * 
 */
typedef const std::string (*solution_t)(std::vector<std::string>);

/**
 * @brief Puzzle year (string)
 * Used to determine relative path to puzzle files.
 * 
 */
#define YEAR "2020"

/**
 * @brief Filename of puzzle input. 
 * Relative path to file will be YEAR/<day>/INPUT
 */
#define INPUT "input"

/**
 * @brief File extension for right answers.
 * Relative path to file will be YEAR/<day>/<Task::_id>.<chosen_ext>
 *
 */
#define RIGHT_ANSWER_EXT ".right"

/**
 * @brief File extension for wrong answers.
 * Relative path to file will be YEAR/<day>/<Task::_id>.<chosen_ext>
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
  Task(){};

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
  Task(std::string id, solution_t solver);

  /**
   * @brief Destroy the Task object
   * 
   */
  ~Task(){};

  /**
   * @brief Execute given solver and check result.
   * 
   * @param id puzzle id. String with length = 3. 
   * Includes day and part id.
   * Day must be two digits (from "01" to "25").
   * Part id must be 'a' for first part and 'b' for second.
   * Examples: "05b", "23a". 
   * @param solver Pointer to chosen solve() method.
   * @return const std::string Execution result.
   */
  const std::string execute(std::string id, solution_t solver);

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
   * @brief Benchmark chosen solution.
   *
   * @return int64_t
   */
   int64_t benchmark();

  /**
   * @brief Get task id.
   *
   * @return const string Task day
   */
  const std::string getId();

  /**
   * @brief Get task part id.
   *
   * @return const char
   * 'a' for part one, 'b' for part two.
   */
  const char getPartId();

  /**
   * @brief Prepend filename with relative path to puzzle dir.
   * 
   * @param filename name of file
   * @return const string relative path
   */
  inline const std::string puzzleDirPath(const std::string filename) {
    return std::string(YEAR) + "/" + getId() + "/" + filename;
  }

  inline const std::string inputPath() {
    return puzzleDirPath(INPUT);
  }

  inline const std::string rightAnswerPath(){
    return puzzleDirPath(_id + RIGHT_ANSWER_EXT);
  }

  inline const std::string wrongAnswerPath(){
    return puzzleDirPath(_id + WRONG_ANSWER_EXT);
  }


 private:
  /**
   * @brief Set task id.
   * This setter is intentionally private,
   * as id should be set only once for class instance.
   *
   * @param id std::string (length must be 3).
   */
  inline void _setId(const std::string id);

  //TODO: consider using a struct for id.
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

  /**
   * @brief Time of execution.
   *
   */
  int64_t _time;
};