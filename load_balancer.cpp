#include "load_balancer.h"

// CONFIG
// Multipliers for dynamic server allocation
#define SERVERS_MULT_LOW 2
#define SERVERS_MULT_HIGH 5

LoadBalancer::LoadBalancer(uint32_t maxServers, uint32_t maxTimeDigits, IPRange blocked, Stats* stats) :
    time{0}, requests{}, servers{}, maxServers{maxServers}, blocked{blocked}, stats{stats}
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
    // Block requests in blocked IP ranges
    while (!requests.empty() && blocked.test(requests.front()->ipIn)) {
        Request* request = requests.front();
        requests.pop();
        printf(
            "\e[2m[%*" PRIu64 "] \e[22;38;5;190m[System %*s]\e[m Request of size \e[38;5;40m%*" PRIu64 "\e[m (\e[38;5;208m%15s\e[m \e[91m-X \e[38;5;207m%-15s\e[m) \e[91mblocked\e[m\n",
            logInfo.maxTimeDigits, time, logInfo.maxIdDigits, "", logInfo.maxReqSizeDigits, request->requiredTime, request->ipIn.c_str(), request->ipOut.c_str()
        );
        delete request;
    }

    // Dynamic server allocation
    if (requests.size() > (servers.size() * SERVERS_MULT_LOW) && servers.size() < maxServers) {
        uint32_t newId = servers.size() + 1;
        servers.push_back(new WebServer{static_cast<uint32_t>(newId), logInfo});
        printf(
            "\e[2m[%*" PRIu64 "] \e[22;96m[Server \e[38;5;220m%*u\e[96m] \e[92mnow online due to higher demand\e[m\n",
            logInfo.maxTimeDigits, time, logInfo.maxIdDigits, newId
        );
    }
    else if (requests.size() < (servers.size() * SERVERS_MULT_HIGH) && servers.size() > 1) {
        uint32_t oldId = servers.size();
        delete servers.back();
        servers.pop_back();
        printf(
            "\e[2m[%*" PRIu64 "] \e[22;96m[Server \e[38;5;220m%*u\e[96m] \e[91mnow offline due to lower demand\e[m\n",
            logInfo.maxTimeDigits, time, logInfo.maxIdDigits, oldId
        );
    }

    // Assign requests to servers
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
