#ifndef PYHANDLER_H
#define PYHANDLER_H

#include <stdint.h>
#include <vector>

#include "envlib.h"

using namespace std;

class pyhandler
{
    public:
        static int init(uint32_t N, uint32_t firstDisplay);

    private:
        static vector<envlib::dinoInterface> _environments;
};

#endif
