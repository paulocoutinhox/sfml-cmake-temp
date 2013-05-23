#include "Util.h"

int Util::randomInt(int min, int max)
{
    return min + (rand() % (int)(max - min + 1));
}

void Util::log(std::string msg)
{
    std::cout << "DEBUG: " << msg << std::endl;
}

std::string Util::convertIntToString(int value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

int Util::convertUserDataToInt(void *param)
{
    return *((int*)(&param));
}
