/*
 * CMStatusReader.cpp
 *  Read the initial status of each CM. Such as sensor types, power, computation capabilities, position and etc.
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#include "CMStatusReader.h"

CMStatusReader::CMStatusReader(const string & filename) {
    inputfile = new Inputfile(filename);
}

// The return is the ID of the target node. Return -1 means error or EOF.
// The string is written with the status information for the target node.
int CMStatusReader::readNextStatus(string & str) {
    if(! inputfile->readNextLine(str)) {
        return -1;
    }
    return Status::parseInputGetId(str);
}

CMStatusReader::~CMStatusReader() {
}

