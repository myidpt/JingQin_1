/*
 * SimpleStatus.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: yonggang
 */

#include "SimpleStatus.h"

SimpleStatus::SimpleStatus() {
    computeCap = -1;
    power = -1;
    for (int i = 0; i < MAX_SENSORS; i ++) {
        sensors[i] = false;
        sensorCosts[i] = -1;
    }
    lastPowerUpdateTime = 0;
    currentTask = NULL;
}

int SimpleStatus::getId() {
    return myId;
}

void SimpleStatus::getSensors(bool sensors[]) {
    for (int i = 0; i < MAX_SENSORS; i ++) {
        sensors[i] = this->sensors[i];
    }
}

double SimpleStatus::getSensorCost(int id) {
    return sensorCosts[id];
}

double SimpleStatus::getComputeCap() {
    return computeCap;
}

// Update the power at this time point
double SimpleStatus::getPower() {
    double exetime = 0;
    double now = SIMTIME_DBL(simTime());
    if (currentTask != NULL) { // Update the residue energy.
        if (lastPowerUpdateTime <= currentTask->getArrivalTime()) { // Count the exe part.
            exetime = now - currentTask->getArrivalTime();
        }
        else { // Count the uncounted exe part.
            exetime = now - lastPowerUpdateTime;
        }
        power -= exetime * sensorCosts[currentTask->getSensorId()];
    }
    lastPowerUpdateTime = now;
    if (power < 0) {
        power = 0;
    }
    return power;
}

void SimpleStatus::assignTask(ITask * task) {
    currentTask = task;
    lastPowerUpdateTime = SIMTIME_DBL(simTime());
}

void SimpleStatus::taskFinish() {
    double now = SIMTIME_DBL(simTime());
    power -= (now - lastPowerUpdateTime) * sensorCosts[currentTask->getSensorId()];
    if (power < 0) {
        power = 0;
    }
    currentTask = NULL;
}

bool SimpleStatus::isBusy() {
    if (currentTask == NULL) {
        return false;
    }
    else {
        return true;
    }
}

double SimpleStatus::getRemainingCost() {
    if (currentTask == NULL) {
        cerr << "Error: getRemainingCost" << endl;
        return 0;
    }
    return currentTask->getComputeCost() - ((SIMTIME_DBL(simTime()) - currentTask->getArrivalTime()) * computeCap);
}

double SimpleStatus::predictExecutionTime(double cost) {
    return cost / computeCap;
}

// Incomplete
cObject * SimpleStatus::dup() {
    SimpleStatus * status = new SimpleStatus();
    return status;
}

bool SimpleStatus::parseStatusString(const string & str) {
    string fields[4];
    int start = 0;
    int end = 0;
    for (int i = 0; i < 3; i ++) {
        end = str.find(';', start);
        if (end == (int)string::npos) { // You meet the end before expected.
            cerr << "Meet the end before expected: " << str << endl;
            return false;
        }
        fields[i] = str.substr(start, end - start);
        start = end + 1;
    }
    fields[3] = str.substr(start, string::npos);

    istringstream stream0(fields[0]);
    istringstream stream1(fields[1]);
    istringstream stream2(fields[2]);
    if(!(stream0 >> myId)) {
        cerr << "myId parsing error." << endl;
        return false;
    }
    if(!(stream1 >> computeCap)) {
        cerr << "ComputeCap parsing error." << endl;
        return false;
    }
    if(!(stream2 >> power)) {
        cerr << "Power parsing error." << endl;
        return false;
    }
    start = 0;
    end = 0;
    int colon = 0;
    string sensoridstr;
    string valuestr;
    int sensorid = 0;
    int value = 0;

    while((colon=fields[3].find(':',start)) != string::npos) {
        sensoridstr = fields[3].substr(start, colon - start);
        end = fields[3].find(',', colon);
        if (end == (int)string::npos) {
            valuestr = fields[3].substr(colon + 1, (int)string::npos);
        }
        else {
            valuestr = fields[3].substr(colon + 1, end - colon - 1);
        }
        istringstream sensoridstream(sensoridstr);
        if(!(sensoridstream >> sensorid)) {
            cerr << "Sensor Id error:" << sensoridstr << endl;
            return false;
        }
        istringstream valuestream(valuestr);
        if(!(valuestream >> value)) {
            cerr << "Value parsing error:" << valuestr << endl;
            return false;
        }
        sensors[sensorid] = true;
        sensorCosts[sensorid] = value;
        if (end == (int)string::npos) { // This is the last one.
            break;
        }
        start = end + 1;
    }

    return true;
}

void SimpleStatus::printInformation() {
}

SimpleStatus::~SimpleStatus() {
}

