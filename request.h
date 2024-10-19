#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "common.h"

#define REQ_SIZE_MIN 5
#define REQ_SIZE_MAX 20

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
