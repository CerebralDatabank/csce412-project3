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

typedef string IP;

inline int randInt(int min, int max) {
    return min + rand() % (max + 1 - min);
}

#endif // COMMON_H
