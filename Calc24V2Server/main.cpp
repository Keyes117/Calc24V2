

#include <iostream>

#include "TCPServer.h"

int main()
{
    TCPServer calc24Serevr;
    if (!calc24Serevr.init(5, "0.0.0.0", 8888))
    {
        return 0;
    }

    calc24Serevr.start();
}