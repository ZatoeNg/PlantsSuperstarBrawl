//
// Created by Administrator on 2025/1/7.
//

#ifndef PLANTSMASHBROS_PARTICLE_H
#define PLANTSMASHBROS_PARTICLE_H

#include "vector2.h"
#include "atlas.h"
#include "camera.h"
#include "image.h"

class Particle {
private:
    int timer = 0;  //动画播放定时器
    int lifespan = 0; //单帧粒子动画存活时间
    int idxFrame = 0; //正在播放的动画帧

    Vector2 position;  //粒子世界坐标
    bool valid = true; //粒子对象是否有效
    Atlas *atlas = nullptr; //粒子图集

public:
    Particle() = default;

    Particle(const Vector2 &positions, Atlas *atlas, int lifespans)
            : position(positions), atlas(atlas), lifespan(lifespans) {

    }

    ~Particle() = default;

public:
    void onUpdate(int delta) {
        timer += delta;
        if (timer >= lifespan) {
            timer = 0;
            idxFrame++;
            if (idxFrame >= atlas->getSize()) {
                idxFrame = atlas->getSize() - 1;
                valid = false;
            }
        }
    }

    void onDraw(const Camera& camera)const
    {
        putimageAlpha(camera,(int)position.x,(int)position.y,atlas->getImage(idxFrame));
    }
public:
    void setAtlas(Atlas *atlas) {
        this->atlas = atlas;
    }

    void setPosition(const Vector2 &positions) {
        position = positions;
    }

    void setLifespan(int ms) {
        lifespan = ms;
    }

    bool checkValid() const {
        return valid;
    }

};

#endif //PLANTSMASHBROS_PARTICLE_H
