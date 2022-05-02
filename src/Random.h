#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
 public:
    static int getInt(int low, int high);
    static float getFloat();
    static float getFloat(float low, float high);

 private:
    static std::mt19937 s_engine;
    static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
};

#endif
