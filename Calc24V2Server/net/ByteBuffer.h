/*
* 2024/7/2
* �Զ��建������
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
    // ���������� ����������
    //const char* operator()();

    //������˵�������ʽ��ת�� const char*
    operator const char* ();

    void append(const char* buf, int bufLen);
    //ȡ���� 
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

