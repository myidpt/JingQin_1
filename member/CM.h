

#ifndef __JINGQIN_CM_H_
#define __JINGQIN_CM_H_

#include <omnetpp.h>
#include "General.h"
#include "status/Status.h"


class CM : public cSimpleModule
{
protected:
    Status * status;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
