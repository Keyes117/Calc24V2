/*
* 2024/7/2
* 自定义缓冲区类
*/
#pragma once

#include <string>

class ByteBuffer
{
public:
    ByteBuffer();
    ~ByteBuffer();

    ByteBuffer(const ByteBuffer& rhs);
    ByteBuffer& operator=(const ByteBuffer& rhs);

    ByteBuffer(ByteBuffer&& rhs);
    ByteBuffer& operator=(ByteBuffer&& rhs);

public:
    // 这里是重载 （）操作符
    //const char* operator()();

    //这里是说类可以隐式的转成 const char*
    operator const char* ();

    void append(const char* buf, int bufLen);
    //取数据 
    void retrieve(std::string& outBuf, int buf = 0);
    size_t retrieve(char* outBuf, size_t bufLen = 0);

    size_t peek(char* buf, size_t bufLen);

    void erase(int bufLen = 0);

    int remaining();

    void clear();

    bool isEmpty();
private:
    std::string  m_internalBuf;
};

