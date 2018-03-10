/*
 * bmp2rgb.cpp
 *
 *  Created on: 2014年5月9日
 *      Author: zhujie
 */
 
#include "bmp2rgb.h"

bool readBmpInfo(const char* bmpName,BITMAPFILEHEADER& bitMapFileHeader,BITMAPINFOHEADER& bitMapInfoHeader)
{
    //以二进制读方式打开指定的图像文件
    FILE* fp=fopen(bmpName,"rb");
    if(!fp) return false;
    //读位图文件头
    fread(&bitMapFileHeader,sizeof(BITMAPFILEHEADER),1,fp);
    //读位图信息头
    fread(&bitMapInfoHeader,sizeof(BITMAPINFOHEADER),1,fp);

    fclose(fp);

    return true;
}
bool readBmpData(const char* bmpName,TRGB* pRgb,unsigned long size)
{
    if(pRgb==NULL)return false;
    //以二进制读方式打开指定的图像文件
    FILE* fp=fopen(bmpName,"rb");
    if(!fp) return false;
    BITMAPFILEHEADER bitMapFileHeader;
    BITMAPINFOHEADER bitMapInfoHeader;
    //获取文件头和文件信息
    //读位图文件头
    fread(&bitMapFileHeader,sizeof(BITMAPFILEHEADER),1,fp);
    //读位图信息头
    fread(&bitMapInfoHeader,sizeof(BITMAPINFOHEADER),1,fp);
    if(size < bitMapInfoHeader.biWidth*bitMapInfoHeader.biHeight
            || bitMapInfoHeader.biBitCount!=24)
    {//缓冲区大小不足或者不是24位图
        fclose(fp);
        return false;
    }
    /*颜色表中RGBQUAD结构数据的个数有biBitCount来确定：
     * 当biBitCount=1,4,8时，分别有2,16,256个表项；
     * 当biBitCount=24时，没有颜色表项。
     * 
     * 当biBitCount=1时，8个像素占1个字节；
     * 当biBitCount=4时，2个像素占1个字节；
     * 当biBitCount=8时，1个像素占1个字节；
     * 当biBitCount=24时，1个像素占3个字节,按顺序分别为B,G,R；
     */
    /*RGBQUAD* pColorTable = NULL;
    int colorTableSize=0;
    if(bitMapInfoHeader.biBitCount==1)
    {
        colorTableSize = 2;
    }
    else if(bitMapInfoHeader.biBitCount==4)
    {
        colorTableSize = 16;
    }
    else if(bitMapInfoHeader.biBitCount==8)
    {
        colorTableSize = 256;
    }
    if(colorTableSize>0)
    {
        //申请颜色表所需要的空间
        pColorTable=new RGBQUAD[colorTableSize];
        fread(pColorTable,sizeof(RGBQUAD),colorTableSize,fp);
    }*/
    //定位到数据位置
    fseek(fp,bitMapFileHeader.bfOffBits,SEEK_SET); 
    int lineBytes=3*bitMapInfoHeader.biWidth;
    int modVal=lineBytes % 4;
    if( modVal == 0)
    {//可以整除4
        unsigned long biSizeImage=(unsigned long)bitMapInfoHeader.biSizeImage;
        if(size*sizeof(TRGB) < biSizeImage)
        {
            fclose(fp);
            return false;
        }
        fread(pRgb,1,biSizeImage,fp);
    }
    else
    {//不可整除4
        int addZeroCount=4-modVal;
        char *pZero=new char[addZeroCount];
        for(int i=0;i<bitMapInfoHeader.biHeight;i++)
        {
            fread((char*)(pRgb)+i*lineBytes,1,lineBytes,fp);
            fread(pZero,1,addZeroCount,fp);
        }
        delete[] pZero;
    }

    //删除颜色表
    //if(pColorTable)delete[] pColorTable;
    fclose(fp);

    return true;
}
bool readBmpData(const char* bmpName,LazyBuffer& buff)
{
    //以二进制读方式打开指定的图像文件
    FILE* fp=fopen(bmpName,"rb");
    if(!fp) return false;
    BITMAPFILEHEADER bitMapFileHeader;
    BITMAPINFOHEADER bitMapInfoHeader;
    //获取文件头和文件信息
    //读位图文件头
    fread(&bitMapFileHeader,sizeof(BITMAPFILEHEADER),1,fp);
    //读位图信息头
    fread(&bitMapInfoHeader,sizeof(BITMAPINFOHEADER),1,fp);
    //真彩色图片没有颜色表
    //灰度图片有颜色表，其颜色表为256
    if(bitMapInfoHeader.biBitCount==8)
    {
        //申请颜色表所需要的空间
        RGBQUAD* pColorTable=new RGBQUAD[256];
        fread(pColorTable,sizeof(RGBQUAD),256,fp);
        delete[] pColorTable;
    }
    //申请位图数据所需的空间，读位图数据进内存
    long biSizeImage=(long)bitMapInfoHeader.biSizeImage;
    buff.initToUse(biSizeImage);
    fread((char *)buff.getBuff(),1,biSizeImage,fp);
    fclose(fp);

    return true;
}
