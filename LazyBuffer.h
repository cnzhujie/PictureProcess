#ifndef LAZYBUFFER_H
#define LAZYBUFFER_H

#include <string.h>

#define DEFAULT_LAZYBUFFER_SIZE     1024*10     //10k

/********************************************************************
惰性缓冲区类
适用场合：当需要频繁开辟缓冲区作为中转时，每次使用之前可调用InitToUse设置需要的大小，
如果当前缓冲区大小不足则会重新分配
********************************************************************/
class LazyBuffer
{
public:
    LazyBuffer();
    LazyBuffer(unsigned long initSize);
    ~LazyBuffer();
private:
    void init(unsigned long initSize);
private:
    char *buff;//缓冲区地址
    unsigned long used;//已使用大小
    unsigned long size;//总大小
public:
    /*返回缓冲区已使用的大小*/
    unsigned long GetUsedSize();
    /*返回缓冲区总大小*/
    unsigned long GetSize();
    /*重新根据缓冲区已使用的大小分配空间*/
    void Fit();
public:
    /*开始使用缓冲区前调用，
        newSize不为0则是给定一个新的大小，如果当前空间不够，就重新分配
    */
    void InitToUse(unsigned long newSize=0,bool copyIfReAlloc=false,bool bZero=false);
    /*向缓冲区写入数据,返回写入个数，如果写入不下返回0*/
    int AddData(const char *data,unsigned long len);
    /*返回缓冲区指针地址*/
    const char *GetBuff();
    /*设置缓冲区已使用大小*/
    bool SetUsed(unsigned long newUsed);
};

#endif  //_LazyBuffer_H_
