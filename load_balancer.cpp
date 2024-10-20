#include "load_balancer.h"

LoadBalancer::LoadBalancer(uint32_t maxServers, uint32_t maxTimeDigits) :
    time{0}, requests{}, servers{}, maxServers{maxServers}
{
    logInfo = LogInfo{
        maxTimeDigits,
        static_cast<uint32_t>(to_string(maxServers).length()),
        static_cast<uint32_t>(to_string(REQ_SIZE_MAX).length())
    };
    servers.push_back(new WebServer{1, logInfo});
}

LoadBalancer::~LoadBalancer() {
    for (; !requests.empty(); delete requests.front(), requests.pop());
    for (WebServer* server : servers) delete server;
}

void LoadBalancer::addRequest(Request* request) {
    requests.push(request);
}

uint64_t LoadBalancer::clock() {
    if (requests.size() > (maxServers * 5) && servers.size() < maxServers) {
        uint32_t newId = servers.size() + 1;
        servers.push_back(new WebServer{static_cast<uint32_t>(newId), logInfo});
        printf(
            "\e[2m[%*llu] \e[22;96m[Server \e[38;5;220m%*u\e[96m] \e[92mnow online due to higher demand\e[m\n",
            logInfo.maxTimeDigits, time, logInfo.maxIdDigits, newId
        );
    }
    else if (requests.size() < (maxServers * 2) && servers.size() > 1) {
        uint32_t oldId = servers.size();
        delete servers.back();
        servers.pop_back();
        printf(
            "\e[2m[%*llu] \e[22;96m[Server \e[38;5;220m%*u\e[96m] \e[91mnow offline due to lower demand\e[m\n",
            logInfo.maxTimeDigits, time, logInfo.maxIdDigits, oldId
        );
    }
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
