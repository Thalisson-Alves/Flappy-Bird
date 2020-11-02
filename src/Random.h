#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
public:
	Random();

	int getInt(int low, int high);
	float getFloat(float low, float high);

private:
	std::mt19937 m_engine;
};

#endif
