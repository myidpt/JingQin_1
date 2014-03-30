/*
 * SimpleSubTask.h
 *
 *  Created on: Apr 16, 2013
 *      Author: yonggang
 */

#ifndef SIMPLESUBTASK_H_
#define SIMPLESUBTASK_H_

#include <omnetpp.h>
#include "ITask.h"
#include "status/IStatus.h"

class SimpleSubTask : public ITask {
protected:
    ITask * fatherTask;
    int Id;
    int sensorId;
    double inputData; // In MB.
    double outputData; // In MB.
    double computeCost;
    double maxDelay;
    int chunks; // Number of subtask chunks.
    int serverId; // The ID of the server serving it.
    bool isdispatched;
    bool isfinished;

    double arrivalTime;
    double finishTime;
    SimpleSubTask(ITask * fathertask, int chunks, IStatus * server);

    IStatus * server;

public:
    enum Parameter {
        CHUNKS,
        ERROR
    };
    cObject * dup();
    int getId();
    int getSensorId();
    double getArrivalTime();
    double getFinishTime();
    ITask::TaskType getTaskType();
    double getInputData();
    double getOutputData();
    double getComputeCost();
    double getRemainingCost();
    double getRemainingTimeBeforeDeadline();
    double getMaxDelay();
    ITask * getFatherTask();
    int getServerId();
    void setServerId(int id);

    bool setParameter(int param, double value);
    double getParameter(int param);
    bool parseTaskString(string & line);
    void printInformation();
    bool dispatched();
    bool finished();
    virtual ~SimpleSubTask();
    friend class SimpleTask;
};

#endif /* SIMPLESUBTASK_H_ */
