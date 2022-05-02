#include "Random.h"

std::mt19937 Random::s_engine(std::random_device().operator()());
std::uniform_int_distribution<std::mt19937::result_type> Random::s_distribution;

int Random::getInt(int low, int high)
{
    return low + (static_cast<int>(s_distribution(s_engine)) % (high - low + 1));
}

float Random::getFloat()
{
    return (float)s_distribution(s_engine) / (float)std::numeric_limits<std::mt19937::result_type>::max();
}

float Random::getFloat(float low, float high)
{
    return low + (high - low) * getFloat();
}
