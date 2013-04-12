

#include "CM.h"

Define_Module(CM);

void CM::initialize()
{
    status = NULL;
}

void CM::handleMessage(cMessage *msg)
{
    cPacket * packet = (cPacket *)msg;
    switch (packet->getKind()) {
    case STATUS:
        status = Status::createStatus(packet->par(STATUS_PAR).stringValue());
        delete packet;
    }

}
