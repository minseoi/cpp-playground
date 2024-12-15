/* Created by minseoi */

#pragma once

#define LOG(level, format, ...) \
std::printf("[%s] (%s/%d) " format "\n", level, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_D(format, ...) \
LOG("DEBUG", format, ##__VA_ARGS__)