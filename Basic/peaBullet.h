//
// Created by Administrator on 2025/1/6.
//

#ifndef PLANTSMASHBROS_PEABULLET_H
#define PLANTSMASHBROS_PEABULLET_H

#include "bullet.h"
#include "animation.h"

extern IMAGE imgPea;
extern Atlas atlasPeaBreak;

class PeaBullet : public Bullet {
private:
    Animation animationBreak; //豌豆子弹破碎动画


public:
    PeaBullet() {
        size.x = 64;
        size.y = 64;
        damage = 10;

        animationBreak.setAtlas(&atlasPeaBreak);
        animationBreak.setInterval(100);
        animationBreak.setLoop(false);
        animationBreak.setCallback([&]() {
            canRemove = true;
        });
    }

    ~PeaBullet() = default;

public:
    void onCollide() {
        Bullet::onCollide();

        switch (rand() % 3) {
            case 0:
                mciSendString(_T("play pea_break_1 from 0"), NULL, 0, NULL);
                break;
            case 1:
                mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
                break;
            case 2:
                mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
                break;
        }
    }

    void onUpdate(int delta) {
        position += velocity * (float) delta;
        if (!valid)animationBreak.onUpdate(delta);
        if (checkIfExceedsScreen())canRemove = true;
    }

    void onDraw(const Camera &camera) const {
        if (valid)putimageAlpha(camera, (int) position.x, (int) position.y, &imgPea);
        else animationBreak.onDraw(camera, (int) position.x, (int) position.y);

        Bullet::onDraw(camera);
    }
};

#endif //PLANTSMASHBROS_PEABULLET_H
