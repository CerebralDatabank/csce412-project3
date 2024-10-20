#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "common.h"

#define REQ_SIZE_MIN 5
#define REQ_SIZE_MAX 20

class Request {
public:
    IP ipIn;
    IP ipOut;
    uint64_t requiredTime;

    Request();
    Request(IP ipIn, IP ipOut, uint64_t requiredTime);
    static IP randIp();
};

#endif // REQUEST_H
