/*
 * CHTaskReader.cpp
 *  Reads the task traces from the input file.
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#include "CHTaskReader.h"

CHTaskReader::CHTaskReader(const string & filename) {
    inputfile = new Inputfile(filename);
}

bool CHTaskReader::readNextTask(ITask * task) {
    if (task == NULL) {
        return false;
    }
    string line;
    if(! inputfile->readNextLine(line)) {
        cout << "Task file meets EOF." << endl;
        return false;
    }
    return task->parseInputfile(line);
}

CHTaskReader::~CHTaskReader() {
    if (inputfile != NULL) {
        delete inputfile;
    }
}

