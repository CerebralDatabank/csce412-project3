#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include "common.h"
#include "request.h"
#include "web_server.h"
#include "ip_range.h"
#include <queue>
#include <vector>

struct Stats {
    uint32_t requestsBlocked;
    uint32_t requestsCompleted;
};

class LoadBalancer {
private:
    uint64_t time;
    queue<Request*> requests;
    vector<WebServer*> servers;
    uint32_t maxServers;
    IPRange blocked;
    LogInfo logInfo; // to pass to WebServer
    Stats* stats;
public:
    LoadBalancer(uint32_t maxServers, uint32_t maxTimeDigits, IPRange blocked, Stats* stats);
    ~LoadBalancer();
    void addRequest(Request* request);
    uint64_t clock();
    size_t queueSize();
};

#endif // LOAD_BALANCER_H
