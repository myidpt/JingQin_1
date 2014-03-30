/*
 * TaskFactory.cc
 *
 *  Created on: Apr 13, 2013
 *      Author: yonggang
 */

#include "TaskFactory.h"

TaskFactory::TaskFactory(const string & filename, ITask::TaskType type) {
    inputfile = new Inputfile(filename);
    myTaskType = type;
    initialAverageWorkloadsAvailable = parseInitialParameters(initialAverageWorkloads);
}

bool TaskFactory::parseInitialParameters(double input[]) {
    string line;
    if (!inputfile->readNextLine(line)) {
        return false;
    }
    int start = 0;
    int end = 0;
    int colon = 0;
    string sensoridstr;
    string valuestr;
    int sensorid = 0;
    double value = 0;
    while((colon=line.find(':',start)) != string::npos) {
        sensoridstr = line.substr(start, colon - start);
        end = line.find(',', colon);
        if (end == (int)string::npos) {
            valuestr = line.substr(colon + 1, (int)string::npos);
        }
        else {
            valuestr = line.substr(colon + 1, end - colon - 1);
        }
        istringstream sensoridstream(sensoridstr);
        if(!(sensoridstream >> sensorid)) {
            cerr << "parseInitialParameters: Sensor Id error:" << sensoridstr << endl;
            break;
        }
        istringstream valuestream(valuestr);
        if(!(valuestream >> value)) {
            cerr << "parseInitialParameters: Value parsing error:" << valuestr << endl;
            break;
        }
        input[sensorid] = value;
        if (end == (int)string::npos) { // This is the last one.
            return true;
        }
        start = end + 1;
    }

    for (int i = 0; i < MAX_SENSORS; i ++) { // Set to be default.
        input[i] = 0;
    }

    return false;
}

bool TaskFactory::getInitialAverageWorkloads(double workloads[]) {
    if (! initialAverageWorkloadsAvailable) {
        return false;
    }
    for (int i = 0; i < MAX_SENSORS; i ++) {
        workloads[i] = initialAverageWorkloads[i];
    }
    return true;
}

ITask * TaskFactory::createTask() {
    ITask * task;
    if (myTaskType == ITask::SimpleTaskType) {
        task = new SimpleTask();
    }
    else {
        cerr << "Unknown task type:" << myTaskType << endl;
        return NULL;
    }
    string str;
    if (inputfile->readNextLine(str)) {
        if(!task->parseTaskString(str)) {
            delete task;
            return NULL;
        }
    }
    else {
        delete task;
        return NULL;
    }
    return task;
}

TaskFactory::~TaskFactory() {
}

