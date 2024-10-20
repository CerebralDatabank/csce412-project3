/** @file web_server.cpp
 * @brief Implementation file for the WebServer class.
 * 
 * This file contains the implementation of the WebServer class, which represents a web server that can process requests.
 * The class includes methods for taking a request and checking if the server is free.
 */
#include "web_server.h"

WebServer::WebServer(uint32_t id, LogInfo logInfo) :
    request{nullptr}, timeWhenFree{0}, logInfo{logInfo}, id{id}
{}

void WebServer::takeRequest(Request* req, uint64_t time) {
    if (request != nullptr) {
        printf(
            "\e[2m[%*" PRIu64 "] \e[22;96m[Server \e[38;5;220m%*u\e[96m]\e[m Request of size \e[38;5;40m%*" PRIu64 "\e[m (\e[38;5;208m%15s\e[m -> \e[38;5;207m%-15s\e[m) completed\n",
            logInfo.maxTimeDigits, time, logInfo.maxIdDigits, id, logInfo.maxReqSizeDigits, request->requiredTime, request->ipIn.c_str(), request->ipOut.c_str()
        );
        delete request;
    }
    request = req;
    timeWhenFree = time + req->requiredTime;
}

bool WebServer::isFree(uint64_t time) {
    return time >= timeWhenFree;
}
