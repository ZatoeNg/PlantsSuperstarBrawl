//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_TIMER_H
#define PLANTSMASHBROS_TIMER_H

#include <functional>

class Timer
{
private:
    int passTime = 0; //已过时间
    int waitTime = 0; //等待时间
    bool paused = false;  //是否暂停
    bool shotted = false; //是否触发
    bool oneShot = false; //单次触发

    std::function<void()> callback;


public:
    Timer() = default;
    ~Timer() = default;

public:
    void restart()
    {
        passTime = 0;
        shotted = false;
    }

    void setWaitTime(int val)
    {
        waitTime = val;
    }

    void setOneShot(bool flag)
    {
        oneShot = flag;
    }

    void pause()
    {
        paused = true;
    }

    void resume()
    {
        paused = false;
    }


    void setCallback(std::function<void()> callback)
    {
        this->callback = callback;
    }

public:
    void onUpdate(int delta)
    {
        if (paused)return;

        passTime += delta;
        if (passTime >= waitTime)
        {
            if ((!oneShot || (oneShot && !shotted)) && callback)callback();
            shotted = true;
            passTime = 0;
        }

    }

};

#endif //PLANTSMASHBROS_TIMER_H
