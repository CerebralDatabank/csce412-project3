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
