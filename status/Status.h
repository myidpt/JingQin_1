/*
 * Status.h
 *
 *  Created on: Apr 10, 2013
 *      Author: yonggang
 */

#ifndef STATUS_H_
#define STATUS_H_

#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#define MAX_SENSORS     20
#define KEY_COMP_CAP    "comp_cap"
#define KEY_POWER       "power"
#define KEY_SENSOR      "sensor"
#define KEY_SENSORCOST  "sensor_cost"

using namespace std;

// This is the status for one node.
class Status {
protected:
    int id;
    bool sensors[MAX_SENSORS];
    double sensorCosts[MAX_SENSORS];
    double computeCap;
    double power;

    Status(); // A Status can only be created by the statusFactory method.
    bool parseStatusString(const string & str);
public:
    static int parseInputGetId(string & str);
    static Status * createStatus(const string & str); // Create a Status object.
    string genStatusString();
    void printInformation(); // For debugging.
    virtual ~Status();
};

#endif /* STATUS_H_ */
