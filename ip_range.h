/** @file ip_range.h
 * @brief A class to represent an IP range.
 * 
 * This file contains the definition of the IPRange class, which represents a range of IP addresses.
 * The class contains a method to test if a given IP address is within the range.
 * 
 * @sa ip_range.cpp
 */
#ifndef IP_RANGE_H
#define IP_RANGE_H

#include <string>
#include "common.h"

/**
 * @class IPRange
 * @brief Represents a range of IP addresses.
 */
class IPRange {
private:
    /**
     * @brief The minimum IP address in the range.
     */
    uint32_t min;

    /**
     * @brief The maximum IP address in the range.
     */
    uint32_t max;

    /**
     * @brief Converts an IP address to a numeric representation.
     * @param ip The IP address to convert.
     * @return The numeric representation of the IP address.
     */
    static uint32_t toNum(IP ip);

public:
    /**
     * @brief Constructs an IPRange object with the specified minimum and maximum IP addresses.
     * @param IPmin The minimum IP address in the range.
     * @param IPmax The maximum IP address in the range.
     */
    IPRange(IP IPmin, IP IPmax);

    /**
     * @brief Tests if a given IP address is within the range.
     * @param ip The IP address to test.
     * @return True if the IP address is within the range, false otherwise.
     */
    bool test(IP ip);
};

#endif // IP_RANGE_H