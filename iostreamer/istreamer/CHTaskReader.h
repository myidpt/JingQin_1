/*
 * CHTaskReader.h
 *
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#ifndef CHTASKREADER_H_
#define CHTASKREADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Inputfile.h"
#include "task/ITask.h"

using namespace std;

class CHTaskReader {
protected:
    Inputfile * inputfile;
public:
    CHTaskReader(const string & filename);
    bool readNextTask(ITask * task);
    virtual ~CHTaskReader();
};

#endif /* CHTASKREADER_H_ */
