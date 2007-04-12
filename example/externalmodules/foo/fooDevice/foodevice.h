// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2007 Lorenzo Natale
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

// This is just an example for an empty device.


#include <yarp/dev/DeviceDriver.h>

namespace yarp {
    namespace dev {
      class foodevice;
    } 
}

class yarp::dev::foodevice : public DeviceDriver
{
private:
public:
    foodevice() {}
    virtual bool open(yarp::os::Searchable& config);
};

