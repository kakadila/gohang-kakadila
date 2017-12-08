#ifndef __LOG_H_
#define __LOG_H_


#include <stdio.h>

#define log(x) printf("%s,%d:%s\n",__FUNCTION__,__LINE__,x);

#endif
