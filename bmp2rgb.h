/*
 * bmp2rgb.h
 *
 *  Created on: 2014年5月9日
 *      Author: zhujie
 */
 
#ifndef BMP2RGB_H_
#define BMP2RGB_H_

#include "TRGB.h"
#include "Common.h"
#include "LazyBuffer.h"
/************************************************
 * 此处的代码是从蒋俊的工程中拷贝而来，本人稍作修改，修复了读取图片
 * 未考虑每行数据4字节对齐时数据补零的问题。
 **************************************************/
#ifdef _WIN_
	#pragma pack(1) /*指定按2字节对齐，等价于#pragma pack(push,2)*/
	#include <windows.h>
	#pragma pack() /*取消指定对齐，恢复缺省对齐,等价于#pragma pack(pop)*/
#else

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3

typedef struct tagBITMAPFILEHEADER 
{
    RGB_WORD	bfType;
    RGB_DWORD	bfSize;
    RGB_WORD	bfReserved1;
    RGB_WORD	bfReserved2;
    RGB_DWORD	bfOffBits;
}__attribute__ ((packed)) BITMAPFILEHEADER,*LPBITMAPFILEHEADER,*PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    RGB_DWORD	biSize;
    RGB_LONG	biWidth;
    RGB_LONG	biHeight;
    RGB_WORD	biPlanes;
    RGB_WORD	biBitCount;
    RGB_DWORD	biCompression;
    RGB_DWORD	biSizeImage;
    RGB_LONG	biXPelsPerMeter;
    RGB_LONG	biYPelsPerMeter;
    RGB_DWORD	biClrUsed;
    RGB_DWORD	biClrImportant;
}__attribute__ ((packed)) BITMAPINFOHEADER,*LPBITMAPINFOHEADER,*PBITMAPINFOHEADER;

typedef struct tagRGBQUAD 
{
    RGB_BYTE	rgbBlue;
    RGB_BYTE	rgbGreen;
    RGB_BYTE	rgbRed;
    RGB_BYTE	rgbReserved;
}__attribute__ ((packed)) RGBQUAD,*LPRGBQUAD;
#endif


/**
 * 读取图片文件头信息
 * @param bmpName
 * @param bitMapFileHeader
 * @param bitMapInfoHeader
 * @return 
 */
bool readBmpInfo(const char* bmpName,BITMAPFILEHEADER& bitMapFileHeader,BITMAPINFOHEADER& bitMapInfoHeader);
/**
 * 读取图片数据
 * @param bmpName
 * @param pRgb
 * @param size
 * @return 
 */
bool readBmpData(const char* bmpName,TRGB* pRgb,unsigned long size);
/**
 * 读取图片数据
 * @param bmpName
 * @param buff
 * @return 
 */
bool readBmpData(const char* bmpName,LazyBuffer& buff);

#endif /* BMP2RGB_H_ */
