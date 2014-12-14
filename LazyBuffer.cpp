#include "LazyBuffer.h"

LazyBuffer::LazyBuffer()
{
    init(DEFAULT_LAZYBUFFER_SIZE);
}
LazyBuffer::LazyBuffer(unsigned long initSize)
{
    init(initSize);
}
LazyBuffer::~LazyBuffer()
{
    delete[] buff;
}
void LazyBuffer::init(unsigned long initSize)
{
    size=initSize;
    used=0;
    buff=new char[size];
}

const char *LazyBuffer::GetBuff()
{
    return buff;
}
unsigned long LazyBuffer::GetUsedSize()
{
    return used;
}

unsigned long LazyBuffer::GetSize()
{
    return size;
}

void LazyBuffer::Fit()
{
    if(used<size)
    {
        int newSize=used;
        if(newSize<=0)newSize=1;
        char *newBuff=new char[newSize];
        memcpy(newBuff,buff,newSize);
        delete[] buff;
        buff=newBuff;
        size=newSize;
    }
}

void LazyBuffer::InitToUse(unsigned long newSize,bool copyIfReAlloc,bool bZero)
{
    if(newSize>size)
    {//空间不足
        char *newBuff=new char[newSize];
        if(copyIfReAlloc)
        {
            memcpy(newBuff,buff,size);
        }
        delete[] buff;
        buff=newBuff;
        size=newSize;
    }
    if(bZero)
    {
            memset(buff,0,size);
    }
    used=0;
}

int LazyBuffer::AddData(const char *data,unsigned long len)
{
    if(!data || used+len>size)return 0;
    memcpy(buff+used,data,len);
    used+=len;
    return len;
}

bool LazyBuffer::SetUsed(unsigned long newUsed)
{
    if(newUsed>size)return false;
    used=newUsed;
    return true;
}

