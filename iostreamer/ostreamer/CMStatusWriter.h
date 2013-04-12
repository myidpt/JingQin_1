/*
 * CMStatusWriter.h
 *
 *  Created on: Apr 9, 2013
 *      Author: yonggang
 */

#ifndef CMSTATUSWRITER_H_
#define CMSTATUSWRITER_H_

#include <string>
#include "Outputfile.h"
#include "status/Status.h"

using namespace std;

class CMStatusWriter {
protected:
    Outputfile * outputfile;
public:
    CMStatusWriter(const string & filename);
    bool writeStatus(string & statusstr);
    virtual ~CMStatusWriter();
};

#endif /* CMSTATUSWRITER_H_ */
