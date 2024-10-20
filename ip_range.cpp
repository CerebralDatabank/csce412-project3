#include "ip_range.h"
#include "common.h"

uint32_t IPRange::toNum(IP ip) {
    uint32_t num = 0;
    size_t pos = 0;
    int shift = 24; // Start with the highest byte

    while ((pos = ip.find('.')) != std::string::npos) {
        num += std::stoi(ip.substr(0, pos)) << shift;
        ip.erase(0, pos + 1);
        shift -= 8; // Move to the next byte
    }
    num += std::stoi(ip) << shift; // Add the last byte

    return num;
}

IPRange::IPRange(IP IPmin, IP IPmax) : min{toNum(IPmin)}, max{toNum(IPmax)} {}

bool IPRange::test(IP ip) {
    return min <= toNum(ip) && toNum(ip) <= max;
}
