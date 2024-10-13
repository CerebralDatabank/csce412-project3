#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "common.h"

class Request {
public:
    string ipIn;
    string ipOut;
    uint64_t requiredTime;

    Request();
    Request(string ipIn, string ipOut, uint64_t requiredTime);
    static string randIp();
};

#endif // REQUEST_H
