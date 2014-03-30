/*
 * Task.cpp
 *
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#include "SimpleTask.h"

SimpleTask::SimpleTask() {
    subId = 0;
    concurrency = 0;
    subTasks = new list<ITask *>();
}

cObject * SimpleTask::dup() {
    SimpleTask * task = new SimpleTask();
    return task;
}

int SimpleTask::getId() {
    return Id;
}

int SimpleTask::getSensorId() {
    return sensorId;
}

double SimpleTask::getArrivalTime() {
    return arrivalTime;
}

double SimpleTask::getFinishTime() {
    return finishTime;
}

// Return NULL if all dispatched.
ITask * SimpleTask::createSubTask(int chunks, IStatus * server) {
    if (undispatchedSubTasks == 0) { // All dispatched.
        return NULL;
    }
    if (chunks > undispatchedSubTasks) {
        chunks = undispatchedSubTasks;
    }
    undispatchedSubTasks -= chunks;
    SimpleSubTask * task = new SimpleSubTask(this, chunks, server);
    task->Id = this->Id * ID_INDEX + subId;
    subId ++;
    task->computeCost = computeCost * chunks / totalSubTasks;
    task->inputData = inputData * chunks / totalSubTasks;
    task->outputData = outputData * chunks / totalSubTasks;
    task->sensorId = sensorId;
    task->maxDelay = maxDelay;
    concurrency ++;
    server->assignTask(task);

    subTasks->push_front(task);

//    cout << "Allocate #" << task->Id << " (" << task->computeCost << ") to server #" << task->getServerId() << endl;
//    cout << "undispatchedSubTasks = " << undispatchedSubTasks << endl;
    return task;
}

ITask * SimpleTask::getFatherTask() {
    cerr << "SimpleTask does not have getFatherTask." << endl;
    return NULL;
}

ITask::TaskType SimpleTask::getTaskType() {
    return ITask::SimpleTaskType;
}

double SimpleTask::getInputData() {
    return inputData;
}

double SimpleTask::getOutputData() {
    return outputData;
}

double SimpleTask::getComputeCost() {
    return computeCost;
}

double SimpleTask::getRemainingCost() {
    return computeCost * undispatchedSubTasks / totalSubTasks + getServingWorkload();
}

double SimpleTask::getServingWorkload() {
    double remainingCost = 0;
    list<ITask *>::iterator it;
    for (it = subTasks->begin(); it != subTasks->end(); it ++) {
//        cout << "add cost: #" << (*it)->getId() << " - " << (*it)->getRemainingCost() << endl;
//        fflush (stdout);
        remainingCost += (*it)->getRemainingCost();
    }
    return remainingCost;
}

double SimpleTask::getRemainingTimeBeforeDeadline() {
    return maxDelay + arrivalTime - SIMTIME_DBL(simTime());
}

double SimpleTask::getMaxDelay() {
    return maxDelay;
}

int SimpleTask::getServerId() {
    cerr << "SimpleTask does not implement getServerId." << endl;
    return 0;
}

void SimpleTask::setServerId(int id) {
    cerr << "SimpleTask does not implement setServerId." << endl;
}

bool SimpleTask::setParameter(int param, double value) {
    if (param == PARADEGREE) {
        paradegree = value;
        return true;
    }
    return false;
}

double SimpleTask::getParameter(int param) {
    if (param == CONCURRENCY) {
        return concurrency;
    }
    else if (param == PARADEGREE) {
        return paradegree;
    }
    else if (param == DEGREEFUL) {
//        cout << "para:" << concurrency << ":" << paradegree << endl;
        if (concurrency >= paradegree) {
            return 1;
        }
        else {
            return -1;
        }
    }
    else if (param == SUBTASK_COST) {
        return computeCost / totalSubTasks;
    }
    return -1;
}

// Return true if all done. Return false if error happens or not all done.
bool SimpleTask::setFinishedSubTask(ITask * task) {
    if (task->getFatherTask() != this) {
        cerr << "Task's father task is not this." << endl;
        return false;
    }
    concurrency --;
    unfinishedSubTasks -= ((SimpleSubTask * )task)->chunks;

    subTasks->remove(task);

//    cout << "Get finished task #" << task->getId() << ", undispatchedSubTasks = " << undispatchedSubTasks << endl;
    if (unfinishedSubTasks < 0) {
        cerr << "SimpleTask: unfinishedSubTasks < 0" << endl;
        return false;
    }
    else if (unfinishedSubTasks == 0) {
        finishTime = SIMTIME_DBL(simTime());
//        cout << finishTime << ": Task #" << Id << " finished." << endl;
        return true;
    }
    return false;
}

// All of the subtasks are dispatched.
bool SimpleTask::dispatched() {
    if (undispatchedSubTasks == 0) {
        return true;
    }
    else {
        return false;
    }
}

// All of the subtasks are finished.
bool SimpleTask::finished() {
    if (unfinishedSubTasks == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool SimpleTask::parseTaskString(string & line) {
    if (sscanf(line.c_str(), "%d %lf %d %d %lf %lf %lf %lf", &Id, &arrivalTime, &totalSubTasks, &sensorId,
            &inputData, &outputData, &computeCost, &maxDelay) == 8) {
        undispatchedSubTasks = totalSubTasks;
        unfinishedSubTasks = totalSubTasks;
        printInformation();
        return true;
    } else {
        return false;
    }
}

int SimpleTask::getUnfinishedSubTasks() {
    return unfinishedSubTasks;
}

int SimpleTask::getUndispatchedSubTasks() {
    return undispatchedSubTasks;
}

int SimpleTask::getSubTaskCost() {
    return computeCost / totalSubTasks;
}

int SimpleTask::getConcurrency() {
    return concurrency;
}

void SimpleTask::printInformation() {
//    cout << "Id = " << Id <<
//            ", arrivalTime = " << arrivalTime << ", totalSubTasks = " << totalSubTasks <<
//            ", sensorId = " << sensorId << ", inputData = " << inputData <<
//            ", outputData = " << outputData << ", computeCost = " << computeCost <<
//            ", maxDelay = " << maxDelay << endl;

    cout << "SimpleTask, Id = " << Id <<
            ", arrivalTime = " << arrivalTime << endl;
}

SimpleTask::~SimpleTask() {
    if (subTasks != NULL) {
        delete subTasks;
        subTasks = NULL;
    }
}

