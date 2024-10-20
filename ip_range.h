#ifndef IP_RANGE_H
#define IP_RANGE_H

#include <string>
#include "common.h"

class IPRange {
private:
    uint32_t min;
    uint32_t max;
public:
    static uint32_t toNum(IP ip);
public:
    IPRange(IP IPmin, IP IPmax);
    bool test(IP ip);
};

#endif // IP_RANGE_H