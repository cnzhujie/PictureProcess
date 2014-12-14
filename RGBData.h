#ifndef RGBDATA_H
#define RGBDATA_H

#include <stdio.h>
#include <string>
using namespace std;

#include "TRGB.h"
#include "rgb2bmp.h"
#include "bmp2rgb.h"

/**
 * RGB像素图片类
 */
class RGBData
{
    public:
        RGBData(unsigned long w,unsigned long h);
        RGBData(string fn);
        virtual ~RGBData();
    public:
        /*初始化图片的像素值*/
        void Init(TRGB& rgb);
        /*设置i行j列的颜色*/
        void SetColor(unsigned long i,unsigned long j,TRGB& rgb);
        /*将rgb数据保存成bmp图像*/
        bool SaveToFile(string fn);
        /*从图片载入rgb数据*/
        bool LoadFromFile(string fn);
        /*在此图片之上叠加另外一张图片*/
        void Overlap(const RGBData& another,TRGB& transparent);
    private:
        TRGB *m_pArr;//rgb数组
        unsigned long m_w;//宽度
        unsigned long m_h;//高度
    public:
        inline unsigned long getW(){return m_w;}
        inline unsigned long getH(){return m_h;}
        inline TRGB *getArr(){return m_pArr;}
};

#endif // RGBDATA_H
