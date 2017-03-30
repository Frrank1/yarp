/*
 * Copyright (C) 2006, 2008, 2009 RobotCub Consortium
 * Authors: Lorenzo Natale
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_DEV_IMPLEMENTOPENLOOPCONTROL_H
#define YARP_DEV_IMPLEMENTOPENLOOPCONTROL_H

#include <yarp/dev/IOpenLoopControl.h>
#include <yarp/dev/api.h>
#include <yarp/conf/system.h>

namespace yarp {
    namespace dev {
        class ImplementOpenLoopControl;
    }
}


#if defined(_MSC_VER) && !defined(YARP_NO_DEPRECATED) // since YARP 2.3.65
YARP_WARNING_PUSH
YARP_DISABLE_DEPRECATED_WARNING
#endif

class YARP_dev_API yarp::dev::ImplementOpenLoopControl: public IOpenLoopControl
{
    void *helper;
    yarp::dev::IOpenLoopControlRaw *raw;
    double *dummy;
public:
    bool initialize(int k, const int *amap);
    bool uninitialize();
    ImplementOpenLoopControl(IOpenLoopControlRaw *v);
    ~ImplementOpenLoopControl();
    bool setRefOutput(int j, double v);
    bool setRefOutputs(const double *v);
    bool getRefOutput(int j, double *v);
    bool getRefOutputs(double *v);
    bool getOutput(int j, double *v);
    bool getOutputs(double *v);
};

#if defined(_MSC_VER) && !defined(YARP_NO_DEPRECATED) // since YARP 2.3.65
YARP_WARNING_POP
#endif

#endif // YARP_DEV_IMPLEMENTOPENLOOPCONTROL_H
