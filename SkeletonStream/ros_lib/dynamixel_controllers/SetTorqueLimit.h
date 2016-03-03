#ifndef _ROS_SERVICE_SetTorqueLimit_h
#define _ROS_SERVICE_SetTorqueLimit_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_controllers
{

static const char SETTORQUELIMIT[] = "dynamixel_controllers/SetTorqueLimit";

  class SetTorqueLimitRequest : public ros::Msg
  {
    public:
      double torque_limit;

    SetTorqueLimitRequest():
      torque_limit(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_torque_limit;
      u_torque_limit.real = this->torque_limit;
      *(outbuffer + offset + 0) = (u_torque_limit.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_torque_limit.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_torque_limit.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_torque_limit.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_torque_limit.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_torque_limit.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_torque_limit.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_torque_limit.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->torque_limit);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_torque_limit;
      u_torque_limit.base = 0;
      u_torque_limit.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_torque_limit.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_torque_limit.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_torque_limit.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_torque_limit.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_torque_limit.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_torque_limit.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_torque_limit.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->torque_limit = u_torque_limit.real;
      offset += sizeof(this->torque_limit);
     return offset;
    }

    const char * getType(){ return SETTORQUELIMIT; };
    const char * getMD5(){ return "7ac67170532bb79d95db2a425915bbd6"; };

  };

  class SetTorqueLimitResponse : public ros::Msg
  {
    public:

    SetTorqueLimitResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return SETTORQUELIMIT; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetTorqueLimit {
    public:
    typedef SetTorqueLimitRequest Request;
    typedef SetTorqueLimitResponse Response;
  };

}
#endif
