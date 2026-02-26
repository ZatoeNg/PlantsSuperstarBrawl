//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_PEASHOOTERPLAYER_H
#define PLANTSMASHBROS_PEASHOOTERPLAYER_H

#include <iostream>
#include "player.h"
#include "peaBullet.h"

extern Atlas atlasPeashooterIdleLeft;                //豌豆射手朝向左的默认动画图集
extern Atlas atlasPeashooterIdleRight;                //豌豆射手朝向右的默认动画图集
extern Atlas atlasPeashooterRunLeft;                //豌豆射手朝向左的奔跑动画图集
extern Atlas atlasPeashooterRunRight;                //豌豆射手朝向右的奔跑动画图集
extern Atlas atlasPeashooterAttackExLeft;            //豌豆射手朝向左的特殊攻击动画图集
extern Atlas atlasPeashooterAttackExRight;            //豌豆射手朝向右的特殊攻击动画图集

extern Atlas atlasPeashooterDieLeft;				//豌豆射手朝向左的死亡动画图集
extern Atlas atlasPeashooterDieRight;				//豌豆射手朝向右的死亡动画图集

extern std::vector<Bullet *> bulletList;

class PeashooterPlayer : public Player {
private:
    const float speedPea = 0.75f;
    const float speedPeaEx = 1.5f;
    const int attackExDuration = 2500; //特殊攻击状态持续时间

    Timer timerAttackEx; //特殊攻击定时器
    Timer timerSpwanPeaEx; //豌豆子弹发射定时器
public:
    PeashooterPlayer(bool facingRight = true) : Player(facingRight) {
        animationIdleLeft.setAtlas(&atlasPeashooterIdleLeft);
        animationIdleRight.setAtlas(&atlasPeashooterIdleRight);
        animationRunLeft.setAtlas(&atlasPeashooterRunLeft);
        animationRunRight.setAtlas(&atlasPeashooterRunRight);


        animationAttackExLeft.setAtlas(&atlasPeashooterAttackExLeft);
        animationAttackExRight.setAtlas(&atlasPeashooterAttackExRight);

        animationDieLeft.setAtlas(&atlasPeashooterDieLeft);
        animationDieRight.setAtlas(&atlasPeashooterDieRight);

        animationIdleLeft.setInterval(75);
        animationIdleRight.setInterval(75);
        animationRunLeft.setInterval(75);
        animationRunRight.setInterval(75);

        animationAttackExLeft.setInterval(75);
        animationAttackExRight.setInterval(75);

        animationDieLeft.setInterval(150);
        animationDieRight.setInterval(150);

        animationDieLeft.setLoop(false);
        animationDieRight.setLoop(false);

        size.x = 96;
        size.y = 96;

        timerAttackEx.setWaitTime(attackExDuration);
        timerAttackEx.setOneShot(true);
        timerAttackEx.setCallback([&]() {
            isAttackingEx = false;
        });

        timerSpwanPeaEx.setWaitTime(100);
        timerSpwanPeaEx.setCallback([&]() {
            spawnPeaBullet(speedPeaEx);
        });

        attackCd = 100;

    };

    ~PeashooterPlayer() = default;

public:
    void onUpdate(int delta) {
        Player::onUpdate(delta);
        std::cout << "豌豆射手正在更新" << std::endl;

        if (isAttackingEx) {
            mainCamera.shake(5, 100);
            timerAttackEx.onUpdate(delta);
            timerSpwanPeaEx.onUpdate(delta);
        }
    }

private:
    void spawnPeaBullet(float speed) {
        Bullet *bullet = new PeaBullet();

        Vector2 bulletPosition, bulletVelocity;
        const Vector2 &bulletSize = bullet->getSize();
        bulletPosition.x = isFacingRight ?
                           position.x + size.x - bulletSize.x
                                         : position.x - bulletSize.x / 2;
        bulletPosition.y = position.y;

        bulletVelocity.x = isFacingRight ? speed : -speed;
        bulletVelocity.y = 0;

        bullet->setPosition(bulletPosition.x, bulletPosition.y);
        bullet->setVelocity(bulletVelocity.x, bulletVelocity.y);

        bullet->setCollideTarget(pid == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1);
        bullet->setCallback([&]() {
            mp += 25;
        });

        bulletList.push_back(bullet);
    }

    void onAttack() {
        spawnPeaBullet(speedPea);
        switch (rand() % 2) {
            case 0:
                mciSendString(_T("play pea_shoot_1 from 0"), NULL, 0, NULL);
                break;
            case 1:
                mciSendString(_T("play pea_shoot_2 from 0"), NULL, 0, NULL);
                break;
        }
    }

    void onAttackEx() {
        isAttackingEx = true;
        timerAttackEx.restart();

        isFacingRight ? animationAttackExRight.reset() : animationAttackExLeft.reset();

        mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);
    }
};

#endif //PLANTSMASHBROS_PEASHOOTERPLAYER_H
