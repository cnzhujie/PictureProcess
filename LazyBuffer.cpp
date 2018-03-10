#include "LazyBuffer.h"

LazyBuffer::LazyBuffer() {
    init(DEFAULT_LAZYBUFFER_SIZE);
}

LazyBuffer::LazyBuffer(unsigned long initSize) {
    init(initSize);
}

LazyBuffer::~LazyBuffer() {
    delete[] buff;
}

void LazyBuffer::init(unsigned long initSize) {
    fullSize = initSize;
    usedSize = 0;
    buff = new char[fullSize];
}

const char *LazyBuffer::getBuff() {
    return buff;
}

unsigned long LazyBuffer::getUsedSize() {
    return usedSize;
}

unsigned long LazyBuffer::getFullSize() {
    return fullSize;
}

void LazyBuffer::fit() {
    if (usedSize < fullSize) {
        int newSize = usedSize;
        if (newSize <= 0)newSize = 1;
        char *newBuff = new char[newSize];
        memcpy(newBuff, buff, newSize);
        delete[] buff;
        buff = newBuff;
        fullSize = newSize;
    }
}

void LazyBuffer::initToUse(unsigned long newSize, bool copyIfReAlloc, bool bZero) {
    if (newSize > fullSize) {//空间不足
        char *newBuff = new char[newSize];
        if (copyIfReAlloc) {
            memcpy(newBuff, buff, fullSize);
        }
        delete[] buff;
        buff = newBuff;
        fullSize = newSize;
    }
    if (bZero) {
        memset(buff, 0, fullSize);
    }
    usedSize = 0;
}

int LazyBuffer::addData(const char *data, unsigned long len) {
    if (!data || usedSize + len > fullSize)return 0;
    memcpy(buff + usedSize, data, len);
    usedSize += len;
    return len;
}

bool LazyBuffer::setUsedSize(unsigned long newUsedSize) {
    if (newUsedSize > fullSize)return false;
    usedSize = newUsedSize;
    return true;
}

