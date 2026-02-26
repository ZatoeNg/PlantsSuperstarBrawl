//
// Created by Administrator on 2025/1/6.
//

#ifndef PLANTSMASHBROS_SUNBULLETEX_H
#define PLANTSMASHBROS_SUNBULLETEX_H

#include "bullet.h"
#include "animation.h"

extern Atlas atlasSunEx;             //阳光动画图集
extern Atlas atlasSunExExplode;    //阳光爆炸动画图集
extern Camera mainCamera;

class SunBulletEx : public Bullet {
private:
    Animation animationIdle;     //巨大日光爆炸默认动画
    Animation animationExplode;  //巨大日光爆炸动画
    Vector2 explodeRenderOffset; //爆炸动画渲染偏移

public:
    SunBulletEx() {
        size.x = 288, size.y = 288;
        damage = 20;

        animationIdle.setAtlas(&atlasSunEx);
        animationIdle.setInterval(50);

        animationExplode.setAtlas(&atlasSunExExplode);
        animationExplode.setInterval(50);
        animationExplode.setLoop(false);
        animationExplode.setCallback([&]() {
            canRemove = true;
        });

        IMAGE *frameIdle = animationIdle.getFrame();
        IMAGE *frameExplode = animationExplode.getFrame();

        explodeRenderOffset.x = (frameIdle->getwidth() - frameExplode->getwidth()) / 2.0f;
        explodeRenderOffset.y = (frameIdle->getheight() - frameExplode->getheight()) / 2.0f;
    }

    ~SunBulletEx() = default;

public:
    void onCollide() {
        Bullet::onCollide();
        mainCamera.shake(20, 350);
        mciSendString(_T("play sun_explode_ex from 0"), NULL, 0, NULL);
    }

    bool checkCollision(const Vector2 &position, const Vector2 &size) {

        bool isCollideX = ((max(this->position.x + this->size.x, position.x + size.x)
                            - min(this->position.x, position.x)) <= this->size.x + size.x);

        bool isCollideY = ((max(this->position.y + this->size.y, position.y + size.y)
                            - min(this->position.y, position.y)) <= this->size.y + size.y);

        return (isCollideX && isCollideY);
    }

    void onUpdate(int delta)
    {
        if (valid)position += velocity * (float)delta;

        if (!valid)animationExplode.onUpdate(delta);
        else animationIdle.onUpdate(delta);

        if (checkIfExceedsScreen())canRemove = true;
    }

    void onDraw(const Camera &camera) const {
        if (valid)animationIdle.onDraw(camera, (int) position.x, (int) position.y);
        else {
            animationExplode.onDraw(camera,
                                    (int) (position.x + explodeRenderOffset.x),
                                    (int) (position.y + explodeRenderOffset.y)
            );
        }

        Bullet::onDraw(camera);
    }

};

#endif //PLANTSMASHBROS_SUNBULLETEX_H
