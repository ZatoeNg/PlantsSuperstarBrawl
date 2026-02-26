//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_PLATFORM_H
#define PLANTSMASHBROS_PLATFORM_H

#include <graphics.h>
#include "camera.h"
#include "image.h"


extern bool isDebug;

class Platform
{
private:

public:
    struct CollisionShape
    {
        float y;
        float left, right;
    };

public:
    CollisionShape shape{};
    IMAGE* img = nullptr;
    POINT renderPosition = { 0 };

public:
    Platform() = default;
    ~Platform() = default;

public:

    void onDraw(const Camera& camera) const
    {
        putimageAlpha(camera, renderPosition.x, renderPosition.y, img);

        if (isDebug)
        {
            setlinecolor(RGB(255, 0, 0));
            line(camera, (int)shape.left, (int)shape.y, (int)shape.right, (int)shape.y);
        }
    }

};

#endif //PLANTSMASHBROS_PLATFORM_H
