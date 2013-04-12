/*
 * CMStatusWriter.cpp
 *  Write out the service records and node status, such as the residue power.
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#include "CMStatusWriter.h"

CMStatusWriter::CMStatusWriter(const string & filename) {
    outputfile = new Outputfile(filename);
}

bool CMStatusWriter::writeStatus(string & statusstr) {
    outputfile->writeLine(statusstr);
    return true;
}

CMStatusWriter::~CMStatusWriter() {
}

