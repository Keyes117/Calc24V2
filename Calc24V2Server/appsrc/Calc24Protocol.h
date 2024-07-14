#pragma once
#include <cstdint>

enum  class MsgType
{
    MsgTypeWelcome = 0,
    MsgTypeWaiting,
    MsgTypeInitCards,
    MsgTypeChatMsg
};


struct MsgHeader
{
    uint32_t packageSize;
    uint32_t msgType;
};


struct WelcomeMsg
{
    char welcomeMsg[32];
};
