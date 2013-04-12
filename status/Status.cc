/*
 * Status.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: yonggang
 */

#include "Status.h"

int Status::parseInputGetId(string & str) {
    int id;
    if(sscanf(str.c_str(), "%d", &id) != 1) {
        return -1;
    }
    return id;
}

// Parse the input string.
Status * Status::createStatus(const string & str) {
    Status * status = new Status();
    if (status->parseStatusString(str)) {
        return status;
    }
    else {
        return NULL;
    }
}

Status::Status() {
    computeCap = -1;
    power = -1;
    for (int i = 0; i < MAX_SENSORS; i ++) {
        sensors[i] = false;
        sensorCosts[i] = -1;
    }
}

bool Status::parseStatusString(const string & str) {
    int start = 0;
    int end = 0;
    int colon = 0;
    string key;
    string value;
    int sensorid = 0;
    while ((colon = str.find(":", start)) != string::npos) {
        key = str.substr(start, colon - start);
        end = str.find(";", colon);
        if (end == (int)string::npos) {
            value = str.substr(colon + 1, (int)string::npos);
        }
        else {
            value = str.substr(colon + 1, end - colon - 1);
        }

        istringstream stream(value);
        if (key.compare(KEY_COMP_CAP) == 0) {
            if(!(stream >> computeCap)) {
                cerr << "Compute Capability parsing error." << endl;
                return false;
            }
        }
        else if (key.compare(KEY_POWER) == 0) {
            if(!(stream >> power)) {
                cerr << "Power parsing error." << endl;
                return false;
            }
        }
        else if (key.compare(KEY_SENSOR) == 0) {
            if(!(stream >> sensorid)) {
                cerr << "Sensor paring error." << endl;
                return false;
            }
            sensors[sensorid] = true;
        }
        else if (key.compare(KEY_SENSORCOST) == 0) {
            if(!(stream >> sensorCosts[sensorid])) {
                cerr << "Sensor cost paring error." << endl;
                return false;
            }
        }
    }
    // Check if all fields are filled.
    if(computeCap < 0 ) {
        cerr << "Compute Cap not set." << end;
    }
    if (power < 0 ) {
        cerr << "Power not set." << endl;
    }
    for (int i = 0; i < MAX_SENSORS; i ++) {
        if (sensors[i] == true && sensorCosts[i] < 0) {
            return false;
        }
    }
    return true;
}

string Status::genStatusString() {
    ostringstream stream;
    stream << "computeCap:" << computeCap;
    return stream.str();
}

void Status::printInformation() {
}

Status::~Status() {
}

