/* Created by minseoi */

#pragma once


class App
{
private:
    inline static double CurrentTime    = 0;
    inline static double DeltaTime      = 1 / 30.0;

public:
    inline static double GetCurrentTime()
    {
        return CurrentTime;
    }

    static void SetCurrentTime(double Seconds)
    {
        CurrentTime = Seconds;
    }

    inline static double GetDeltaTime()
    {
        return DeltaTime;
    }

    static void SetDeltaTime(double Seconds)
    {
        DeltaTime = Seconds;
    }
};
