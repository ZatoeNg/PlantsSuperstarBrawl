//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_CAMERA_H
#define PLANTSMASHBROS_CAMERA_H

#include "vector2.h"
#include "timer.h"

class Camera
{
private:
    Vector2 position; // 摄像机位置
    Timer timerShake; //摄像机抖动定时器
    bool isShaking = false; //摄像机是否正在抖动
    float shakingStrength=0; // 摄像机抖动幅度

public:
    Camera() {

        timerShake.setOneShot(true);
        timerShake.setCallback(
                [&]()
                {
                    isShaking = false;
                    reset();
                }
        );

    }
    ~Camera() = default;

public:

    const Vector2& getPosition() const
    {
        return position;
    }

    void reset()
    {
        position.x = 0;
        position.y = 0;
    }

    void onUpdate(int delta)
    {
        /*const Vector2 speed = { -0.35f,0 };
        position += speed * (float)delta;*/

        timerShake.onUpdate(delta);
        if (isShaking)
        {
            position.x = (-50 + rand() % 100) / 50.0f * shakingStrength;
            position.y = (-50 + rand() % 100) / 50.0f * shakingStrength;
        }
    }

    void shake(float strength, int duration)
    {
        isShaking = true;
        shakingStrength = strength;

        timerShake.setWaitTime(duration);
        timerShake.restart();
    }

};

#endif //PLANTSMASHBROS_CAMERA_H
