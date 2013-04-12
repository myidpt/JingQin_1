/*
 * CMStatusReader.h
 *
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#ifndef CMSTATUSREADER_H_
#define CMSTATUSREADER_H_

#include <string>
#include "Inputfile.h"
#include "status/Status.h"

using namespace std;

class CMStatusReader {
protected:
    Inputfile * inputfile;
public:
    CMStatusReader(const string & filename);
    int readNextStatus(string & str); // The return is the ID of the target node.
    virtual ~CMStatusReader();
};

#endif /* CMSTATUSREADER_H_ */
