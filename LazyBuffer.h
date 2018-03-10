#ifndef LAZYBUFFER_H
#define LAZYBUFFER_H

#include <string.h>

#define DEFAULT_LAZYBUFFER_SIZE     1024*10     //10k

/********************************************************************
惰性缓冲区类
适用场合：当需要频繁开辟缓冲区作为中转时，每次使用之前可调用InitToUse设置需要的大小，
如果当前缓冲区大小不足则会重新分配
 ********************************************************************/
class LazyBuffer {
public:
    LazyBuffer();
    LazyBuffer(unsigned long initSize);
    ~LazyBuffer();
private:
    void init(unsigned long initSize);
private:
    char *buff; //缓冲区地址
    unsigned long usedSize; //已使用大小
    unsigned long fullSize; //总大小
public:
    /**
     * 返回缓冲区已使用的大小
     */
    unsigned long getUsedSize();
    /**
     * 返回缓冲区总大小
     */
    unsigned long getFullSize();
    /**
     * 重新根据缓冲区已使用的大小分配空间
     */
    void fit();
public:
    /**
     * 缓冲区使用之前进行初始化
     * 
     * @param newSize        newSize不为0则是给定一个新的大小，如果当前空间不够，就重新分配
     * @param copyIfReAlloc  如果重新分配内存，原来的内容是否拷贝过来，默认false
     * @param bZero          是否将缓冲区中的内存全部默认填充0，默认false
     */
    void initToUse(unsigned long newSize = 0, bool copyIfReAlloc = false, bool bZero = false);
    /**
     * 向缓冲区写入数据,返回写入个数，如果写入不下返回0
     * 
     * @param data  要写入数据的地址
     * @param len   要写入的长度
     * @return 
     */
    int addData(const char *data, unsigned long len);
    /**
     * 返回缓冲区指针地址
     * 
     * @return 
     */
    const char *getBuff();
    /**
     * 设置缓冲区已使用大小
     * 
     * @param newUsedSize
     * @return 
     */
    bool setUsedSize(unsigned long newUsedSize);
};

#endif  //_LazyBuffer_H_
