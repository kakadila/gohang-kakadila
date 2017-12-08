#ifndef MSG_H
#define MSG_H

#include <stdint.h>
#include "protocol.h"

struct Msg
{
   uint32_t len;
   uint32_t protocol;
   uint32_t sender;
};

#endif // MSG_H
