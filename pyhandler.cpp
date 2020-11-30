#include "pyhandler.h"

#include "envlib.h"

#include <vector>

using namespace envlib;

using namespace std;


int pyhandler::init(uint32_t N, uint32_t firstDisplay)
{
    _environments.reserve(N);

    for (uint32_t i = 0; i < N; ++i)
    {
        _environments.emplace_back(firstDisplay + i);
    }

    printf("\nInitialization complete\n");

    return 0; // success
}