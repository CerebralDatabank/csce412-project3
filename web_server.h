#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "common.h"
#include "request.h"

struct LogInfo {
    uint32_t maxTimeDigits;
    uint32_t maxIdDigits;
    uint32_t maxReqSizeDigits;
};

class WebServer {
private:
    Request* request;
    uint64_t timeWhenFree;
    LogInfo logInfo; // for logging
public:
    uint32_t id;

    WebServer(uint32_t id, LogInfo logInfo);
    void takeRequest(Request* req, uint64_t time);
    bool isFree(uint64_t time);
};

#endif // WEB_SERVER_H
