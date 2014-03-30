/*
 * TaskFactory.h
 *
 *  Created on: Apr 13, 2013
 *      Author: yonggang
 */

#ifndef TASKFACTORY_H_
#define TASKFACTORY_H_

#include <sstream>
#include "General.h"
#include "iostreamer/istreamer/Inputfile.h"
#include "ITask.h"
#include "SimpleTask.h"

class TaskFactory {
protected:
    ITask::TaskType myTaskType;
    Inputfile * inputfile;

    bool initialAverageWorkloadsAvailable;
    double initialAverageWorkloads[MAX_SENSORS];

    bool parseInitialParameters(double input[]);
public:
    TaskFactory(const string & filename, ITask::TaskType type);
    bool getInitialAverageWorkloads(double workloads[]);
    bool getBucketMaxCapRatios(double ratios[]);
    ITask * createTask();
    virtual ~TaskFactory();
};

#endif /* TASKFACTORY_H_ */
