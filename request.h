/** 
 * @file request.h
 * @brief Header file for the Request class.
 * 
 * This file contains the definition of the Request class, which represents a network request with source and destination IP addresses and a required time.
 * The class also contains a static method for generating random IP addresses.
 * 
 * @sa request.cpp
 */
#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "common.h"

// CONFIG
/**
 * @brief Minimum size for a request.
 * 
 * This constant defines the upper limit for the required time of a new random request.
 */
constexpr int REQ_SIZE_MIN = 5;
/**
 * @brief Maximum size for a request.
 * 
 * This constant defines the upper limit for the required time of a new random request.
 */
constexpr int REQ_SIZE_MAX = 20;

/**
 * @class Request
 * @brief Represents a network request with source and destination IP addresses and a required time.
 * 
 * The Request class encapsulates the details of a network request, including the source and destination
 * IP addresses and the time required to process the request.
 */
class Request {
public:
    /**
     * @var Request::ipIn
     * @brief The source IP address for the request.
     */
    IP ipIn;
    /**
     * @var Request::ipOut
     * @brief The destination IP address for the request.
     */
    IP ipOut;
    /**
     * @var Request::requiredTime
     * @brief The time required to process the request.
     */
    uint64_t requiredTime;

    /**
     * @brief Default constructor for the Request class.
     * 
     * Initializes a new instance of the Request class with default values.
     */
    Request();
    /**
     * @brief Parameterized constructor for the Request class.
     * 
     * @param ipIn The source IP address for the request.
     * @param ipOut The destination IP address for the request.
     * @param requiredTime The time required to process the request.
     * 
     * Initializes a new instance of the Request class with the specified source and destination IP addresses
     * and the required processing time.
     */
    Request(IP ipIn, IP ipOut, uint64_t requiredTime);
    /**
     * @brief Generates a random IP address.
     * 
     * @return A randomly generated IP address.
     * 
     * This static method generates and returns a random IP address.
     */
    static IP randIp();
};

#endif // REQUEST_H
