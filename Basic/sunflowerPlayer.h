//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_SUNFLOWERPLAYER_H
#define PLANTSMASHBROS_SUNFLOWERPLAYER_H

#include <iostream>
#include "player.h"
#include "sunBulletEx.h"
#include "sunBullet.h"


extern Atlas atlasSunflowerIdleLeft;            //龙日葵朝向左的默认动画图集
extern Atlas atlasSunflowerIdleRight;           //龙日葵朝向右的默认动画图集
extern Atlas atlasSunflowerRunLeft;             //龙日葵朝向左的奔跑动画图集
extern Atlas atlasSunflowerRunRight;            //龙日葵朝向右的奔跑动画图集
extern Atlas atlasSunflowerAttackExLeft;        //龙日葵朝向左的特殊攻击动画图集
extern Atlas atlasSunflowerAttackExRight;       //龙日葵朝向右的特殊攻击动画图集
extern Atlas atlasSunText;                      //"阳光"文本动画图集

extern Atlas atlasSunflowerDieLeft;				//龙日葵朝向左的死亡动画图集
extern Atlas atlasSunflowerDieRight;			//龙日葵朝向右的死亡动画图集

extern Player* player1;
extern Player* player2 ;


class SunflowerPlayer : public Player {
private:
    const float speedSunEx = 0.15f;
    const Vector2 velocitySun = {0.25f, -0.5f};
private:
    Animation animationSunText; //头顶文本动画
    bool isSunTextVisible = false; // 是否显示头顶文本
public:
    SunflowerPlayer(bool facingRight = true):Player(facingRight) {
        animationIdleLeft.setAtlas(&atlasSunflowerIdleLeft);
        animationIdleRight.setAtlas(&atlasSunflowerIdleRight);
        animationRunLeft.setAtlas(&atlasSunflowerRunLeft);
        animationRunRight.setAtlas(&atlasSunflowerRunRight);

        animationDieLeft.setAtlas(&atlasSunflowerDieLeft);
        animationDieRight.setAtlas(&atlasSunflowerDieRight);

        animationAttackExLeft.setAtlas(&atlasSunflowerAttackExLeft);
        animationAttackExRight.setAtlas(&atlasSunflowerAttackExRight);
        animationSunText.setAtlas(&atlasSunText);

        animationIdleLeft.setInterval(75);
        animationIdleRight.setInterval(75);
        animationRunLeft.setInterval(75);
        animationRunRight.setInterval(75);

        animationAttackExLeft.setInterval(100);
        animationAttackExRight.setInterval(100);
        animationSunText.setInterval(100);

        animationDieLeft.setInterval(150);
        animationDieRight.setInterval(150);

        animationDieLeft.setLoop(false);
        animationDieRight.setLoop(false);

        animationAttackExLeft.setLoop(false);
        animationAttackExRight.setLoop(false);
        animationSunText.setLoop(false);

        animationAttackExLeft.setCallback([&]() {
            isAttackingEx=false;
            isSunTextVisible=false;
        });

        animationAttackExRight.setCallback([&]() {
            isAttackingEx=false;
            isSunTextVisible=false;
        });

        size.x = 96;
        size.y = 96;

        attackCd=250;
    };

    ~SunflowerPlayer() = default;

public:
    void onUpdate(int delta) {
        Player::onUpdate(delta);
        std::cout << "龙日葵正在更新" << std::endl;

        if(isSunTextVisible)animationSunText.onUpdate(delta);
    }

    void onDraw(const Camera &camera)
    {
        Player::onDraw(camera);
        if(isSunTextVisible)
        {
            Vector2 textPosition;
            IMAGE* frame = animationSunText.getFrame();
            textPosition.x=position.x-(size.x-frame->getwidth())/2;
            textPosition.y=position.y-frame->getheight();
            animationSunText.onDraw(camera,(int)textPosition.x,(int)textPosition.y);
        }
    }

    void onAttack()
    {
        Bullet *bullet = new SunBullet();

        Vector2 bulletPosition;

        const Vector2 &bulletSize = bullet->getSize();
        bulletPosition.x = position.x + (size.x - bulletSize.x)/2;
        bulletPosition.y = position.y;

        bullet->setPosition(bulletPosition.x, bulletPosition.y);
        bullet->setVelocity(isFacingRight?velocitySun.x:-velocitySun.x, velocitySun.y);

        bullet->setCollideTarget(pid == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1);
        bullet->setCallback([&]() {
            mp += 35;
        });

        bulletList.push_back(bullet);
    }

    void onAttackEx()
    {
        isAttackingEx = true;
        isSunTextVisible=true;

        animationSunText.reset();
        isFacingRight?animationAttackExRight.reset():animationAttackExLeft.reset();

        Bullet* bullet = new SunBulletEx();
        Player* targetPlayer = (pid == PlayerId::P1?player2:player1);
        Vector2 bulletPosition,bulletVelocity;
        const Vector2& bulletSize = bullet->getSize();
        const Vector2& targetSize = targetPlayer->getSize();
        const Vector2& targetPosition = targetPlayer->getPosition();

        bulletPosition.x = targetPosition.x+(targetSize.x - bulletSize.x)/2;
        bulletPosition.y = -size.y;

        bulletVelocity.x=0;
        bulletVelocity.y=speedSunEx;

        bullet->setPosition(bulletPosition.x,bulletPosition.y);
        bullet->setVelocity( bulletVelocity.x, bulletVelocity.y);

        bullet->setCollideTarget(pid == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1);

        bullet->setCallback([&]() {
            mp += 50;
        });

        bulletList.push_back(bullet);

        mciSendString(_T("play sun_text from 0"),NULL,0,NULL);
    }
};

#endif //PLANTSMASHBROS_SUNFLOWERPLAYER_H
