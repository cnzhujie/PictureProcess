#include "RGBData.h"

RGBData::RGBData(unsigned long w, unsigned long h) {
    this->w = w;
    this->h = h;
    this->pArr = new TRGB[this->w * this->h];
}

RGBData::RGBData(string fn) {
    this->w = 0;
    this->h = 0;
    this->pArr = NULL;
    loadFromFile(fn);
}

RGBData::~RGBData() {
    delete[] this->pArr;
}

void RGBData::init(TRGB& rgb) {
    if (this->w == 0 || this->h == 0 || this->pArr == NULL)return;
    unsigned long size = this->w * this->h;
    for (unsigned long i = 0; i < size; i++) {
        this->pArr[i].r = rgb.r;
        this->pArr[i].g = rgb.g;
        this->pArr[i].b = rgb.b;
    }
}

void RGBData::setColor(unsigned long i, unsigned long j, TRGB& rgb) {
    if (i >= this->w || j >= this->h || this->pArr == NULL)return;
    unsigned long pos = j * this->w + i;
    this->pArr[pos].r = rgb.r;
    this->pArr[pos].g = rgb.g;
    this->pArr[pos].b = rgb.b;
}

bool RGBData::saveToFile(string fn) {
    if (this->w == 0 || this->h == 0 || this->pArr == NULL)return false;
    FILE *fp = fopen(fn.c_str(), "wb");
    if (!fp)return false;
    saveRgbToBmpFile((char *) this->pArr, this->w, this->h, fp);
    fclose(fp);
    return true;
}

bool RGBData::loadFromFile(string fn) {
    if (this->pArr)delete[] this->pArr;
    this->w = 0;
    this->h = 0;
    this->pArr = NULL;

    BITMAPFILEHEADER bitMapFileHeader;
    BITMAPINFOHEADER bitMapInfoHeader;
    if (!readBmpInfo(fn.c_str(), bitMapFileHeader, bitMapInfoHeader))return false;

    this->w = bitMapInfoHeader.biWidth;
    this->h = bitMapInfoHeader.biHeight;
    this->pArr = new TRGB[this->w * this->h];
    return readBmpData(fn.c_str(), this->pArr, this->w * this->h);
}

void RGBData::overlap(const RGBData& another, TRGB& transparent) {
    double wZoom = this->w / another.w;
    double hZoom = this->h / another.h;
    unsigned long pos, pos2;
    for (unsigned int i = 0; i < another.w; i++) {
        for (unsigned int j = 0; j < another.h; j++) {
            pos = j * another.w + i;
            pos2 = j * this->w * hZoom + i*wZoom;
            if (another.pArr[pos] == transparent)continue;
            this->pArr[pos2] = another.pArr[pos];
        }
    }
}
