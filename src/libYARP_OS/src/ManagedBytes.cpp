#include <ace/config.h>
#include <ace/OS.h>

#include <yarp/ManagedBytes.h>

using namespace yarp;
using namespace yarp::os;

void ManagedBytes::copy() {
  if (!owned) {
    int len = length();
    char *buf = new char[len];
    yarp::os::Network::assertion(buf!=NULL);
    ACE_OS::memcpy(buf,get(),len);
    b = Bytes(buf,len);
    owned = true;
  }
}
