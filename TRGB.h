/*
 * TRGB.h
 *
 *  Created on: 2014年5月9日
 *      Author: zhujie
 */

#ifndef TRGB_H_
#define TRGB_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//变量重定义
typedef unsigned short RGB_WORD;
typedef unsigned int RGB_DWORD;
typedef unsigned char RGB_BYTE;
typedef int RGB_LONG;
/**
 * RGB
 */
class TRGB
{
public:
    unsigned char b;
    unsigned char g;
    unsigned char r;
public:
    TRGB()
    {
    	r=0;
    	g=0;
    	b=0;
    }
    TRGB(unsigned char b1,unsigned char g1,unsigned char r1)
    {
    	b=b1;g=g1;r=r1;
    }
    void set(unsigned char b1,unsigned char g1,unsigned char r1)
    {
    	b=b1;g=g1;r=r1;
    }
    void rand()
    {
    	srand((unsigned long)(time(NULL)));
    	b=::rand()%256;
    	g=::rand()%256;
    	r=::rand()%256;
    }
    TRGB& Increase()
    {
    	if(b<255)
        {
            b++;
    	}
        else if(g<255)
        {
            g++;
    	}
        else if(r<255)
        {
            r++;
    	}
    	return *this;
    }
    bool operator==(const TRGB& another)
    {
    	return r==another.r && g==another.g && b==another.b;
    }
};


#endif /* TRGB_H_ */
