/** @file common.h
 * @brief A common header file for the project.
 */
#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

// using namespace std;
using std::cin, std::string, std::to_string, std::queue, std::vector;

/**
 * @typedef IP
 * @brief A type alias for the standard string class, representing an IP address.
 */
typedef string IP;

/**
 * @brief Generates a random integer within a specified range.
 * 
 * This function returns a random integer between the given minimum and maximum values, inclusive.
 * 
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return A random integer between min and max, inclusive.
 */
inline int randInt(int min, int max) {
    return min + rand() % (max + 1 - min);
}

#endif // COMMON_H
