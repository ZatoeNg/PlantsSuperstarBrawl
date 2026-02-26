//
// Created by Administrator on 2025/1/6.
//

#ifndef PLANTSMASHBROS_SUNBULLET_H
#define PLANTSMASHBROS_SUNBULLET_H

#include "bullet.h"
#include "animation.h"

extern Atlas atlasSun;             //阳光动画图集
extern Atlas atlasSunExplode;    //阳光爆炸动画图集
extern Camera mainCamera;

class SunBullet : public Bullet {
private:
    Animation animationIdle;     //日光爆炸默认动画
    Animation animationExplode;  //日光爆炸动画
    Vector2 explodeRenderOffset; //爆炸动画渲染偏移

    const float gravity = 1e-3f; //日光炸弹重力

public:
    SunBullet() {
        size.x = 96, size.y = 96;
        damage = 20;

        animationIdle.setAtlas(&atlasSun);
        animationIdle.setInterval(50);

        animationExplode.setAtlas(&atlasSunExplode);
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

    ~SunBullet() = default;

public:
    void onCollide() {
        Bullet::onCollide();
        mainCamera.shake(5, 250);
        mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);
    }

    void onUpdate(int delta) {

        if (valid) {
            velocity.y += gravity * delta;
            position += velocity * (float) delta;

        }

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

#endif //PLANTSMASHBROS_SUNBULLET_H
