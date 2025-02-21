/* Created by minseoi */

#pragma once
#include <chrono>
using namespace std::chrono;

class GenericPlatformTime
{
public:
    static inline double Seconds()
    {
        using namespace std::chrono;
        return duration_cast<duration<double>>(steady_clock::now().time_since_epoch()).count();
    }
};
