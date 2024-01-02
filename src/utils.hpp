#pragma once
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <climits>

/**
 * @brief Create vector of strings from string.
 * 
 * @param line Input string
 * @param delim Delimiter.
 * @return vector<int> Vector of strings.
 */
std::vector<std::string> split(const std::string &line, const std::string &delim = ",");

/**
 * @brief Load input into map of characters.
 * 
 * @param input Puzzle input (array of strings)
 * @return std::vector<std::vector<char>> 2D character array
 */
std::vector<std::vector<char>> char_map(const std::vector<std::string> &input);

/**
 * @brief Print map of characters
 * 
 * @param input Map of characters
 */
void print_map(const std::vector<std::vector<char>> &m);

/**
 * @brief Load input into vector of character maps.
 * 
 * @param input Puzzle input (array of strings)
 * @return std::vector<std::vector<std::vector<char>>> Vector of 2D character vectors.
 */
std::vector<std::vector<std::vector<char>>> char_map_vec(const std::vector<std::string> &input);

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

/**
 * @brief Return sign of given value.
 * 
 * @param value Integer number.
 * @return -1 if value is negative, 1 if value is positive, 0 if val = 0.
 */
int sign(int value);

int first(const std::string &s, const int invalid = INT_MIN);

/**
 * @brief Return all ints in the string as vector
 * 
 * @param s Input string
 * @return std::vector<long long> Resulting vector
 */
std::vector<long long> ints(const std::string &s);


std::vector<long long> signed_ints(const std::string &s);