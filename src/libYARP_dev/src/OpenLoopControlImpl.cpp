/*
 * Copyright (C) 2008 RobotCub Consortium
 * Authors: Marco Randazzo and Lorenzo Natale
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include "yarp/dev/ImplementOpenLoopControl.h"
#include <yarp/dev/ControlBoardHelper.h>
#include <iostream>

using namespace yarp::dev;
#define JOINTIDCHECK if (j >= castToMapper(helper)->axes()){yError("joint id out of bound"); return false;}
#define MJOINTIDCHECK(i) if (joints[i] >= castToMapper(helper)->axes()){yError("joint id out of bound"); return false;}
#define PJOINTIDCHECK(j) if (j >= castToMapper(helper)->axes()){yError("joint id out of bound"); return false;}

/////////////// implement ImplementOpenLoopControl
ImplementOpenLoopControl::ImplementOpenLoopControl(IOpenLoopControlRaw *r)
{
    raw=r;
    helper=0;
}

bool ImplementOpenLoopControl::initialize(int size, const int *amap)
{
    if (helper!=0)
        return false;

    double *dummy=new double [size];
    for(int k=0;k<size;k++)
        dummy[k]=0;

    helper=(void *)(new ControlBoardHelper(size, amap, dummy, dummy, dummy));
    yAssert(helper != 0);

    delete [] dummy;
    return true;
}

ImplementOpenLoopControl::~ImplementOpenLoopControl()
{
    uninitialize();
}

bool ImplementOpenLoopControl::uninitialize ()
{
    if (helper!=0)
    {
        delete castToMapper(helper);
        helper=0;
    }

    return true;
}

bool ImplementOpenLoopControl::setRefOutput(int j, double v)
{
    JOINTIDCHECK
    int k=castToMapper(helper)->toHw(j);

    return raw->setRefOutputRaw(k, v);
}

bool ImplementOpenLoopControl::setRefOutputs(const double *v)
{
    castToMapper(helper)->toHw(v, dummy);

    return raw->setRefOutputsRaw(dummy);
}

bool ImplementOpenLoopControl::getRefOutput(int j, double *v)
{
    JOINTIDCHECK
    int k=castToMapper(helper)->toHw(j);

    bool ret = raw->getRefOutputRaw(k, v);
    return ret;
}

bool ImplementOpenLoopControl::getRefOutputs(double *v)
{
    bool ret=raw->getRefOutputsRaw(dummy);

    castToMapper(helper)->toUser(dummy, v);
    return ret;
}

bool ImplementOpenLoopControl::getOutput(int j, double *v)
{
    JOINTIDCHECK
    int k=castToMapper(helper)->toHw(j);

    bool ret = raw->getOutputRaw(k, v);
    return ret;
}

bool ImplementOpenLoopControl::getOutputs(double *v)
{
    bool ret=raw->getOutputsRaw(dummy);

    castToMapper(helper)->toUser(dummy, v);
    return ret;
}
