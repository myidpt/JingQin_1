/*
 * Task.cpp
 *
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#include "SimpleTask.h"

SimpleTask::SimpleTask() {

}

bool SimpleTask::setParameter(int param, double value) {
    return true;
}

double SimpleTask::getParameter(int param) {
    return 0;
}

bool SimpleTask::setFinishedSubTask(int id) {
    return true;
}

bool SimpleTask::setUnfinishedSubTask(int id) {
    return true;
}

bool SimpleTask::parseInputfile(string & line) {
    if (sscanf(line.c_str(), "%d %lf %d %d %lf %lf %lf %lf", &Id, &arrivalTime, &totalSubTasks, &sensorID,
            &inputData, &outputData, &computeCost, &maxDelay) == 8) {
        printInformation();
        return true;
    } else {
        return false;
    }
}

void SimpleTask::printInformation() {
    cout << "Id = " << Id <<
            ", arrivalTime = " << arrivalTime << ", totalSubTasks = " << totalSubTasks <<
            ", sensorID = " << sensorID << ", inputData = " << inputData <<
            ", outputData = " << outputData << ", computeCost = " << computeCost <<
            ", maxDelay = " << maxDelay << endl;
}

SimpleTask::~SimpleTask() {

}

