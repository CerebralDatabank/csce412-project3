#include "common.h"
#include "load_balancer.h"
#include "ip_range.h"

// Prints clock cycles (including no-op ones) on right of screen
// #define DEBUG

// Add new request every NEW_REQ_INTERVAL cycles
#define NEW_REQ_INTERVAL 50
#define NEW_REQ_AMT_MIN 1
#define NEW_REQ_AMT_MAX 5

int main() {
    puts("\n  \e[38;5;46;1;7m  Project 3 - Load Balancer  \e[27m\n        \e[96mBy Gopal Othayoth\n          \e[23;2;3mCSCE 412 500\e[m\n");

    srand(time(nullptr));

    uint64_t timeToRun;
    uint32_t maxServers;
    IP blockRangeMin;
    IP blockRangeMax;

    fputs("Enter the time to run (in clock cycles): \e[38;5;220m", stdout);
    cin >> timeToRun;
    fputs("\e[mEnter the number of servers: \e[38;5;220m", stdout);
    cin >> maxServers;

    puts("\e[mIP Range to block (leave empty for default):");

    cin.ignore();
    fputs("\n\e[2m- Upper bound (default 200.10.0.0):\e[1F\e[m- Lower bound (default 192.168.0.1): \e[38;5;220m", stdout);
    getline(cin, blockRangeMin);
    if (blockRangeMin.empty()) blockRangeMin = "192.168.0.1";

    fputs("\e[m- Upper bound (default 200.10.0.0): \e[38;5;220m", stdout);
    getline(cin, blockRangeMax);
    if (blockRangeMax.empty()) blockRangeMax = "192.168.0.255";
    fputs("\e[m", stdout);

    LoadBalancer lb{
        maxServers,
        static_cast<uint32_t>(to_string(timeToRun).length()),
        IPRange{blockRangeMin, blockRangeMax}
    };

    const uint64_t startQSize = maxServers * 100;
    for (uint32_t i = 0; i < startQSize; ++i) {
        lb.addRequest(new Request{});
    }

    printf("Starting request queue size: \e[96m%llu\e[m\n", lb.queueSize());

    for (uint64_t time = 0; time <= timeToRun; time = lb.clock()) {
        if (time % NEW_REQ_INTERVAL == 0) {
            int numRequests = randInt(NEW_REQ_AMT_MIN, NEW_REQ_AMT_MAX);
            for (int i = 0; i < numRequests; ++i)
                lb.addRequest(new Request{});
        }

        #ifdef DEBUG
        int numDigits = to_string(timeToRun).length();
        printf("\e[999C\e[%dD\e[2m%*llu\e[m\e[999D", numDigits - 1, numDigits, time);
        #endif
    }

    printf("Starting request queue size: \e[96m%llu\e[m\n", startQSize);
    printf("Ending request queue size:   \e[96m%llu\e[m\n", lb.queueSize());

    return 0;
}
