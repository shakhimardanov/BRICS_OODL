#ifndef BRICS_OODL_YOUBOT_H
#define BRICS_OODL_YOUBOT_H


#include <vector>
#include <sstream>
#include <string>
#include <boost/thread.hpp>
#include "rude/config.h"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/EthercatMaster.hpp"
#include "youbot/YouBotJoint.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"
#include "base-kinematic/FourSwedishWheelOmniBaseKinematic.hpp"

extern "C"{
#include <ethercattype.h>
#include <ethercatmain.h>
}

namespace brics_oodl {

//have to be a singleton in the system
class YouBot {
friend class YouBotJoint;
  private:
    static YouBot* instance;

    YouBot();

    YouBot(const YouBot& ) {};

    ~YouBot();


  public:
    static YouBot& getInstance(std::string ethernetDeviceName = "eth0");

    static void destroy();

    unsigned int getNumberOfJoints();

    YouBotJoint& getJoint(unsigned int jointNumber);

    void setBaseVelocity(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity);

    FourSwedishWheelOmniBaseKinematic YouBotBaseKinematic;


  private:
    void setMsgBuffer(const YouBotSlaveMsg& msgBuffer, unsigned int jointNumber);

    YouBotSlaveMsg getMsgBuffer(unsigned int jointNumber);

    void setMailboxMsgBuffer(const YouBotSlaveMailboxMsg& msgBuffer, unsigned int jointNumber);

    YouBotSlaveMailboxMsg getMailboxMsgBuffer(unsigned int jointNumber);

    void initializeEthercat();

    void initializeJoints();

    void initializeKinematic();

    bool closeEthercat();

    void updateSensorActorValues();

    std::vector<YouBotJoint> Joints;

    EthercatMaster* ethercatMaster;

    static std::string ethernetDevice;

    ec_mbxbuft mailboxBuffer;

    //in milliseconds
    static const unsigned int timeTillNextEthercatUpdate = 4;

    boost::mutex mutexDataOne;

    boost::mutex mutexDataTwo;

    boost::thread_group threads;

    volatile bool stopThread;

    boost::mutex mutexEthercatMaster;

    std::vector<YouBotSlaveMsg> firstBufferVector;

    std::vector<YouBotSlaveMsg> secondBufferVector;

    unsigned int nrOfSlaves;

    volatile bool newDataFlagOne;

    volatile bool newDataFlagTwo;

    std::vector<bool> newOutputDataFlagOne;

    std::vector<bool> newOutputDataFlagTwo;

    std::vector<outputBuffer*> ethercatOutputBufferVector;

    std::vector<inputBuffer*> ethercatinputBufferVector;

    std::vector<YouBotSlaveMailboxMsg> firstMailboxBufferVector;

    std::vector<YouBotSlaveMailboxMsg> secondMailboxBufferVector;

    std::vector<bool> newMailboxDataFlagOne;

    std::vector<bool> newMailboxDataFlagTwo;

    ec_mbxbuft mailboxBufferSend;

    unsigned int mailboxSendTimeout;

    ec_mbxbuft mailboxBufferReceive;

    std::vector<bool> newMailboxInputDataFlagOne;

    std::vector<bool> newMailboxInputDataFlagTwo;

    rude::Config configfile;

};

} // namespace brics_oodl
#endif