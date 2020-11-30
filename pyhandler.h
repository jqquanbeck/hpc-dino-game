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
<<<<<<< HEAD
        static int getScore(uint32_t i, uint32_t &score);
        static int getObservation(uint32_t i, uint32_t obs[OBS_SIZE]);
=======
        //static int getScore(uint32_t i, uint32_t &score);
        //static int getObservation(uint32_t i, uint32_t *obs[OBS_SIZE]);
		static int getObservation(uint32_t i, uint32_t *obs[OBS_SIZE], uint32_t &score);
>>>>>>> cad741017065991c82e55981d4b9ab41f44ee729
        static int setAction(uint32_t i, uint32_t action);
        // enum Action { NONE, UP, DOWN };

    private:
        static vector<envlib::dinoInterface> _environments;
};

#endif
