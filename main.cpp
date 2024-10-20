#include "common.h"
#include "load_balancer.h"
#include "ip_range.h"
#ifdef _WIN32
#include <windows.h>
#endif

// Prints clock cycles (including no-op ones) on right of screen
// #define DEBUG

// CONFIG
// Add new request every NEW_REQ_INTERVAL cycles
constexpr int NEW_REQ_INTERVAL = 50;
constexpr int NEW_REQ_AMT_MIN = 1;
constexpr int NEW_REQ_AMT_MAX = 5;

void enableAnsiSupport() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    DWORD mode;
    if (GetConsoleMode(hConsole, &mode))
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
}

int main() {
    enableAnsiSupport();
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
    fputs("\n\e[2m| Upper bound (default 200.10.0.0):\e[1F\e[m| Lower bound (default 192.168.0.1): \e[38;5;220m", stdout);
    getline(cin, blockRangeMin);
    if (blockRangeMin.empty()) blockRangeMin = "192.168.0.1";

    fputs("\e[m| Upper bound (default 200.10.0.0): \e[38;5;220m", stdout);
    getline(cin, blockRangeMax);
    if (blockRangeMax.empty()) blockRangeMax = "200.10.0.0";

    // CONFIG
    const uint64_t startQSize = maxServers * 100;
    puts("\e[m\nOther config details (change via statements marked \"CONFIG\" in code):");
    printf("| Starting request queue size: \e[38;5;220m%" PRIu64 "\e[m\n", startQSize);
    printf("| New request(s) every \e[38;5;220m%u\e[m cycles\n", NEW_REQ_INTERVAL);
    printf("| New request amount range: [\e[38;5;220m%u\e[m, \e[38;5;220m%u\e[m]\n", NEW_REQ_AMT_MIN, NEW_REQ_AMT_MAX);
    printf("| New request required time range: [\e[38;5;220m%u\e[m, \e[38;5;220m%u\e[m]\n\n", REQ_SIZE_MIN, REQ_SIZE_MAX);

    fputs("\e[m\nPress \e[92m[Enter]\e[m to start...", stdout);
    cin.get();
    fputs("\e[m\n", stdout);

    LoadBalancer lb{
        maxServers,
        static_cast<uint32_t>(to_string(timeToRun).length()),
        IPRange{blockRangeMin, blockRangeMax}
    };

    for (uint32_t i = 0; i < startQSize; ++i) {
        lb.addRequest(new Request{});
    }

    for (uint64_t time = 0; time <= timeToRun; time = lb.clock()) {
        if (time % NEW_REQ_INTERVAL == 0) {
            int numRequests = randInt(NEW_REQ_AMT_MIN, NEW_REQ_AMT_MAX);
            for (int i = 0; i < numRequests; ++i)
                lb.addRequest(new Request{});
        }

        #ifdef DEBUG
        int numDigits = to_string(timeToRun).length();
        printf("\e[999C\e[%dD\e[2m%*" PRIu64 "\e[m\e[999D", numDigits - 1, numDigits, time);
        #endif
    }

    puts("\nSummary:");
    printf("| Starting request queue size: \e[96m%" PRIu64 "\e[m\n", startQSize);
    printf("| Ending request queue size:   \e[96m%" PRIu64 "\e[m\n\n", lb.queueSize());

    return 0;
}
