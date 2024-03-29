#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Receiver: public cSimpleModule {
private:
    cOutVector receivedTimeVecotr;
    cDoubleHistogram hopCountStats;
    double lastMessageReceived;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(Receiver);

void Receiver::initialize() {
    lastMessageReceived = simTime().dbl();
    WATCH(lastMessageReceived);
}

void Receiver::handleMessage(cMessage *msg) {
    EV << "Received message:" << msg;

    receivedTimeVecotr.record(simTime().dbl() - lastMessageReceived);
    hopCountStats.collect(simTime().dbl() - lastMessageReceived);

    lastMessageReceived = simTime().dbl();
}

void Receiver::finish()
{
}
