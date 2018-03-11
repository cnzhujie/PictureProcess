
/*
 * bmp2rgb.h
 *
 *  Created on: 2014年5月9日
 *      Author: zhujie
 */

#ifndef BMP_H
#define BMP_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Common.h"
#include "LazyBuffer.h"



//变量重定义
typedef unsigned short RGB_WORD;
typedef unsigned int RGB_DWORD;
typedef unsigned char RGB_BYTE;
typedef int RGB_LONG;

/**
 * RGB
 */
class TRGB {
public:
    unsigned char b;
    unsigned char g;
    unsigned char r;
public:

    TRGB() {
        r = 0;
        g = 0;
        b = 0;
    }

    TRGB(unsigned char b1, unsigned char g1, unsigned char r1) {
        b = b1;
        g = g1;
        r = r1;
    }

    void set(unsigned char b1, unsigned char g1, unsigned char r1) {
        b = b1;
        g = g1;
        r = r1;
    }

    void rand() {
        srand((unsigned long) (time(NULL)));
        b = ::rand() % 256;
        g = ::rand() % 256;
        r = ::rand() % 256;
    }

    TRGB& increase() {
        if (b < 255) {
            b++;
        } else if (g < 255) {
            g++;
        } else if (r < 255) {
            r++;
        }
        return *this;
    }

    bool operator==(const TRGB& another) {
        return r == another.r && g == another.g && b == another.b;
    }
};




#ifdef _WIN_
#pragma pack(1) /*指定按2字节对齐，等价于#pragma pack(push,2)*/
#include <windows.h>
#pragma pack() /*取消指定对齐，恢复缺省对齐,等价于#pragma pack(pop)*/
#else

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3

typedef struct tagBITMAPFILEHEADER {
    RGB_WORD bfType;
    RGB_DWORD bfSize;
    RGB_WORD bfReserved1;
    RGB_WORD bfReserved2;
    RGB_DWORD bfOffBits;
} __attribute__ ((packed)) BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    RGB_DWORD biSize;
    RGB_LONG biWidth;
    RGB_LONG biHeight;
    RGB_WORD biPlanes;
    RGB_WORD biBitCount;
    RGB_DWORD biCompression;
    RGB_DWORD biSizeImage;
    RGB_LONG biXPelsPerMeter;
    RGB_LONG biYPelsPerMeter;
    RGB_DWORD biClrUsed;
    RGB_DWORD biClrImportant;
} __attribute__ ((packed)) BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
    RGB_BYTE rgbBlue;
    RGB_BYTE rgbGreen;
    RGB_BYTE rgbRed;
    RGB_BYTE rgbReserved;
} __attribute__ ((packed)) RGBQUAD, *LPRGBQUAD;
#endif


/**
 * 读取图片文件头信息
 * @param bmpFileName
 * @param bitMapFileHeader
 * @param bitMapInfoHeader
 * @return 
 */
bool readBmpInfo(const char* bmpFileName, BITMAPFILEHEADER& bitMapFileHeader, BITMAPINFOHEADER& bitMapInfoHeader);
/**
 * 读取图片数据
 * @param bmpFileName
 * @param pRgb
 * @param size
 * @return 
 */
bool readBmpData(const char* bmpFileName, TRGB* pRgb, unsigned long size);


/**
 * 将rgb数据写入bmp文件
 * @param pRgbBuffer
 * @param nWidth
 * @param nHeight
 * @param fp1
 * @return 
 */
int saveRgbToBmpFile(char *pRgbBuffer, int nWidth, int nHeight, FILE *fp1);


#endif /* BMP_H */

