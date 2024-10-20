/** @file load_balancer.h
 * @brief Header file for the LoadBalancer class.
 * 
 * This file contains the definition of the LoadBalancer class, which is responsible for managing the requests and servers in the system.
 * The LoadBalancer class assigns requests to servers, blocks requests from certain IP ranges, and dynamically allocates servers based on the demand.
 */
#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include "common.h"
#include "request.h"
#include "web_server.h"
#include "ip_range.h"
#include <queue>
#include <vector>

// CONFIG
/**
 * @brief Multiplier for determining when to add a new server.
 * 
 * This constant is used to decide when the load balancer should add a new server based on the current number of requests.
 */
constexpr int SERVERS_MULT_LOW = 2;
/**
 * @brief Multiplier for determining when to remove a server.
 * 
 * This constant is used to decide when the load balancer should remove a server based on the current number of requests.
 */
constexpr int SERVERS_MULT_HIGH = 5;

/**
 * @struct Stats
 * @brief Structure to hold statistics for the load balancer.
 * 
 * This structure contains counters for tracking the number of requests
 * that have been blocked and the number of requests that have been completed.
 */
struct Stats {
    /**
     * @brief Number of requests that have been blocked.
     */
    uint32_t requestsBlocked;
    /**
     * @brief Number of requests that have been completed.
     */
    uint32_t requestsCompleted;
};

class LoadBalancer {
private:
    /**
     * @brief The current time in the load balancer system.
     */
    uint64_t time;
    
    /**
     * @brief Queue to hold incoming requests.
     */
    queue<Request*> requests;
    
    /**
     * @brief Vector to hold the active web servers.
     */
    vector<WebServer*> servers;
    
    /**
     * @brief Maximum number of servers allowed.
     */
    uint32_t maxServers;
    
    /**
     * @brief IP range that is blocked from making requests.
     */
    IPRange blocked;
    
    /**
     * @brief Log information to pass to WebServer.
     */
    LogInfo logInfo;
    
    /**
     * @brief Pointer to the statistics structure.
     */
    Stats* stats;

public:
    /**
     * @brief Constructor for LoadBalancer.
     * 
     * @param maxServers Maximum number of servers allowed.
     * @param maxTimeDigits Maximum number of digits for the time.
     * @param blocked IP range that is blocked from making requests.
     * @param stats Pointer to the statistics structure.
     */
    LoadBalancer(uint32_t maxServers, uint32_t maxTimeDigits, IPRange blocked, Stats* stats);
    
    /**
     * @brief Destructor for LoadBalancer.
     */
    ~LoadBalancer();
    
    /**
     * @brief Adds a request to the load balancer.
     * 
     * @param request Pointer to the request to be added.
     */
    void addRequest(Request* request);
    
    /**
     * @brief Returns the current time in the load balancer system.
     * 
     * @return Current time.
     */
    uint64_t clock();
    
    /**
     * @brief Returns the size of the request queue.
     * 
     * @return Size of the request queue.
     */
    size_t queueSize();
};

#endif // LOAD_BALANCER_H
