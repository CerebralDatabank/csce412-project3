#include "request.h"

string Request::randIp() {
    string ip = "";
    for (int i = 0; i < 4; i++) {
        ip += to_string(rand() % 256);
        if (i < 3) ip += '.';
    }
    return ip;
}

Request::Request() :
    ipIn{randIp()},
    ipOut{randIp()},
    requiredTime{rand() % 1000 + 1uLL}
{}

Request::Request(string ipIn, string ipOut, uint64_t requiredTime) :
    ipIn{ipIn},
    ipOut{ipOut},
    requiredTime{requiredTime}
{}
