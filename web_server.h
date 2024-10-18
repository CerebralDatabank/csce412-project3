#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "common.h"
#include "request.h"

class WebServer {
private:
    Request* request;
    uint64_t timeWhenFree;
public:
    uint32_t id;

    WebServer(uint32_t id);
    void takeRequest(Request* req, uint64_t time);
    bool isFree(uint64_t time);
};

#endif // WEB_SERVER_H
