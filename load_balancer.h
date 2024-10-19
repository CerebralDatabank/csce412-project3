#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include "common.h"
#include "request.h"
#include "web_server.h"
#include <queue>
#include <vector>

class LoadBalancer {
private:
    uint64_t time;
    queue<Request*> requests;
    vector<WebServer*> servers;
    uint32_t maxServers;
    LogInfo logInfo; // to pass to WebServer
public:
    LoadBalancer(uint32_t maxServers, uint32_t maxTimeDigits);
    ~LoadBalancer();
    void addRequest(Request* request);
    uint64_t clock();
    size_t queueSize();
};

#endif // LOAD_BALANCER_H
