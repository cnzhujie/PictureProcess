//============================================================================
// Name        : Main.cpp
// Author      : zhujie
//============================================================================

#include <iostream>
#include <string>
using namespace std;
#include "RGBData.h"
#include "Clock.h"

typedef bool (*PicOverlapIsTranColorFunc)(TRGB&);
void overlap(string bk, string front, string save, TRGB& tran);
void overlap(string bk, string front, string save, PicOverlapIsTranColorFunc pPicOverlapIsTranColorFunc);
void overlap(string bk, string front, string save, PicOverlapIsTranColorFunc pPicOverlapIsTranColorFunc, TRGB* pTran);


#define LR_FLIP 1       //左右翻转
#define TD_FLIP 2       //上下翻转
#define CENTER_FLIP 3   //中心翻转
#define PI          3.1415926
void flip(string pic, string save, int flipType);
void flipAngle(string pic, string save, double angle, TRGB blankColor = TRGB(255, 255, 255));

void colorReplace(string pic, string save, TRGB& from, TRGB& to);
typedef void (*ColorReplaceFunc)(TRGB&);
void colorReplace(string pic, string save, ColorReplaceFunc pColorReplaceFunc);

void colorToGray(TRGB& t);
void pictureToGray(string pic, string save);

void scaleBrightness(string pic, string save, double zoomLevel);
void stepBrightness(string pic, string save, char step);

void tuneHue(string pic, string save, char bStep, char gStep, char rStep);

void inverseColor(string pic, string save);

void singleColor(string pic, string save, char onlyKeepColor);

void zoomToLinear(string pic, string save, double percent);
void zoomToLinear(string pic, string save, double wPercent, double hPercent);
void zoomTo(string pic, string save, double percent);
void zoomTo(string pic, string save, double wPercent, double hPercent);

void circularShift(string pic, string save, int wShift, int hShift);

void binaryzationOtsu(string pic, string save);
void binaryzationBernsen(string pic, string save, unsigned char globalThreshold, unsigned char maxNearDistance = 15);
void binaryzation(string pic, string save, unsigned char threshold);

void smooth(string pic, string save);

void neon(string pic, string save);

void sharpen(string pic, string save);
void sharpen(string pic, string save, double ratio);

void cameo(string pic, string save);
void cameo(string pic, string save, char add);

int main() {
    string picDir = "/Users/kaiji/workspace/cnzhujie/PictureProcess/pic/";
    Clock c;

    c.start();
    ///////////////////////////////////////////////////////////////
    //左右镜像旋转
    flip(picDir + "source.bmp", picDir + "flip_LR.bmp", LR_FLIP);
    //上下镜像旋转
    flip(picDir + "source.bmp", picDir + "flip_TD.bmp", TD_FLIP);
    //中心点镜像旋转
    flip(picDir + "source.bmp", picDir + "flip_CENTER.bmp", CENTER_FLIP);

    //以中心点逆时针任意角度旋转
    flipAngle(picDir + "source.bmp", picDir + "flip_ANGLE_90.bmp", 90);
    flipAngle(picDir + "source.bmp", picDir + "flip_ANGLE_20.bmp", 20);
    flipAngle(picDir + "source.bmp", picDir + "flip_ANGLE_135.bmp", 135);
    flipAngle(picDir + "source.bmp", picDir + "flip_ANGLE_180.bmp", 180);
    flipAngle(picDir + "source.bmp", picDir + "flip_ANGLE_280.bmp", 280);

    //图片叠加
    TRGB tran(255, 255, 255); //透明色
    overlap(picDir + "back.bmp", picDir + "front.bmp", picDir + "overlap.bmp", tran);

    //颜色替换
    TRGB from(0, 0, 0), to(255, 255, 255);
    colorReplace(picDir + "front.bmp", picDir + "blackToWhite.bmp", from, to);

    //彩色图像转化为灰色图像
    colorReplace(picDir + "source.bmp", picDir + "gray1.bmp", colorToGray);
    pictureToGray(picDir + "source.bmp", picDir + "gray.bmp");

    //更改亮度
    scaleBrightness(picDir + "brightness.bmp", picDir + "scalelight.bmp", 1.2);
    scaleBrightness(picDir + "brightness.bmp", picDir + "scaledark.bmp", 0.5);
    stepBrightness(picDir + "brightness.bmp", picDir + "steplight.bmp", 30);
    stepBrightness(picDir + "brightness.bmp", picDir + "stepdark.bmp", -30);

    //更改色调
    tuneHue(picDir + "brightness.bmp", picDir + "tuneHue_30_-20_-10.bmp", 30, -20, -10);
    tuneHue(picDir + "brightness.bmp", picDir + "tuneHue_-30_20_10.bmp", -30, 20, 10);
    tuneHue(picDir + "brightness.bmp", picDir + "tuneHue_30_-20_10.bmp", 30, -20, 10);

    //颜色反转
    inverseColor(picDir + "source.bmp", picDir + "inverseColor.bmp");

    //图片单色化
    singleColor(picDir + "source.bmp", picDir + "singleColor_r.bmp", 'r');
    singleColor(picDir + "source.bmp", picDir + "singleColor_g.bmp", 'g');
    singleColor(picDir + "source.bmp", picDir + "singleColor_b.bmp", 'b');

    //图片缩放
    zoomTo(picDir + "brightness.bmp", picDir + "zoomTo0.8.bmp", 0.8);
    zoomTo(picDir + "brightness.bmp", picDir + "zoomTo1.8.bmp", 1.8);
    zoomToLinear(picDir + "brightness.bmp", picDir + "zoomToLinear0.8.bmp", 0.8);
    zoomToLinear(picDir + "brightness.bmp", picDir + "zoomToLinear1.8.bmp", 1.8);

    //循环移位
    circularShift(picDir + "source.bmp", picDir + "circularShift_100_0.bmp", 100, 0);
    circularShift(picDir + "source.bmp", picDir + "circularShift_0_-100.bmp", 0, -100);
    circularShift(picDir + "source.bmp", picDir + "circularShift_100_-100.bmp", 100, -100);

    //二值化
    binaryzationOtsu(picDir + "brightness.bmp", picDir + "brightness_otsn.bmp");
    binaryzation(picDir + "brightness.bmp", picDir + "brightness_binaryzation.bmp", 128);
    binaryzationOtsu(picDir + "source.bmp", picDir + "source_otsn.bmp");
    binaryzation(picDir + "source.bmp", picDir + "source_binaryzation.bmp", 128);
    binaryzationOtsu(picDir + "front.bmp", picDir + "front_otsn.bmp");
    binaryzation(picDir + "front.bmp", picDir + "front_binaryzation.bmp", 10);

    //平滑
    smooth(picDir + "brightness.bmp", picDir + "smooth.bmp");

    //霓虹处理
    neon(picDir + "brightness.bmp", picDir + "brightness_neon.bmp");
    neon(picDir + "source.bmp", picDir + "source_neon.bmp");
    neon(picDir + "front.bmp", picDir + "front_neon.bmp");

    //锐化处理
    sharpen(picDir + "brightness.bmp", picDir + "brightness_sharpen.bmp", 0.25);
    sharpen(picDir + "source.bmp", picDir + "source_sharpen.bmp", 0.25);
    sharpen(picDir + "front.bmp", picDir + "front_sharpen.bmp", 0.25);

    //锐化处理
    cameo(picDir + "brightness.bmp", picDir + "brightness_cameo.bmp", 128);
    cameo(picDir + "source.bmp", picDir + "source_cameo.bmp", 128);
    cameo(picDir + "front.bmp", picDir + "front_cameo.bmp", 128);

    c.end();

    cout << "Total time: " << c.strTime() << endl;
    return 0;
}

/**
 * 替换图片中的指定颜色为其他颜色
 * @param pic
 * @param save
 * @param from
 * @param to
 */
void colorReplace(string pic, string save, TRGB& from, TRGB& to) {
    RGBData *pBmp = new RGBData(pic);

    long w = pBmp->getW();
    long h = pBmp->getH();
    TRGB* pArr = pBmp->getArr();
    long s = w*h;
    for (long i = 0; i < s; i++) {
        if (pArr[i] == from) {
            pArr[i] = to;
        }
    }
    //保存
    pBmp->saveToFile(save);

    delete pBmp;
}

/**
 * 按照规定规则替换图片中的颜色
 * @param pic
 * @param save
 * @param pColorReplaceFunc
 */
void colorReplace(string pic, string save, ColorReplaceFunc pColorReplaceFunc) {
    RGBData *pBmp = new RGBData(pic);

    long w = pBmp->getW();
    long h = pBmp->getH();
    TRGB* pArr = pBmp->getArr();
    long s = w*h;
    for (long i = 0; i < s; i++) {
        pColorReplaceFunc(pArr[i]);
    }
    //保存
    pBmp->saveToFile(save);

    delete pBmp;
}

/**
 * 将某个彩色的颜色值转化为灰度
 * @param t
 */
void colorToGray(TRGB& t) {
    static unsigned char gray;
    gray = (t.r * 299 + t.g * 587 + t.b * 114 + 500) / 1000;
    t.r = gray;
    t.b = gray;
    t.g = gray;
}

/**
 * 将某副图像转化位灰度图像
 * @param pic
 * @param save
 */
void pictureToGray(string pic, string save) {
    colorReplace(pic, save, colorToGray);
}

/**
 * 图片翻转
 * @param pic
 * @param save
 * @param flipType
 */
void flip(string pic, string save, int flipType) {
    RGBData *pBmp = new RGBData(pic);

    long w = pBmp->getW();
    long h = pBmp->getH();
    TRGB t;
    TRGB* pArr = pBmp->getArr();

    if (flipType == CENTER_FLIP) {
        long s = w * h - 1;
        for (long i = 0; i <= s / 2; i++) {
            t = pArr[i];
            pArr[i] = pArr[s - i];
            pArr[s - i] = t;
        }
    } else if (flipType == LR_FLIP) {
        long w2 = w / 2;
        long n1, n2;
        for (long i = 0; i < h; i++) {
            for (long j = 0; j <= w2; j++) {
                n1 = i * w + j;
                n2 = i * w + w - 1 - j;
                t = pArr[n1];
                pArr[n1] = pArr[n2];
                pArr[n2] = t;
            }
        }
    } else if (flipType == TD_FLIP) {
        long h2 = h / 2;
        long n1, n2;
        for (long i = 0; i <= h2; i++) {
            for (long j = 0; j < w; j++) {
                n1 = i * w + j;
                n2 = (h - 1 - i) * w + j;
                t = pArr[n1];
                pArr[n1] = pArr[n2];
                pArr[n2] = t;
            }
        }
    }

    //保存
    pBmp->saveToFile(save);

    delete pBmp;
}

/**
 * 以任意角度旋转图像(there is something wrong. Bugs...)
 * @param pic
 * @param save
 * @param angle 逆时针角度
 */
void flipAngle(string pic, string save, double angle, TRGB blankColor) {
    if (angle <= 0 || angle >= 360)return;
    if (angle == 180) {
        flip(pic, save, CENTER_FLIP);
        return;
    }

    RGBData *pBmpOld = new RGBData(pic);
    RGBData *pBmpNew = NULL;

    //原图象宽度,高度
    long lOldWidth = pBmpOld->getW();
    long lOldHeight = pBmpOld->getH();
    //旋转角度的弧度
    double fArcAngle = (angle * PI) / 180.0;
    ;
    double fSin, fCos;
    if (angle == 90) {
        fSin = 1;
        fCos = 0;
    } else if (angle == 270) {
        fSin = -1;
        fCos = 0;
    } else {
        fSin = sin(fArcAngle);
        fCos = cos(fArcAngle);
    }

    //计算原图的四个角的坐标（以图像中心为坐标系原点）
    double fSrcX1 = (double) (-(lOldWidth) / 2.0);
    double fSrcY1 = (double) ((lOldHeight) / 2.0);
    double fSrcX2 = (double) ((lOldWidth) / 2.0);
    double fSrcY2 = (double) ((lOldHeight) / 2.0);
    double fSrcX3 = (double) (-(lOldWidth) / 2.0);
    double fSrcY3 = (double) (-(lOldHeight) / 2.0);
    double fSrcX4 = (double) ((lOldWidth) / 2.0);
    double fSrcY4 = (double) (-(lOldHeight) / 2.0);

    //计算新图四个角的坐标（以图像中心为坐标系原点）
    double fDstX1 = fCos * fSrcX1 + fSin * fSrcY1;
    double fDstY1 = -fSin * fSrcX1 + fCos * fSrcY1;
    double fDstX2 = fCos * fSrcX2 + fSin * fSrcY2;
    double fDstY2 = -fSin * fSrcX2 + fCos * fSrcY2;
    double fDstX3 = fCos * fSrcX3 + fSin * fSrcY3;
    double fDstY3 = -fSin * fSrcX3 + fCos * fSrcY3;
    double fDstX4 = fCos * fSrcX4 + fSin * fSrcY4;
    double fDstY4 = -fSin * fSrcX4 + fCos * fSrcY4;

    //计算旋转后的图像实际宽度
    long lNewWidth = (long) (max(fabs(fDstX4 - fDstX1),
            fabs(fDstX3 - fDstX2)) + 0.5);

    //计算旋转后的图像高度
    long lNewHeight = (long) (max(fabs(fDstY4 - fDstY1),
            fabs(fDstY3 - fDstY2)) + 0.5);

    pBmpNew = new RGBData(lNewWidth, lNewHeight);
    pBmpNew->init(blankColor);
    unsigned long posNew, iOld, jOld;
    double diOld, djOld, u, v;
    double xNew, yNew;
    TRGB rgb, *pRgb1, *pRgb2, *pRgb3, *pRgb4;
    TRGB* pArrOld = pBmpOld->getArr();
    //旋转图像每列
    for (unsigned long iNew = 0; iNew < lNewWidth; iNew++) {
        //旋转图象每行
        for (unsigned long jNew = 0; jNew < lNewHeight; jNew++) {
            posNew = jNew * lNewWidth + iNew;
            //坐标
            xNew = iNew - lNewWidth / 2.0;
            yNew = lNewHeight / 2.0 - jNew;
            //计算每个像素点在原图象中的坐标
            diOld = (lOldWidth + 2 * (xNew * fCos - yNew * fSin)) / 2.0;
            djOld = (lOldHeight - 2 * (xNew * fSin + yNew * fCos)) / 2.0;

            iOld = diOld;
            jOld = djOld;

            u = diOld - iOld;
            v = djOld - jOld;
            if (iOld < 0 || iOld >= lOldWidth || jOld < 0 || jOld >= lOldHeight)continue;

            pRgb1 = pArrOld + jOld * lOldWidth + iOld;
            pRgb2 = pRgb3 = pRgb4 = pRgb1;
            if (jOld < lOldHeight - 1) {
                pRgb2 = pArrOld + (jOld + 1) * lOldWidth + iOld;
            }
            if (iOld < lOldWidth - 1) {
                pRgb3 = pArrOld + jOld * lOldWidth + iOld + 1;
            }
            if (jOld < lOldHeight - 1 && iOld < lOldWidth - 1) {
                pRgb4 = pArrOld + (jOld + 1) * lOldWidth + iOld + 1;
            }
            //双线性内插值
            rgb.b = (1 - u)*(1 - v) * pRgb1->b + (1 - u) * v * pRgb2->b + u * (1 - v) * pRgb3->b + u * v * pRgb4->b;
            rgb.g = (1 - u)*(1 - v) * pRgb1->g + (1 - u) * v * pRgb2->g + u * (1 - v) * pRgb3->g + u * v * pRgb4->g;
            rgb.r = (1 - u)*(1 - v) * pRgb1->r + (1 - u) * v * pRgb2->r + u * (1 - v) * pRgb3->r + u * v * pRgb4->r;

            pBmpNew->getArr()[posNew] = rgb;
        }
    }

    //保存
    if (pBmpNew)pBmpNew->saveToFile(save);
    if (pBmpNew)delete pBmpNew;
    delete pBmpOld;
}

/**
 * 两张图片按照背景色叠加
 * @param bk
 * @param front
 * @param tran  背景透明颜色
 * @param save
 */
void overlap(string bk, string front, string save, TRGB& tran) {
    overlap(bk, front, save, NULL, &tran);
}

/**
 * 两张图片叠加，背景透明颜色按照指定规则进行指定
 * @param bk
 * @param front
 * @param save
 * @param pPicOverlapIsTranColorFunc    背景透明颜色判断规则
 */
void overlap(string bk, string front, string save, PicOverlapIsTranColorFunc pPicOverlapIsTranColorFunc) {
    overlap(bk, front, save, pPicOverlapIsTranColorFunc, NULL);
}

/**
 * 
 * @param bk
 * @param front
 * @param save
 * @param pPicOverlapIsTranColorFunc
 * @param pTran
 */
void overlap(string bk, string front, string save, PicOverlapIsTranColorFunc pPicOverlapIsTranColorFunc, TRGB* pTran) {
    RGBData *pBmpBk = new RGBData(bk);
    RGBData *pBmpFront = new RGBData(front);

    //合并
    double wZoom = pBmpBk->getW() / pBmpFront->getW();
    double hZoom = pBmpBk->getH() / pBmpFront->getH();
    unsigned long pos, pos2;
    for (unsigned int i = 0; i < pBmpFront->getW(); i++) {
        for (unsigned int j = 0; j < pBmpFront->getH(); j++) {
            pos = j * pBmpFront->getW() + i;
            pos2 = j * pBmpBk->getW() * hZoom + i*wZoom;
            if (pPicOverlapIsTranColorFunc) {//透明颜色判别函数
                if (pPicOverlapIsTranColorFunc(pBmpFront->getArr()[pos])) {
                    continue;
                }
            } else if (pTran) {//判断是否等于透明色
                if (pBmpFront->getArr()[pos] == *pTran) {
                    continue;
                }
            }
            pBmpBk->getArr()[pos2] = pBmpFront->getArr()[pos];
        }
    }

    //保存
    pBmpBk->saveToFile(save);

    delete pBmpBk;
    delete pBmpFront;
}

/**
 * 按比例调节图片亮度（对有些图片效果不好）
 * @param pic
 * @param save
 * @param zoomLevel     调节到原来亮度的比例，小于1变暗，大于1变亮
 */
void scaleBrightness(string pic, string save, double scaleLevel) {
    RGBData *pBmp = new RGBData(pic);

    long w = pBmp->getW();
    long h = pBmp->getH();
    double Y, U, V;
    long r, g, b;
    TRGB* pArr = pBmp->getArr();
    long s = w*h;
    for (long i = 0; i < s; i++) {
        //rgb转yuv
        Y = 0.299 * pArr[i].r + 0.587 * pArr[i].g + 0.114 * pArr[i].b;
        U = (1 / 2.032)*(pArr[i].b - Y);
        V = (1 / 1.140)*(pArr[i].r - Y);
        //调整Y值,调整亮度
        Y = Y*scaleLevel;
        if (Y > 255)Y = 255;
        //在将YUV转成rgb
        r = Y + 1.140 * V;
        g = Y - (0.114 * 2.032 / 0.587) * U - (0.299 * 1.140 / 0.587) * V;
        b = Y + 2.032 * U;
        pArr[i].r = (r < 0) ? 0 : (r > 255 ? 255 : r);
        pArr[i].g = (g < 0) ? 0 : (g > 255 ? 255 : g);
        pArr[i].b = (b < 0) ? 0 : (b > 255 ? 255 : b);
    }
    //保存
    pBmp->saveToFile(save);

    delete pBmp;
}

/**
 * 增加或减少图片亮度
 * @param pic
 * @param save
 * @param step  增加或减少的亮度值,正值为增加亮度，负值减少亮度
 */
void stepBrightness(string pic, string save, char step) {
    tuneHue(pic, save, step, step, step);
}

/**
 * 更改色调
 * @param pic
 * @param save
 * @param bStep
 * @param gStep
 * @param rStep
 */
void tuneHue(string pic, string save, char bStep, char gStep, char rStep) {
    RGBData *pBmp = new RGBData(pic);

    long w = pBmp->getW();
    long h = pBmp->getH();
    TRGB* pArr = pBmp->getArr();
    long s = w*h;
    long r, g, b;
    for (long i = 0; i < s; i++) {
        r = pArr[i].r + rStep;
        g = pArr[i].g + gStep;
        b = pArr[i].b + bStep;
        pArr[i].r = (r < 0) ? 0 : (r > 255 ? 255 : r);
        pArr[i].g = (g < 0) ? 0 : (g > 255 ? 255 : g);
        pArr[i].b = (b < 0) ? 0 : (b > 255 ? 255 : b);
    }
    //保存
    pBmp->saveToFile(save);

    delete pBmp;
}

/**
 * 反色
 * @param pic
 * @param save
 */
void inverseColor(string pic, string save) {
    RGBData *pBmp = new RGBData(pic);

    long w = pBmp->getW();
    long h = pBmp->getH();
    TRGB* pArr = pBmp->getArr();
    long s = w*h;
    for (long i = 0; i < s; i++) {
        pArr[i].r = 255 - pArr[i].r;
        pArr[i].g = 255 - pArr[i].g;
        pArr[i].b = 255 - pArr[i].b;
    }
    //保存
    pBmp->saveToFile(save);

    delete pBmp;
}

/**
 * 图片单色化
 * @param pic
 * @param save
 * @param onlyKeepColor
 */
void singleColor(string pic, string save, char onlyKeepColor) {
    RGBData *pBmp = new RGBData(pic);

    long w = pBmp->getW();
    long h = pBmp->getH();
    TRGB* pArr = pBmp->getArr();
    long s = w*h;
    for (long i = 0; i < s; i++) {
        if (onlyKeepColor == 'r') {
            pArr[i].g = pArr[i].r;
            pArr[i].b = pArr[i].r;
        } else if (onlyKeepColor == 'g') {
            pArr[i].r = pArr[i].g;
            pArr[i].b = pArr[i].g;
        } else if (onlyKeepColor == 'b') {
            pArr[i].r = pArr[i].b;
            pArr[i].g = pArr[i].b;
        }
    }
    //保存
    pBmp->saveToFile(save);

    delete pBmp;
}

/**
 * 采用线性插值将图片缩放到原来尺寸的百分之多少
 * @param pic
 * @param save
 * @param percent
 */
void zoomToLinear(string pic, string save, double percent) {
    zoomToLinear(pic, save, percent, percent);
}

void zoomToLinear(string pic, string save, double wPercent, double hPercent) {
    RGBData *pBmpOld = new RGBData(pic);

    unsigned long wOld = pBmpOld->getW();
    unsigned long hOld = pBmpOld->getH();
    unsigned long wNew = wOld*wPercent;
    unsigned long hNew = hOld*hPercent;
    RGBData *pBmpNew = new RGBData(wNew, hNew);

    double diOld, djOld, u, v;
    unsigned long iOld, jOld;
    TRGB rgb, *pRgb1, *pRgb2, *pRgb3, *pRgb4;
    TRGB* pArrOld = pBmpOld->getArr();
    for (unsigned long iNew = 0; iNew < wNew; iNew++) {
        for (unsigned long jNew = 0; jNew < hNew; jNew++) {
            diOld = iNew / wPercent;
            djOld = jNew / hPercent;
            iOld = diOld;
            jOld = djOld;
            u = diOld - iOld;
            v = djOld - jOld;
            if (iOld >= wOld || jOld >= hOld)continue;

            pRgb1 = pArrOld + jOld * wOld + iOld;
            pRgb2 = pRgb3 = pRgb4 = pRgb1;
            if (jOld < hOld - 1) {
                pRgb2 = pArrOld + (jOld + 1) * wOld + iOld;
            }
            if (iOld < wOld - 1) {
                pRgb3 = pArrOld + jOld * wOld + iOld + 1;
            }
            if (jOld < hOld - 1 && iOld < wOld - 1) {
                pRgb4 = pArrOld + (jOld + 1) * wOld + iOld + 1;
            }
            //双线性内插值
            rgb.b = (1 - u)*(1 - v) * pRgb1->b + (1 - u) * v * pRgb2->b + u * (1 - v) * pRgb3->b + u * v * pRgb4->b;
            rgb.g = (1 - u)*(1 - v) * pRgb1->g + (1 - u) * v * pRgb2->g + u * (1 - v) * pRgb3->g + u * v * pRgb4->g;
            rgb.r = (1 - u)*(1 - v) * pRgb1->r + (1 - u) * v * pRgb2->r + u * (1 - v) * pRgb3->r + u * v * pRgb4->r;

            pBmpNew->getArr()[jNew * wNew + iNew] = rgb;
        }
    }

    pBmpNew->saveToFile(save);
    delete pBmpOld;
    delete pBmpNew;
}

/**
 * 将图片缩放到原来尺寸的百分之多少
 * @param pic
 * @param save
 * @param percent
 */
void zoomTo(string pic, string save, double percent) {
    zoomTo(pic, save, percent, percent);
}

void zoomTo(string pic, string save, double wPercent, double hPercent) {
    RGBData *pBmpOld = new RGBData(pic);

    unsigned long wOld = pBmpOld->getW();
    unsigned long hOld = pBmpOld->getH();
    unsigned long wNew = wOld*wPercent;
    unsigned long hNew = hOld*hPercent;
    RGBData *pBmpNew = new RGBData(wNew, hNew);

    unsigned long iOld, jOld;
    TRGB* pArrOld = pBmpOld->getArr();
    for (unsigned long iNew = 0; iNew < wNew; iNew++) {
        for (unsigned long jNew = 0; jNew < hNew; jNew++) {
            iOld = iNew / wPercent;
            jOld = jNew / hPercent;

            pBmpNew->getArr()[jNew * wNew + iNew] = pArrOld[jOld * wOld + iOld];
        }
    }

    pBmpNew->saveToFile(save);
    delete pBmpNew;
    delete pBmpOld;
}

/**
 * 循环位移
 * @param pic
 * @param save
 * @param wShift
 * @param hShift
 */
void circularShift(string pic, string save, int wShift, int hShift) {
    if (wShift == 0 && hShift == 0)return;
    RGBData *pBmpOld = new RGBData(pic);
    unsigned long w = pBmpOld->getW();
    unsigned long h = pBmpOld->getH();
    RGBData *pBmpNew = new RGBData(w, h);
    //如果位移像素超过图片宽度或高度，转换成之内的值
    if (wShift > 0) {
        wShift = wShift % w;
    } else {
        long w2 = -1 * w;
        while (wShift <= w2) {
            wShift += w;
        }
    }
    if (hShift > 0) {
        hShift = hShift % h;
    } else {
        long h2 = -1 * h;
        while (hShift <= h2) {
            hShift += h;
        }
    }
    //
    long iNew, jNew;
    for (unsigned long iOld = 0; iOld < w; iOld++) {
        for (unsigned long jOld = 0; jOld < h; jOld++) {
            iNew = (iOld + wShift + w) % w;
            jNew = (jOld + hShift + h) % h;
            pBmpNew->getArr()[jNew * w + iNew] = pBmpOld->getArr()[jOld * w + iOld];
        }
    }
    //保存
    pBmpNew->saveToFile(save);
    delete pBmpNew;
    delete pBmpOld;
}

/**
 * 图像二值化
 * @param pic
 * @param save
 * @param type
 */
void binaryzationOtsu(string pic, string save) {
    RGBData *pBmp = new RGBData(pic);
    unsigned long w = pBmp->getW();
    unsigned long h = pBmp->getH();
    TRGB* pArr = pBmp->getArr(), *pRgb;


    int thresholdValue = 1; // 阈值
    int ihist[256]; // 图像直方图，256个点
    // 对直方图置零
    memset(ihist, 0, sizeof (ihist));
    for (unsigned long j = 0; j < h; j++) {
        for (unsigned long i = 0; i < w; i++) {
            pRgb = pArr + j * w + i;
            colorToGray(*pRgb); //转化为灰度颜色
            ihist[pRgb->b]++;
        }
    }

    // set up everything
    double sum = 0.0;
    int n = 0;
    for (int k = 0; k <= 255; k++) {
        sum += (double) k * (double) ihist[k]; /**//* x*f(x) 质量矩*/
        n += ihist[k]; /**//* f(x) 质量 */
    }

    if (!n) {
        // if n has no value, there is problems
        //fprintf(stderr, "NOT NORMAL thresholdValue = 160\n");
        thresholdValue = 160;
    } else {
        // do the otsu global thresholding method
        double m1, m2, fmax = -1.0, csum, sb;
        int n1 = 0, n2;
        for (int k = 0; k < 255; k++) {
            n1 += ihist[k];
            if (!n1) {
                continue;
            }
            n2 = n - n1;
            if (n2 == 0) {
                break;
            }
            csum += (double) k * ihist[k];
            m1 = csum / n1;
            m2 = (sum - csum) / n2;
            sb = (double) n1 * (double) n2 * (m1 - m2) * (m1 - m2);
            /**//* bbg: note: can be optimized. */
            if (sb > fmax) {
                fmax = sb;
                thresholdValue = k;
            }
        }
    }
    //二值化
    long s = w*h;
    for (long i = 0; i < s; i++) {
        pRgb = pArr + i;
        if (pRgb->b >= thresholdValue) {
            pRgb->b = pRgb->g = pRgb->r = 255;
        } else {
            pRgb->b = pRgb->g = pRgb->r = 0;
        }
    }
    //保存
    pBmp->saveToFile(save);

    delete pBmp;
}

/**
 * 
 * @param pic
 * @param save
 */
void binaryzationBernsen(string pic, string save, unsigned char globalThreshold, unsigned char maxNearDistance) {
    RGBData *pBmpOld = new RGBData(pic);

    int i = 0, j = 0, k = 0, l = 0, maximum = 0, minor = 0, mid_gray = 0;
    int upleft = 0, upright = 0, downleft = 0, downright = 0;
    unsigned long wide = pBmpOld->getW();
    unsigned long high = pBmpOld->getH();
    unsigned long pos;

    //图片灰度化
    RGBData *pBmpNew = new RGBData(wide, high);
    TRGB *pArrOld = pBmpOld->getArr(), *pArrNew = pBmpNew->getArr(), *pRgb;
    for (j = 0; j < high; j++) {
        for (i = 0; i < wide; i++) {
            pRgb = pArrOld + j * wide + i;
            colorToGray(*pRgb); //转化为灰度颜色
        }
    }
    //遍历所有像素
    for (j = 0; j < high; j++) {
        for (i = 0; i < wide; i++) {
            //求出周围区块像素的最大值和最小值
            maximum = 0, minor = 255;
            upleft = (i - 15) > 0 ? (i - 15) : 0;
            upright = (i + 15) < wide ? (i + 15) : (wide - 1);
            downleft = (j - 15) > 0 ? (j - 15) : 0;
            downright = (j + 15) < high ? (j + 15) : (high - 1);
            for (k = downright; k <= downright; k++) {
                for (l = upleft; l <= upright; l++) {
                    pos = l * high + k;
                    if (pArrOld[pos].b >= maximum) {
                        maximum = pArrOld[pos].b;
                    } else if (pArrOld[pos].b <= minor) {
                        minor = pArrOld[pos].b;
                    }
                }
            }

            pos = i * high + j;
            mid_gray = (maximum + minor) >> 1;
            //本像素周围区块的像素相差较大
            if ((maximum - minor) > maxNearDistance) {
                if (pArrNew[pos].b >= mid_gray) {
                    pArrNew[pos].b = pArrNew[pos].g = pArrNew[pos].r = 255;
                } else {
                    pArrNew[pos].b = pArrNew[pos].g = pArrNew[pos].r = 0;
                }
            } else {
                if (mid_gray >= globalThreshold) {
                    pArrNew[pos].b = pArrNew[pos].g = pArrNew[pos].r = 255;
                } else {
                    pArrNew[pos].b = pArrNew[pos].g = pArrNew[pos].r = 0;
                }
            }
        }
    }

    pBmpNew->saveToFile(save);
    delete pBmpNew;
    delete pBmpOld;
}

/**
 * 
 * @param pic
 * @param save
 * @param threshold
 */
void binaryzation(string pic, string save, unsigned char threshold) {
    RGBData *pBmp = new RGBData(pic);
    TRGB *pRgb, *pArr = pBmp->getArr();
    unsigned long w = pBmp->getW();
    unsigned long h = pBmp->getH();
    long s = w*h;
    for (long i = 0; i < s; i++) {
        pRgb = pArr + i;
        colorToGray(*pRgb); //转化为灰度颜色
        if (pRgb->b >= threshold) {
            pRgb->b = pRgb->g = pRgb->r = 255;
        } else {
            pRgb->b = pRgb->g = pRgb->r = 0;
        }
    }
    //保存
    pBmp->saveToFile(save);

    delete pBmp;
}

/**
 * 图像平滑
 * @param pic
 * @param save
 */
void smooth(string pic, string save) {
    RGBData *pBmp = new RGBData(pic);
    TRGB *pArr = pBmp->getArr();
    unsigned long w = pBmp->getW();
    unsigned long h = pBmp->getH();
    long r, g, b, pos, n;
    RGBData *pBmpNew = new RGBData(w, h);
    TRGB *pArrNew = pBmpNew->getArr();

    for (unsigned long i = 0; i < w; i++) {
        long is = i - 1;
        long id = i + 1;
        if (is < 0)is = 0;
        if (id >= w)id = w - 1;
        for (unsigned long j = 0; j < h; j++) {
            long js = j - 1;
            long jd = j + 1;
            if (js < 0)js = 0;
            if (jd >= h)jd = h - 1;
            r = g = b = 0;
            n = 0;
            for (long i0 = is; i0 <= id; i0++) {
                for (long j0 = js; j0 <= jd; j0++) {
                    n++;
                    pos = i0 + j0*w;
                    r += pArr[pos].r;
                    g += pArr[pos].g;
                    b += pArr[pos].b;
                }
            }

            pos = i + j*w;
            if (n > 0) {
                pArrNew[pos].r = r / n;
                pArrNew[pos].g = g / n;
                pArrNew[pos].b = b / n;
            }
        }
    }

    //保存
    pBmpNew->saveToFile(save);
    delete pBmp;
    delete pBmpNew;
}

/**
 * 霓虹处理
 * @param pic
 * @param save
 */
void neon(string pic, string save) {
    RGBData *pBmp = new RGBData(pic);
    TRGB *pArr = pBmp->getArr();
    unsigned long w = pBmp->getW();
    unsigned long h = pBmp->getH();
    TRGB *pRGB, *pRGBLine, *pRGBCol;

    for (unsigned long i = 0; i < w - 1; i++) {
        for (unsigned long j = 0; j < h - 1; j++) {
            pRGB = pArr + i + j*w;
            pRGBLine = pArr + i + 1 + j*w;
            pRGBCol = pArr + i + (j + 1) * w;

            pRGB->r = sqrt(
                    (pRGBLine->r - pRGB->r)*(pRGBLine->r - pRGB->r)+
                    (pRGBCol->r - pRGB->r)*(pRGBCol->r - pRGB->r)
                    );
            pRGB->g = sqrt(
                    (pRGBLine->g - pRGB->g)*(pRGBLine->g - pRGB->g)+
                    (pRGBCol->g - pRGB->g)*(pRGBCol->g - pRGB->g)
                    );
            pRGB->b = sqrt(
                    (pRGBLine->b - pRGB->b)*(pRGBLine->b - pRGB->b)+
                    (pRGBCol->b - pRGB->b)*(pRGBCol->b - pRGB->b)
                    );
        }
    }
    for (unsigned long i = 0; i < w; i++) {
        pRGB = pArr + i + (h - 1) * w;
        pRGBCol = pArr + i + (h - 2) * w;
        pRGB->r = pRGBCol->r;
        pRGB->g = pRGBCol->g;
        pRGB->b = pRGBCol->b;
    }
    for (unsigned long j = 0; j < h; j++) {
        pRGB = pArr + w - 1 + (j) * w;
        pRGBLine = pArr + w - 2 + (j) * w;
        pRGB->r = pRGBLine->r;
        pRGB->g = pRGBLine->g;
        pRGB->b = pRGBLine->b;
    }

    //保存
    pBmp->saveToFile(save);
    delete pBmp;
}

/**
 * 锐化处理
 * @param pic
 * @param save
 */
void sharpen(string pic, string save) {
    sharpen(pic, save, 0.25);
}

void sharpen(string pic, string save, double ratio) {
    RGBData *pBmp = new RGBData(pic);
    TRGB *pArr = pBmp->getArr();
    unsigned long w = pBmp->getW();
    unsigned long h = pBmp->getH();
    TRGB *pRGB, *pRGBLineCol;

    for (unsigned long i = 1; i < w; i++) {
        for (unsigned long j = 1; j < h; j++) {
            pRGB = pArr + i + j*w;
            pRGBLineCol = pArr + i - 1 + (j - 1) * w;

            pRGB->r = pRGB->r + ratio * abs(pRGB->r - pRGBLineCol->r);
            pRGB->g = pRGB->g + ratio * abs(pRGB->g - pRGBLineCol->g);
            pRGB->b = pRGB->b + ratio * abs(pRGB->b - pRGBLineCol->b);
        }
    }
    for (unsigned long i = 0; i < w; i++) {
        pRGB = pArr + i;
        pRGBLineCol = pArr + i + w;
        pRGB->r = pRGBLineCol->r;
        pRGB->g = pRGBLineCol->g;
        pRGB->b = pRGBLineCol->b;
    }
    for (unsigned long j = 0; j < h; j++) {
        pRGB = pArr + (j) * w;
        pRGBLineCol = pArr + 1 + (j) * w;
        pRGB->r = pRGBLineCol->r;
        pRGB->g = pRGBLineCol->g;
        pRGB->b = pRGBLineCol->b;
    }

    //保存
    pBmp->saveToFile(save);
    delete pBmp;
}

/**
 * 浮雕处理
 * @param pic
 * @param save
 */
void cameo(string pic, string save) {
    cameo(pic, save, 128);
}

void cameo(string pic, string save, char add) {
    RGBData *pBmp = new RGBData(pic);
    TRGB *pArr = pBmp->getArr();
    unsigned long w = pBmp->getW();
    unsigned long h = pBmp->getH();
    TRGB *pRGB, *pRGBLineCol;

    for (unsigned long i = 1; i < w; i++) {
        for (unsigned long j = 0; j < h; j++) {
            pRGB = pArr + i + j*w;
            pRGBLineCol = pArr + i - 1 + (j) * w;

            pRGB->r = pRGB->r - pRGBLineCol->r + add;
            pRGB->g = pRGB->g - pRGBLineCol->g + add;
            pRGB->b = pRGB->b - pRGBLineCol->b + add;
        }
    }
    for (unsigned long i = 0; i < w; i++) {
        pRGB = pArr + i;
        pRGBLineCol = pArr + i + w;
        pRGB->r = pRGBLineCol->r;
        pRGB->g = pRGBLineCol->g;
        pRGB->b = pRGBLineCol->b;
    }

    //保存
    pBmp->saveToFile(save);
    delete pBmp;
}