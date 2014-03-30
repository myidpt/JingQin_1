/*
 * StatusFactory.h
 *
 *  Created on: Apr 12, 2013
 *      Author: yonggang
 */

#ifndef STATUSFACTORY_H_
#define STATUSFACTORY_H_

#include <IStatus.h>
#include <SimpleStatus.h>
#include <iostreamer/istreamer/Inputfile.h>

class StatusFactory {
public:
    enum StatusType {
        SimpleStatusType
    };
protected:
    StatusType myStatusType;
    Inputfile * inputfile;
    bool parseStatusString(const string & str);
public:
    StatusFactory(const string & filename, StatusType type);
    IStatus * createStatus();
    virtual ~StatusFactory();
};

#endif /* STATUSFACTORY_H_ */
