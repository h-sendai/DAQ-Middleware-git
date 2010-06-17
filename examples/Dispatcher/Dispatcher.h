// -*- C++ -*-
/*!
 * @file Dispatcher.h
 * @brief Event data dispatching component. 
 * @date
 * @author Kazuo Nakayoshi <kazuo.nakayoshi@kek.jp>
 *
 * Copyright (C) 2008
 *     Kazuo Nakayoshi
 *     Electronics System Group,
 *     KEK, Japan.
 *     All rights reserved.
 *
 */

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <boost/algorithm/string.hpp>
#include "DaqComponentBase.h"

// Service implementation headers
#include "DAQServiceSVC_impl.h"

using namespace RTC;

class Dispatcher
    : public DAQMW::DaqComponentBase
{
public:
    Dispatcher(RTC::Manager* manager);
    ~Dispatcher();

    // The initialize action (on CREATED->ALIVE transition)
    virtual RTC::ReturnCode_t onInitialize();

    // The execution action that is invoked periodically
    virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

private:
    TimedOctetSeq m_in_data;
    ///InPort<TimedOctetSeq, MyRingBuffer> m_InPort;
    InPort<TimedOctetSeq> m_InPort;
  
    TimedOctetSeq m_out_data1;
    ///OutPort<TimedOctetSeq, MyRingBuffer> m_OutPort1;
    OutPort<TimedOctetSeq> m_OutPort1;
    TimedOctetSeq m_out_data2;
    ///OutPort<TimedOctetSeq, MyRingBuffer> m_OutPort2;
    OutPort<TimedOctetSeq> m_OutPort2;

private:
    int daq_dummy();
    int daq_configure();
    int daq_unconfigure();
    int daq_start();
    int daq_run();
    int daq_stop();
    int daq_pause();
    int daq_resume();

    int parse_params(::NVList* list);
    int set_sampling_rate(int rate);
    int reset_InPort();

    BufferStatus m_in_status;
    BufferStatus m_out1_status;
    BufferStatus m_out2_status;

    int m_sampling_rate;
    std::string m_monitor_port_name;

    bool m_debug;
};


extern "C"
{
  void DispatcherInit(RTC::Manager* manager);
};

#endif // DISPATCHER_H
