#ifndef ETHOFFSET_H
#define ETHOFFSET_H
#include "offset.h"

class EthOffset : public Offset
{
public:
    EthOffset();
    ~EthOffset();

    virtual QString format();

};

#endif // ETHOFFSET_H
