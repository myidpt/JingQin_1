/*
 * ITask.h
 *  This class acts as an interface for all task types.
 *  Created on: Apr 10, 2013
 *      Author: yonggang
 */

#ifndef ITASK_H_
#define ITASK_H_

#include <string>
#include <iostream>

using namespace std;

class ITask {
public:
    ITask();
    virtual bool setParameter(int param, double value) = 0;
    virtual double getParameter(int param) = 0;
    virtual bool setFinishedSubTask(int id) = 0;
    virtual bool setUnfinishedSubTask(int id) = 0;
    virtual bool parseInputfile(string & line) = 0; // Parse a line of the input file.
    virtual void printInformation(); // For debugging.
    virtual ~ITask();
};

#endif /* ITASK_H_ */
