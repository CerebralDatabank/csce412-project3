/** 
 * @file request.cpp
 * @brief Implementation file for the Request class.
 * 
 * This file contains the implementation of the Request class, which represents a network request with source and destination IP addresses and a required time.
 * 
 * @sa request.h
 */
#include "request.h"

IP Request::randIp() {
    IP ip = "";
    for (int i = 0; i < 4; i++) {
        ip += to_string(randInt(0, 255));
        if (i < 3) ip += '.';
    }
    return ip;
}

Request::Request() :
    ipIn{randIp()},
    ipOut{randIp()},
    requiredTime{static_cast<uint64_t>(randInt(REQ_SIZE_MIN, REQ_SIZE_MAX))}
{}

Request::Request(IP ipIn, IP ipOut, uint64_t requiredTime) :
    ipIn{ipIn},
    ipOut{ipOut},
    requiredTime{requiredTime}
{}
