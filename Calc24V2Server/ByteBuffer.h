/*
* 2024/7/2
* 自定义缓冲区类
*/
#pragma once

#include <string>

class ByteBuffer
{
public:
    //TODO:完成构造、析构 拷贝构造、移动构造的逻辑 
    ByteBuffer();
    ~ByteBuffer();

    ByteBuffer(const ByteBuffer& rhs);
    ByteBuffer& operator=(const ByteBuffer& rhs);

    ByteBuffer(ByteBuffer&& rhs);
    ByteBuffer& operator=(ByteBuffer&& rhs);

public:
    void append(const char* buf, int bufLen);
    void retrieve(std::string& outBuf, int buf = 0);


    void clear();
private:
    std::string  m_internalBuf;
};

