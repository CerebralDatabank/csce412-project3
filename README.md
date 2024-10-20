# Load Balancer (CSCE 412 Project 3) Documentation

# Load Balancer Simulation

This is a simulated load balancer that dynamically manages servers to handle incoming requests. The load balancer uses a round-robin algorithm to distribute requests to servers, adding and removing servers as needed.

## Setup

1. Ensure you have `g++` installed.
2. Open a terminal in the repo directory.
3. Run `make`.
4. Run the program according to your platform:
   - Linux: `./project3`
   - Windows: `.\project3`
5. Follow the on-screen instructions.
6. Optionally, run `make clean` to remove the compiled program.

## Information

- Requests are assigned using a round-robin algorithm.
- Servers are added and removed based on the number of requests in the queue.
- The load balancer has an IP range blocker to prevent certain IPs from accessing the server.
- The program's main configuration is via user input, and additional configuration can be done in the source code.
  - Config variables are marked with `// CONFIG` in the source code. See the documentation for more information.
