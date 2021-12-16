#pragma once
#include <vector>
#include <string>
#include <regex>
#include <cmath>

/**
 * @brief Create vector of numbers from string.
 * 
 * @param line String of comma-delimited integers.
 * @return vector<int> Vector of integers.
 */
std::vector<int> parseLineOfNumbers(const std::string &line);

/**
 * @brief Convert submatch value to integer.
 * 
 * @param m Chosen submatch.
 * @return int Value.
 */
inline int ToInt(std::ssub_match m) { return std::stoi(m.str()); }

/**
 * @brief Wrap std::stoi for use in std::transform.
 * 
 * @param str Input string
 * @return int
 */
inline int stoiWrap(const std::string &str) { return std::stoi(str); }

/**
 * @brief Convert representation of number as binary string to unsigned integer.
 * 
 * @param binary Input string (should contain only symbols '0' and '1').
 * @return Result (size_t)
 */
size_t binaryStringToDecimal(const std::string &binary);