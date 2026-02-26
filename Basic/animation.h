//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_ANIMATION_H
#define PLANTSMASHBROS_ANIMATION_H

#include <functional>

#include "graphics.h"
#include "atlas.h"
#include "camera.h"
#include "image.h"


class Animation {
private:
    Atlas* atlas = nullptr;
    int timer = 0; //计时器
    int interval = 0; //帧间隔
    int idxFrame = 0; //帧索引
    bool isLoop = true; //是否循环
    std::function<void()> callBack; //回调函数

public:
    Animation() = default;

    ~Animation() = default;

public:
    //    重置动画状态
    void reset() {
        timer = 0;
        idxFrame = 0;
    }

    //   设置动画所使用的图集
    void setAtlas(Atlas* newAtlas) {
        reset();
        atlas = newAtlas;
    }

    //设置动画是否循环播放
    void setLoop(bool flag) {
        isLoop = flag;
    }

    //设置动画帧间隔
    void setInterval(int ms) {
        interval = ms;
    }

    //    获取当前帧索引
    int getIdxFrame() {
        return idxFrame;
    }

    //    获取当前帧图片
    IMAGE* getFrame() {
        return atlas->getImage(idxFrame);
    }

    //判断动画是否播放结束
    bool checkFinished() {
        if (isLoop)return false;
        return (idxFrame == atlas->getSize() - 1);
    }

    //    设置回调函数
    void setCallback(std::function<void()> callback) {
        this->callBack = callback;
    }

public:
    void onUpdate(int delta) {
        timer += delta;
        if (timer >= interval) {
            timer = 0;
            idxFrame++;
            if (idxFrame >= atlas->getSize()) {
                idxFrame = isLoop ? 0 : atlas->getSize() - 1;
                if (!isLoop && callBack)
                {
                    callBack();
                }
            }
        }
    }

    void onDraw(const Camera& camera,int x, int y) const {
        putimageAlpha(camera,x, y, atlas->getImage(idxFrame));
    }

};

#endif //PLANTSMASHBROS_ANIMATION_H
