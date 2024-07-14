#include "ByteBuffer.h"

ByteBuffer::ByteBuffer()
{
}

ByteBuffer::~ByteBuffer()
{
}

ByteBuffer::ByteBuffer(const ByteBuffer& rhs) :
    m_internalBuf(rhs.m_internalBuf)
{

}

ByteBuffer& ByteBuffer::operator=(const ByteBuffer& rhs)
{
    // TODO: insert return statement here
    if (this != &rhs)
    {
        m_internalBuf = rhs.m_internalBuf;
    }
    return *this;
}

ByteBuffer::ByteBuffer(ByteBuffer&& rhs) :
    m_internalBuf(std::move(rhs.m_internalBuf))
{

}

ByteBuffer& ByteBuffer::operator=(ByteBuffer&& rhs)
{
    // TODO: insert return statement here
    if (this != &rhs)
    {
        m_internalBuf = std::move(rhs.m_internalBuf);
    }
    return *this;
}


ByteBuffer::operator const char* ()
{
    return m_internalBuf.c_str();
}

void ByteBuffer::append(const char* buf, int bufLen)
{
    m_internalBuf.append(buf, bufLen);
}

void ByteBuffer::retrieve(std::string& outBuf, int bufLen/* = 0*/)
{
    if (bufLen == 0 || bufLen >= m_internalBuf.length())
    {
        outBuf = std::move(m_internalBuf);
        return;
    }

    outBuf = m_internalBuf.substr(0, bufLen);
    m_internalBuf.erase(0, bufLen);
}

size_t ByteBuffer::retrieve(char* outBuf, size_t bufLen)
{
    if (bufLen == 0)
        return 0;

    if (bufLen >= m_internalBuf.size())
        bufLen = m_internalBuf.size();

    memcpy(outBuf, m_internalBuf.c_str(), bufLen);
    m_internalBuf.erase(0, bufLen);
    return bufLen;

}

size_t ByteBuffer::peek(char* buf, size_t bufLen)
{
    if (bufLen == 0)
        return 0;

    if (bufLen >= m_internalBuf.size())
        bufLen = m_internalBuf.size();

    memcpy(buf, m_internalBuf.c_str(), bufLen);

    return bufLen;
}

void ByteBuffer::erase(int bufLen /*= 0*/)
{
    if (bufLen == 0 || bufLen >= m_internalBuf.length())
    {
        m_internalBuf.clear();
        return;
    }

    m_internalBuf.erase(0, bufLen);
}

int ByteBuffer::remaining()
{
    return m_internalBuf.length();
}

void ByteBuffer::clear()
{
    m_internalBuf.clear();
}

bool ByteBuffer::isEmpty()
{

    return m_internalBuf.empty();
}