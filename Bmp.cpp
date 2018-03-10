#include "Bmp.h"


/****************************
      RGB加上头部信息转换成BMP
    参数說明：
      rgb_buffer        :RGB数据文件中的信息
      nData             :RGB数据的长度
      nWidth            :图像宽度的像素数
      nHeight           :图像高度的像素数
      fp1               :所存放的文件
*****************************/
int RGB2BMP(char *rgb_buffer,int nWidth,int nHeight,FILE*fp1)
{
     BmpHead m_BMPHeader;
     char bfType[2]={'B','M'};
     m_BMPHeader.imageSize=3*nWidth*nHeight+54;
     m_BMPHeader.blank=0;
     m_BMPHeader.startPosition=54;

     fwrite(bfType,1,sizeof(bfType),fp1);
     fwrite(&m_BMPHeader.imageSize,1,sizeof(m_BMPHeader.imageSize),fp1);
     fwrite(&m_BMPHeader.blank,1,sizeof(m_BMPHeader.blank),fp1);
     fwrite(&m_BMPHeader.startPosition,1,sizeof(m_BMPHeader.startPosition),fp1);

     InfoHead  m_BMPInfoHeader;
     m_BMPInfoHeader.Length=40;
     m_BMPInfoHeader.width=nWidth;
     m_BMPInfoHeader.height=nHeight;
     m_BMPInfoHeader.colorPlane=1;
     m_BMPInfoHeader.bitColor=24;
     m_BMPInfoHeader.zipFormat=0;
     m_BMPInfoHeader.realSize=3*nWidth*nHeight;
     m_BMPInfoHeader.xPels=0;
     m_BMPInfoHeader.yPels=0;
     m_BMPInfoHeader.colorUse=0;
     m_BMPInfoHeader.colorImportant=0;

     fwrite(&m_BMPInfoHeader.Length,1,sizeof(m_BMPInfoHeader.Length),fp1);
     fwrite(&m_BMPInfoHeader.width,1,sizeof(m_BMPInfoHeader.width),fp1);
     fwrite(&m_BMPInfoHeader.height,1,sizeof(m_BMPInfoHeader.height),fp1);
     fwrite(&m_BMPInfoHeader.colorPlane,1,sizeof(m_BMPInfoHeader.colorPlane),fp1);
     fwrite(&m_BMPInfoHeader.bitColor,1,sizeof(m_BMPInfoHeader.bitColor),fp1);
     fwrite(&m_BMPInfoHeader.zipFormat,1,sizeof(m_BMPInfoHeader.zipFormat),fp1);
     fwrite(&m_BMPInfoHeader.realSize,1,sizeof(m_BMPInfoHeader.realSize),fp1);
     fwrite(&m_BMPInfoHeader.xPels,1,sizeof(m_BMPInfoHeader.xPels),fp1);
     fwrite(&m_BMPInfoHeader.yPels,1,sizeof(m_BMPInfoHeader.yPels),fp1);
     fwrite(&m_BMPInfoHeader.colorUse,1,sizeof(m_BMPInfoHeader.colorUse),fp1);
     fwrite(&m_BMPInfoHeader.colorImportant,1,sizeof(m_BMPInfoHeader.colorImportant),fp1);
     //因为BMP格式规定图像每一行所占的字节数必须是4的倍数，如果不是4的倍数就要用0填充。
     //例如你一行是25像素，24位图每个像素3节字，那25像素就是25*3=75字节，75不是4的倍数，比75大的，并且是4的倍数最接近的就是76了，所以一行要填充到76个字节，也就是每一行后面要多加一个没用的字节
     int lineBytes=3*nWidth;
     int modVal=lineBytes % 4;
     if( modVal == 0)
     {//可以整除4
        fwrite(rgb_buffer,lineBytes*nHeight,1,fp1);
     }
     else
     {//不可整除4
        int addZeroCount=4-modVal;
        char *pZero=(char *)malloc(addZeroCount*sizeof(char));
        memset(pZero,0,sizeof(char)*addZeroCount);
        for(int i=0;i<nHeight;i++)
        {
            fwrite(rgb_buffer+i*lineBytes,lineBytes,1,fp1);
            fwrite(pZero,addZeroCount,1,fp1);
        }
        free(pZero);
     }
     return 0;
}



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