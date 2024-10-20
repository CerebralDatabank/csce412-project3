/** @file web_server.h
 * @brief Header file for the WebServer class.
 * 
 * This file contains the definition of the WebServer class, which represents a web server that can process requests.
 * The class includes methods for taking a request and checking if the server is free.
 */
#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "common.h"
#include "request.h"

/**
 * @struct LogInfo
 * @brief Holds configuration for logging information.
 * 
 * This structure contains the maximum number of digits for various logging parameters.
 * It is used to print numbers with padding to align columns in the log output.
 */
struct LogInfo {
    /**
     * @var LogInfo::maxTimeDigits
     * @brief Maximum number of digits for the time field in logs.
     */
    uint32_t maxTimeDigits;
    /**
     * @var LogInfo::maxIdDigits
     * @brief Maximum number of digits for the ID field in logs.
     */
    uint32_t maxIdDigits;
    /**
     * @var LogInfo::maxReqSizeDigits
     * @brief Maximum number of digits for the request size field in logs.
     */
    uint32_t maxReqSizeDigits;
};

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

/**
 * @class WebServer
 * @brief Represents a web server that handles requests and logs information.
 * 
 * The WebServer class is responsible for managing incoming requests, 
 * keeping track of when it will be free to handle the next request, 
 * and logging relevant information.
 */
class WebServer {
private:
    /**
     * @brief Pointer to the current request being handled by the server.
     */
    Request* request;
    /**
     * @brief The time when the server will be free to handle the next request.
     */
    uint64_t timeWhenFree;
    /**
     * @brief Information used for logging purposes.
     */
    LogInfo logInfo; // for logging
    /**
     * @brief Pointer to the statistics structure.
     */
    Stats* stats;
public:
    /**
     * @brief Unique identifier for the web server.
     */
    uint32_t id;

    /**
     * @brief Constructs a WebServer object with a given ID, logging information, and statistics.
     * 
     * @param id The unique identifier for the web server.
     * @param logInfo The logging information to be used by the server.
     * @param stats Pointer to the statistics structure.
     */
    WebServer(uint32_t id, LogInfo logInfo, Stats* stats);
    /**
     * @brief Assigns a request to the server and sets the time when the server will be free.
     * 
     * @param req Pointer to the request to be handled.
     * @param time The time when the server will be free after handling the request.
     */
    void takeRequest(Request* req, uint64_t time);
    /**
     * @brief Checks if the server is free at a given time.
     * 
     * @param time The time to check the server's availability.
     * @return true if the server is free at the given time, false otherwise.
     */
    bool isFree(uint64_t time);
};

#endif // WEB_SERVER_H
