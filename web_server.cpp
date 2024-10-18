#include "web_server.h"

WebServer::WebServer(uint32_t id) : request{nullptr}, timeWhenFree{0}, id{id} {}

void WebServer::takeRequest(Request* req, uint64_t time) {
    if (request != nullptr) {
        printf(
            "\e[96m[Server %u]\e[m Request of size %llu (%s -> %s) completed at time %llu\n",
            id, request->requiredTime, request->ipIn.c_str(), request->ipOut.c_str(), time
        );
        delete request;
    }
    request = req;
    timeWhenFree = time + req->requiredTime;
}

bool WebServer::isFree(uint64_t time) {
    return time >= timeWhenFree;
}
