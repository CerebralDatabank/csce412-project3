#include "load_balancer.h"

LoadBalancer::LoadBalancer(uint32_t maxServers, uint32_t maxTimeDigits) :
    time{0}, requests{}, servers{}, maxServers{maxServers}
{
    logInfo = LogInfo{
        maxTimeDigits,
        static_cast<uint32_t>(to_string(maxServers).length()),
        static_cast<uint32_t>(to_string(REQ_SIZE_MAX).length())
    };
    for (uint32_t i = 1; i <= maxServers; ++i)
        servers.push_back(new WebServer{i, logInfo});
}

LoadBalancer::~LoadBalancer() {
    for (; !requests.empty(); delete requests.front(), requests.pop());
    for (WebServer* server : servers) delete server;
}

void LoadBalancer::addRequest(Request* request) {
    requests.push(request);
}

uint64_t LoadBalancer::clock() {
    for (WebServer* server : servers) {
        if (requests.empty()) goto end;
        if (!server->isFree(time)) continue;
        Request* request = requests.front();
        requests.pop();
        server->takeRequest(request, time);
    }
    end:
    return ++time;
}

size_t LoadBalancer::queueSize() {
    return requests.size();
}
