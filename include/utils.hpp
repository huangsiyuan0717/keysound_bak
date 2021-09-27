#pragma once

#include <string>

extern void addEventId(std::string);
extern void delEventId(std::string);
extern bool eventIdExists(std::string);

extern void addEventId(int);
extern void delEventId(int);
extern bool eventIdExists(int);
extern bool isEventIdLagerThan_FILE_NUMS(int);
extern void clearAllKeyDetectThreads();

// 判断是否为小端系统	Determine whether it is a little endian system
extern bool littleEnd();