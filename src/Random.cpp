#include "Random.h"

Random::Random() :
	m_engine(std::random_device()())
{
}

int Random::getInt(int low, int high)
{
	return std::uniform_int_distribution<int>(low, high)(m_engine);
}

float Random::getFloat(float low, float high)
{
	return std::uniform_real_distribution<float>(low, high)(m_engine);
}
