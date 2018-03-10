#ifndef COLOCK_H
#define COLOCK_H

#ifdef _WIN_
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <map>
using namespace std;

/**
 * 时间计时器
 */
class Clock {
public:
    Clock();
    virtual ~Clock();
    /**
     * 开始计时
     * @return 当前时间
     */
    long long start();
    /**
     * 记录某一事件的开始时间
     * @param event
     * @return 
     */
    long long start(string event);
    /**
     * 结束计时
     * @return 当前时间
     */
    long long end();
    /**
     * 记录某一事件的结束时间
     * @param event
     * @return 
     */
    long long end(string event);
    /**
     * 返回start与end之间的时间差(us)
     * @return 
     */
    long long time();
    /**
     * 返回某个事件的开始与结束的时间差(us)
     * @param event
     * @return 
     */
    long long time(string event);
    /**
     * 将time()函数的返回值以方便识别的字符串返回（xx小时xx分钟xx秒）
     * @return 
     */
    string strTime();
    /**
     * 将time(event)函数的返回值以方便识别的字符串返回（xx小时xx分钟xx秒）
     * @return 
     */
    string strTime(string event);
    /**
     * 重置某个事件的时间计时
     * @param event
     */
    void reset(string event);
    /**
     * 重置所有事件的计时
     */
    void resetAllEvent();
    /**
     * 返回当前系统时间(us)
     * @return 
     */
    long long current();

    /**
     * 将long类型的纳秒级时间使用字面时间表示
     * @param time
     */
    static string makeStr(long long time);

private:
#ifdef _WIN_
    long long _min_timer_frequency;
    void __calcTimerFreq();
#endif
private:
    long long _begin; // 记录开始时间
    long long _end; //记录结束时间
    map<string, long long> times; //记录各个事件的时间
};

#endif // COLOCK_H
