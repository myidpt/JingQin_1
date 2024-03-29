/*
 * SimpleSubTask.cc
 *
 *  Created on: Apr 16, 2013
 *      Author: yonggang
 */

#include "SimpleSubTask.h"

SimpleSubTask::SimpleSubTask(ITask * task, int chunks, IStatus * server) {
    fatherTask = task;
    this->chunks = chunks;
    arrivalTime = SIMTIME_DBL(simTime());
    this->serverId = server->getId();
    this->server = server;
    isfinished = false;
}

cObject * SimpleSubTask::dup() {
    SimpleSubTask * task = new SimpleSubTask(fatherTask, chunks, server);
    return task;
}

int SimpleSubTask::getId() {
    return Id;
}

int SimpleSubTask::getSensorId() {
    return sensorId;
}

double SimpleSubTask::getArrivalTime() {
    return arrivalTime;
}

double SimpleSubTask::getFinishTime() {
    cerr << "SimpleSubTask does not have getFinishTime." << endl;
    return 0;
}

ITask * SimpleSubTask::getFatherTask() {
    return fatherTask;
}

ITask::TaskType SimpleSubTask::getTaskType() {
    return ITask::SimpleSubTaskType;
}

int SimpleSubTask::getServerId() {
    return serverId;
}

void SimpleSubTask::setServerId(int id) {
    serverId = id;
}

double SimpleSubTask::getInputData() {
    return inputData;
}

double SimpleSubTask::getOutputData() {
    return outputData;
}

double SimpleSubTask::getComputeCost() {
    return computeCost;
}

double SimpleSubTask::getRemainingCost() {
    if (isfinished) {
        return 0;
    }
    else {
        return server->getRemainingCost();
    }
}

double SimpleSubTask::getMaxDelay() {
    return maxDelay;
}

double SimpleSubTask::getRemainingTimeBeforeDeadline() {
    return maxDelay + arrivalTime - SIMTIME_DBL(simTime());
}

bool SimpleSubTask::setParameter(int param, double value) {
    return true;
}

double SimpleSubTask::getParameter(int param) {
    return 0;
}

bool SimpleSubTask::parseTaskString(string & line) {
    cerr << "SimpleSubTask does not have parseTaskString." << endl;
    return false;
}

bool SimpleSubTask::dispatched() {
    return isdispatched;
}

bool SimpleSubTask::finished() {
    return isfinished;
}

void SimpleSubTask::printInformation() {
    cout << "Id = " << Id <<
            ", sensorId = " << sensorId << ", inputData = " << inputData <<
            ", outputData = " << outputData << ", computeCost = " << computeCost <<
            ", maxDelay = " << maxDelay << endl;
}

SimpleSubTask::~SimpleSubTask() {
}

