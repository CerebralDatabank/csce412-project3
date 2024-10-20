#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <iostream>

using namespace std;

typedef string IP;

inline int randInt(int min, int max) {
    return min + rand() % (max + 1 - min);
}

#endif // COMMON_H
