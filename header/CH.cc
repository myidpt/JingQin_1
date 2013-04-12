/*
 * Maintain all the status of the CH.
 */

#include "CH.h"

Define_Module(CH);

void CH::initialize()
{
    numCM = par("numCM").longValue();
    string taskifilename = par("CH_task_input_filename").stdstringValue();
    string taskofilename = par("CH_task_output_filename").stdstringValue();
    string statusifilename = par("CM_status_input_filename").stdstringValue();
    string statusofilename = par("CM_status_output_filename").stdstringValue();

    taskReader = new CHTaskReader(taskifilename);
    ITask * task = new SimpleTask();
    while (taskReader->readNextTask(task));

    taskWriter = new CHTaskWriter(taskofilename);
    taskWriter->writeTask(task);

    cmStatusReader = new CMStatusReader(statusifilename);
    distributeInitialStatus();

    cmStatusWriter = new CMStatusWriter(statusofilename);
}

void CH::handleMessage(cMessage *msg)
{

}

void CH::distributeInitialStatus() {
    int id;
    string str;
    while((id = cmStatusReader->readNextStatus(str)) != -1) {
        cPacket * packet = new cPacket("InitialStatus", STATUS);
        cout << "id = " << id << ", info = " << str << endl;
        cMsgPar * par = new cMsgPar(STATUS_PAR);
        par->setStringValue(str.c_str());
        packet->addPar(par);
        sendSafe(id, packet);
    }
}

void CH::sendSafe(int id, cPacket * packet){
    cChannel * cch = gate("gate$o", id)->getTransmissionChannel();
    if(cch->isBusy()) {
        sendDelayed(packet, cch->getTransmissionFinishTime() - simTime(), "gate$o", id);
    }
    else {
        send(packet, "gate$o", id);
    }
}

