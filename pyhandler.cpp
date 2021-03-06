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


int pyhandler::getObservation(uint32_t i, uint32_t obs[OBS_SIZE])
{
    return _environments.at(i).getObservation(obs);
}


int pyhandler::setAction(uint32_t i, uint32_t action)
{
    return _environments.at(i).setAction((envlib::dinoInterface::Action)action);
}
