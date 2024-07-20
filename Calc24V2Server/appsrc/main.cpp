

#include <iostream>

#include "Calc24Server.h"

int main()
{
    Calc24Server calc24Serevr;
    if (!calc24Serevr.init(5, "127.0.0.1", 8888))
    {
        return 0;
    }
    return 1;
}