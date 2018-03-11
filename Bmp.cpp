#include "Bmp.h"

int saveRgbToBmpFile(char *pRgbBuffer, int nWidth, int nHeight, FILE*fp1) {
    BITMAPFILEHEADER bmpFileHeader;
    bmpFileHeader.bfType = 0x4D42; //BM
    bmpFileHeader.bfSize = 3 * nWidth * nHeight + 54;
    bmpFileHeader.bfReserved1 = 0;
    bmpFileHeader.bfReserved2 = 0;
    bmpFileHeader.bfOffBits = 54;

    fwrite(&bmpFileHeader, 1, sizeof (BITMAPFILEHEADER), fp1);

    BITMAPINFOHEADER bmpInfoHeader;
    bmpInfoHeader.biSize = 40;
    bmpInfoHeader.biWidth = nWidth;
    bmpInfoHeader.biHeight = nHeight;
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.biBitCount = 24;
    bmpInfoHeader.biCompression = 0;
    bmpInfoHeader.biSizeImage = 3 * nWidth*nHeight;
    bmpInfoHeader.biXPelsPerMeter = 0;
    bmpInfoHeader.biYPelsPerMeter = 0;
    bmpInfoHeader.biClrUsed = 0;
    bmpInfoHeader.biClrImportant = 0;

    fwrite(&bmpInfoHeader, 1, sizeof (BITMAPINFOHEADER), fp1);
    //因为BMP格式规定图像每一行所占的字节数必须是4的倍数，如果不是4的倍数就要用0填充。
    //例如你一行是25像素，24位图每个像素3节字，那25像素就是25*3=75字节，75不是4的倍数，比75大的，并且是4的倍数最接近的就是76了，所以一行要填充到76个字节，也就是每一行后面要多加一个没用的字节
    int lineBytes = 3 * nWidth;
    int modVal = lineBytes % 4;
    if (modVal == 0) {//可以整除4
        fwrite(pRgbBuffer, lineBytes*nHeight, 1, fp1);
    } else {//不可整除4
        int addZeroCount = 4 - modVal;
        char *pZero = (char *) malloc(addZeroCount * sizeof (char));
        memset(pZero, 0, sizeof (char)*addZeroCount);
        for (int i = 0; i < nHeight; i++) {
            fwrite(pRgbBuffer + i*lineBytes, lineBytes, 1, fp1);
            fwrite(pZero, addZeroCount, 1, fp1);
        }
        free(pZero);
    }
    return 0;
}

bool readBmpInfo(const char* bmpFileName, BITMAPFILEHEADER& bitMapFileHeader, BITMAPINFOHEADER& bitMapInfoHeader) {
    //以二进制读方式打开指定的图像文件
    FILE* fp = fopen(bmpFileName, "rb");
    if (!fp) return false;
    //读位图文件头
    fread(&bitMapFileHeader, sizeof (BITMAPFILEHEADER), 1, fp);
    //读位图信息头
    fread(&bitMapInfoHeader, sizeof (BITMAPINFOHEADER), 1, fp);

    fclose(fp);

    return true;
}

bool readBmpData(const char* bmpFileName, TRGB* pRgbBuffer, unsigned long size) {
    if (pRgbBuffer == NULL)return false;
    //以二进制读方式打开指定的图像文件
    FILE* fp = fopen(bmpFileName, "rb");
    if (!fp) return false;
    BITMAPFILEHEADER bitMapFileHeader;
    BITMAPINFOHEADER bitMapInfoHeader;
    //获取文件头和文件信息
    //读位图文件头
    fread(&bitMapFileHeader, sizeof (BITMAPFILEHEADER), 1, fp);
    //读位图信息头
    fread(&bitMapInfoHeader, sizeof (BITMAPINFOHEADER), 1, fp);
    if (size < bitMapInfoHeader.biWidth * bitMapInfoHeader.biHeight
            || bitMapInfoHeader.biBitCount != 24) {//缓冲区大小不足或者不是24位图
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
    fseek(fp, bitMapFileHeader.bfOffBits, SEEK_SET);
    int lineBytes = 3 * bitMapInfoHeader.biWidth;
    int modVal = lineBytes % 4;
    if (modVal == 0) {//可以整除4
        unsigned long biSizeImage = (unsigned long) bitMapInfoHeader.biSizeImage;
        if (size * sizeof (TRGB) < biSizeImage) {
            fclose(fp);
            return false;
        }
        fread(pRgbBuffer, 1, biSizeImage, fp);
    } else {//不可整除4
        int addZeroCount = 4 - modVal;
        char *pZero = new char[addZeroCount];
        for (int i = 0; i < bitMapInfoHeader.biHeight; i++) {
            fread((char*) (pRgbBuffer) + i*lineBytes, 1, lineBytes, fp);
            fread(pZero, 1, addZeroCount, fp);
        }
        delete[] pZero;
    }

    //删除颜色表
    //if(pColorTable)delete[] pColorTable;
    fclose(fp);

    return true;
}