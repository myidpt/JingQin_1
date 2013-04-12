/*
 * CHTaskWriter.cpp
 *  Writes the task finish time stamps to the output file.
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#include "CHTaskWriter.h"

CHTaskWriter::CHTaskWriter(const string & filename) {
    outputfile = new Outputfile(filename);
}

bool CHTaskWriter::writeTask(ITask * task) {
    outputfile->writeLine("abciosu fsdklkj");
    return true;
}

CHTaskWriter::~CHTaskWriter() {
    if (outputfile != NULL) {
        delete outputfile;
    }
}

