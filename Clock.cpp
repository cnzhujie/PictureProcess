#include "Clock.h"

Clock::Clock() {
    _begin = 0;
    _end = 0;
#ifdef _WIN_
    __calcTimerFreq();
#endif
}

Clock::~Clock() {
    //dtor
}

#ifdef _WIN_
void Clock::__calcTimerFreq() {
    LARGE_INTEGER tmp;
    if (QueryPerformanceFrequency(&tmp) == TRUE) // 返回1秒钟的时间内的时钟频率(震荡次数)
    {
        _min_timer_frequency = tmp.QuadPart;
    } else {
        _min_timer_frequency = -1;
    }
}
#endif

long long Clock::start() {
#ifdef _WIN_
    __calcTimerFreq();
#endif
    _begin = current();
    return _begin;
}

long long Clock::start(string event) {
#ifdef _WIN_
    __calcTimerFreq();
#endif
    long long t = current();
    times[event] = t;
    return t;
}

long long Clock::end() {
    _end = current();
    return _end;
}

long long Clock::end(string event) {
    map<string, long long>::iterator it = times.find(event);
    if (it == times.end())return 0;
    long long t = current();
    it->second = t - it->second;
    return t;
}

long long Clock::current() {
#ifdef _WIN_
    static LARGE_INTEGER tmp;
    QueryPerformanceCounter(&tmp);
    return tmp.QuadPart;
#else
    static struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
#endif
}

long long Clock::time() {
#ifdef _WIN_
    return (_end - _begin)*1000000 / _min_timer_frequency;
#else
    return _end - _begin;
#endif
}

long long Clock::time(string event) {
    map<string, long long>::iterator it = times.find(event);
    if (it == times.end())return 0;
#ifdef _WIN_
    return it->second * 1000000 / _min_timer_frequency;
#else
    return it->second;
#endif
}

string Clock::strTime() {
    return makeStr(time()*1000);
}

string Clock::strTime(string event) {
    return makeStr(time(event)*1000);
}

void Clock::reset(string event) {
    map<string, long long>::iterator it = times.find(event);
    if (it == times.end())return;
    it->second = 0;
}

void Clock::resetAllEvent() {
    times.clear();
}

string Clock::makeStr(long long time) {
    ostringstream os;
    if (time < 1000) {
        os << time << "ns";
        return os.str();
    } else if (time < 1000000) {
        os << time / 1000.0 << "us";
        return os.str();
    } else if (time < 1000000000) {
        os << time / 1000000.0 << "ms";
        return os.str();
    }
    //转化为s
    double sec = time / 1000000000;
    if (sec < 60) {
        os << sec << "s";
        return os.str();
    }
    //min
    long min = (long) sec / 60;
    sec = sec - min * 60;
    if (min < 60) {
        os << min << "min" << sec << "s";
        return os.str();
    }

    long hour = min / 60;
    min = min % 60;
    os << hour << "h" << min << "min" << sec << "s";
    return os.str();
}
