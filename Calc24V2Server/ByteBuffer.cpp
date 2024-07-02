#include "ByteBuffer.h"

ByteBuffer::ByteBuffer()
{
}

ByteBuffer::~ByteBuffer()
{
}

ByteBuffer::ByteBuffer(const ByteBuffer& rhs)
{
}

ByteBuffer& ByteBuffer::operator=(const ByteBuffer& rhs)
{
    // TODO: insert return statement here
}

ByteBuffer::ByteBuffer(ByteBuffer&& rhs)
{
}

ByteBuffer& ByteBuffer::operator=(ByteBuffer&& rhs)
{
    // TODO: insert return statement here
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

void ByteBuffer::clear()
{
    m_internalBuf.clear();
}
