#include "common.h"
#include "load_balancer.h"

// Prints clock cycles (including no-op ones) on right of screen
// #define DEBUG

int main() {
    puts("\n  \e[38;5;46;1;7m  Project 3 - Load Balancer  \e[27m\n        \e[96mBy Gopal Othayoth\n          \e[23;2;3mCSCE 412 500\e[m\n");

    srand(time(nullptr));

    uint64_t timeToRun;
    uint32_t maxServers;
    fputs("Enter the time to run (in clock cycles): \e[38;5;220m", stdout);
    cin >> timeToRun;
    fputs("\e[mEnter the number of servers: \e[38;5;220m", stdout);
    cin >> maxServers;
    fputs("\e[m", stdout);

    LoadBalancer lb{maxServers, static_cast<uint32_t>(to_string(timeToRun).length())};

    for (uint32_t i = 0; i < maxServers * 100; ++i) {
        lb.addRequest(new Request{});
    }

    printf("Starting request queue size: \e[96m%llu\e[m\n", lb.queueSize());

    for (uint64_t time = 0; time <= timeToRun; time = lb.clock()) {
        if (time % 50 == 0) {
            int numRequests = randInt(1, 5);
            for (int i = 0; i < numRequests; ++i)
                lb.addRequest(new Request{});
        }

        #ifdef DEBUG
        int numDigits = to_string(timeToRun).length();
        printf("\e[999C\e[%dD\e[2m%*llu\e[m\e[999D", numDigits - 1, numDigits, time);
        #endif
    }

    printf("Ending request queue size: \e[96m%llu\e[m\n", lb.queueSize());

    return 0;
}
