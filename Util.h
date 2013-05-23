#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>

class Util
{

public:
    static int randomInt(int min, int max);
    static void log(std::string msg);    
    static std::string convertIntToString(int value);
    static int convertUserDataToInt(void *param);
};

#endif // UTIL_H
