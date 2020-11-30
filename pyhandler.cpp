#include "pyhandler.h"

#include "envlib.h"

#include <vector>

using namespace envlib;

using namespace std;

vector<envlib::dinoInterface> pyhandler::_environments;

int pyhandler::init(uint32_t N, uint32_t firstDisplay)
{
    _environments = vector<envlib::dinoInterface>();
    _environments.reserve(N);

    for (uint32_t i = 0; i < N; ++i)
    {
        _environments.emplace_back(firstDisplay + i);
    }

    printf("\nInitialization complete\n");

    return 0; // success
}

/*
int pyhandler::getScore(uint32_t i, uint32_t &score)
{
    return _environments.at(i).getScore(score);
}
*/

<<<<<<< HEAD
int pyhandler::getObservation(uint32_t i, uint32_t obs[OBS_SIZE])
=======
//int pyhandler::getObservation(uint32_t i, uint32_t *obs[OBS_SIZE])
int pyhandler::getObservation(uint32_t i, uint32_t *obs[OBS_SIZE], uint32_t &score)
>>>>>>> cad741017065991c82e55981d4b9ab41f44ee729
{
    return _environments.at(i).getObservation(obs, score);
}

int pyhandler::setAction(uint32_t i, uint32_t action)
{
    return _environments.at(i).setAction((envlib::dinoInterface::Action)action);
}
