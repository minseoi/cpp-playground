/* Created by minseoi */

#pragma once

#define LOG(level, format, ...) \
std::printf("[%s] (%s/%d) " format "\n", level, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_D(format, ...) \
LOG("DEBUG", format, ##__VA_ARGS__)

#define LOG_I(format, ...) \
LOG("INFO", format, ##__VA_ARGS__)