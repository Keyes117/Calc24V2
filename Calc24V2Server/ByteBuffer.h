/*
* 2024/7/2
* �Զ��建������
*/
#pragma once

#include <string>

class ByteBuffer
{
public:
    //TODO:��ɹ��졢���� �������졢�ƶ�������߼� 
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

