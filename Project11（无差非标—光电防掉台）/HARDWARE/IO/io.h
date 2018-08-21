#ifndef __IO_H
#define __IO_H
#include "sys.h"
//#define check PCout(1)
void IO_Init(void);
#define io1 PBin(7)
#define io2 PBin(8)
#define io3 PBin(9)
#define io4 PCin(6)
#define io5 PDin(14)
#define io6 PDin(15)
#endif
