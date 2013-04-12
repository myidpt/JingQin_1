/*
 * Task.h
 *
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#ifndef SIMPLETASK_H_
#define SIMPLETASK_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include "ITask.h"

using namespace std;

class SimpleTask : public ITask {
protected:
    int Id;
    double arrivalTime;
    int totalSubTasks;
    int sensorID;
    double inputData;
    double outputData;
    double computeCost;
    double maxDelay;

public:
    enum Parameter {
        ID, // From input. Read only.
        ARRIVAL_TIME, // From input.
        TOTAL_SUBTASKS, // From input.
        SENSOR_ID, // From input.
        INPUT_DATA, // From input.
        OUTPUT_DATA, // From input.
        COMPUTE_COST, // From input.
        MAX_DELAY, // From input.

        TOTAL_RUNTIME,
        NODES_USED,
        SUCCESS_RATE
    };
    SimpleTask();
    bool setParameter(int param, double value);
    double getParameter(int param);
    bool setFinishedSubTask(int id);
    bool setUnfinishedSubTask(int id);
    bool parseInputfile(string & line);
    void printInformation();
    virtual ~SimpleTask();
};

#endif /* SIMPLETASK_H_ */
