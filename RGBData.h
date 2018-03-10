#ifndef RGBDATA_H
#define RGBDATA_H

#include <stdio.h>
#include <string>
using namespace std;

#include "Bmp.h"

/**
 * RGB像素图片类
 */
class RGBData {
public:
    RGBData(unsigned long w, unsigned long h);
    RGBData(string fn);
    virtual ~RGBData();
public:
    /**
     * 初始化图片的像素值
     * 
     * @param rgb
     */
    void init(TRGB& rgb);
    /**
     * 设置i行j列的颜色
     * 
     * @param i
     * @param j
     * @param rgb
     */
    void setColor(unsigned long i, unsigned long j, TRGB& rgb);
    /**
     * 将rgb数据保存成bmp图像
     * 
     * @param fn
     * @return 
     */
    bool saveToFile(string fn);
    /**
     * 从图片载入rgb数据
     * @param fn
     * @return 
     */
    bool loadFromFile(string fn);
    /**
     * 在此图片之上叠加另外一张图片
     * @param another
     * @param transparent
     */
    void overlap(const RGBData& another, TRGB& transparent);
private:
    TRGB *pArr; //rgb数组
    unsigned long w; //宽度
    unsigned long h; //高度
public:

    inline unsigned long getW() {
        return w;
    }

    inline unsigned long getH() {
        return h;
    }

    inline TRGB *getArr() {
        return pArr;
    }
};

#endif // RGBDATA_H
