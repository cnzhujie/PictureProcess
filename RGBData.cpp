#include "RGBData.h"

RGBData::RGBData(unsigned long w,unsigned long h)
{
    m_w=w;
    m_h=h;
    m_pArr=new TRGB[m_w*m_h];
}
RGBData::RGBData(string fn)
{
    m_w=0;
    m_h=0;
    m_pArr=NULL;
    LoadFromFile(fn);
}

RGBData::~RGBData()
{
    delete[] m_pArr;
}

void RGBData::Init(TRGB& rgb)
{
    if(m_w==0 || m_h==0 || m_pArr==NULL)return;
    unsigned long size=m_w*m_h;
    for(unsigned long i=0;i<size;i++)
    {
        m_pArr[i].r=rgb.r;
        m_pArr[i].g=rgb.g;
        m_pArr[i].b=rgb.b;
    }
}

void RGBData::SetColor(unsigned long i,unsigned long j,TRGB& rgb)
{
    if(i>=m_w || j>=m_h || m_pArr==NULL)return;
    unsigned long pos=j*m_w+i;
    m_pArr[pos].r=rgb.r;
    m_pArr[pos].g=rgb.g;
    m_pArr[pos].b=rgb.b;
}

bool RGBData::SaveToFile(string fn)
{
    if(m_w==0 || m_h==0 || m_pArr==NULL)return false;
    FILE *fp=fopen(fn.c_str(),"wb");
    if(!fp)return false;
    RGB2BMP((char *)m_pArr,m_w,m_h,fp);
    fclose(fp);
    return true;
}
bool RGBData::LoadFromFile(string fn)
{
    if(m_pArr)delete[] m_pArr;
    m_w=0;
    m_h=0;
    m_pArr=NULL;

    BITMAPFILEHEADER bitMapFileHeader;
    BITMAPINFOHEADER bitMapInfoHeader;
    if(! readBmpInfo(fn.c_str(),bitMapFileHeader,bitMapInfoHeader) )return false;

    m_w = bitMapInfoHeader.biWidth;
    m_h = bitMapInfoHeader.biHeight;
    m_pArr=new TRGB[m_w*m_h];
    return readBmpData(fn.c_str(),m_pArr,m_w*m_h);
}
void RGBData::Overlap(const RGBData& another,TRGB& transparent)
{
    double wZoom = m_w / another.m_w;
    double hZoom = m_h / another.m_h;
    unsigned long pos,pos2;
    for(unsigned int i=0;i<another.m_w;i++)
    {
            for(unsigned int j=0;j<another.m_h;j++)
            {
                    pos = j*another.m_w+i;
                    pos2 = j*m_w*hZoom+i*wZoom;
                    if(another.m_pArr[pos] == transparent)continue;
                    m_pArr[pos2] = another.m_pArr[pos];
            }
    }
}
