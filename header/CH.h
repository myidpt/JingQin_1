

#ifndef __JINGQIN_CH_H_
#define __JINGQIN_CH_H_

#include <string>
#include <omnetpp.h>
#include "General.h"
#include "task/SimpleTask.h"
#include "iostreamer/istreamer/CHTaskReader.h"
#include "iostreamer/ostreamer/CHTaskWriter.h"
#include "iostreamer/istreamer/CMStatusReader.h"
#include "iostreamer/ostreamer/CMStatusWriter.h"

class CH : public cSimpleModule
{
protected:
    int numCM;

    CHTaskReader * taskReader;
    CHTaskWriter * taskWriter;
    CMStatusReader * cmStatusReader;
    CMStatusWriter * cmStatusWriter;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    // Distribute the initial status to every CM.
    void distributeInitialStatus();
    void sendSafe(int id, cPacket * packet);
};

#endif
