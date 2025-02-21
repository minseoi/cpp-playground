/* Created by minseoi */

#pragma once

extern bool GIsRequestingExit;

inline bool IsEngineExitRequested()
{
    return GIsRequestingExit;
}
