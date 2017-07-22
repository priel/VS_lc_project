#ifndef INIT_H
#define INIT_H

#include <math.h>
#include "./defined.h"

/// this is a container to hold all the variables of the system.
/// this should be hold by the system in order to calculate the potential.
/// the length of the molecules also hold here for performance.
/// another approach would be that every molecule with hold their structure.

class Init
{
    public:
        Init();
        virtual ~Init();


    protected:

    private:
};

#endif // INIT_H
