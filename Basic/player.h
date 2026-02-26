//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_PLAYER_H
#define PLANTSMASHBROS_PLAYER_H

#include <graphics.h>
#include "camera.h"
#include "vector2.h"
#include "animation.h"
#include "playerId.h"
#include "bullet.h"
#include "particle.h"

extern std::vector<Platform> platformList;
extern std::vector<Bullet *> bulletList;
extern bool isDebug;


extern Atlas atlasRunEffect;                        //奔跑特效动画图集
extern Atlas atlasJumpEffect;                        //跳跃动画图集
extern Atlas atlasLandEffect;                        //落地动画图集

extern IMAGE img1PCursor;                            //1P 指示光标图片
extern IMAGE img2PCursor;                            //2P 指示光标图片


class Player {
private:
    Animation *currentAnimation = nullptr; //当前正在播放的动画



    bool isLeftKeyDown = false;  //向左是否按下
    bool isRightKeyDown = false; //向右是否按下



    //普攻冷却时间
    bool canAttack = true;  //是否可以释放普通攻击
    Timer timerAttcakCd; //普攻攻击冷却定时器



protected:
    Animation animationIdleLeft;  //默认动画
    Animation animationIdleRight; //默认动画
    Animation animationRunLeft;   //奔跑动画
    Animation animationRunRight;  //奔跑动画
    Animation animationAttackExLeft;    //特殊攻击动画
    Animation animationAttackExRight;   //特殊攻击动画
    Animation animationJumpEffect; //跳跃动画
    Animation animationLandEffect; //落地动画
    Animation animationDieLeft;  //向左死亡
    Animation animationDieRight; //向右死亡

    bool isJumpEffectVisible = false; //跳跃动画可见性
    bool isLandEffectVisible = false; //落地动画可见性

    Vector2 positionJumpEffect; //跳跃动画位置
    Vector2 positionLandEffect; //落地动画位置

    bool isFacingRight = true;  //角色是否朝向右
    PlayerId pid = PlayerId::P1; //玩家序号 ID
    bool isAttackingEx = false; //是否正在释放特殊攻击
    int attackCd = 500;

    bool isInvulnerable = false; //是否处于无敌状态
    bool isShowingSketchFrame = false; //是否出现剪影
    Timer timerInvulnerable; //无法状态定时器
    Timer timerInvulnerableBlink; //无法状态闪烁定时器
    IMAGE imgSketch; //动画剪影图片

    std::vector<Particle> particleList; //粒子对象数组

    Vector2 position;  //角色位置
    Vector2 velocity;  //角色速度
    Vector2 size;      //角色尺寸

    const float runVelocity = 0.55f;   //跑步速度
    const float jumpVelocity = -0.85f; //跳跃速度
    const float gravity = 1.6e-3f;     //玩家重力

    int mp = 0;        //角色能量
    int hp = 100;      //角色生命

    Timer timerRunEffectGeneration; //跑动特效粒子定时器
    Timer timerDieEffectGeneration; //死亡特效粒子定时器

    bool isCursorVisible = true; //光标是否可见
    Timer timerCursorVisibility; //光标定时器

    Vector2 lastHurtDirection; //最后一次受击方向


public:
    Player(bool facingRight = true) : isFacingRight(facingRight) {
        currentAnimation = isFacingRight ? &animationIdleRight : &animationIdleLeft;
        timerAttcakCd.setWaitTime(attackCd);
        timerAttcakCd.setOneShot(true);
        timerAttcakCd.setCallback([&]() {
            canAttack = true;
        });

        timerInvulnerable.setWaitTime(750);
        timerInvulnerable.setOneShot(true);
        timerInvulnerable.setCallback([&]() {
            isInvulnerable = false;
        });

        timerInvulnerableBlink.setWaitTime(75);
        timerInvulnerableBlink.setCallback([&]() {
            isShowingSketchFrame = !isShowingSketchFrame;
        });

        timerRunEffectGeneration.setWaitTime(75);
        timerRunEffectGeneration.setCallback([&]() {
            Vector2 particlePosition;
            IMAGE *frame = atlasRunEffect.getImage(0);
            particlePosition.x = position.x + (size.x - frame->getwidth()) / 2;
            particlePosition.y = position.y + size.y - frame->getheight();
            particleList.emplace_back(particlePosition, &atlasRunEffect, 45);

        });

        timerDieEffectGeneration.setWaitTime(35);
        timerDieEffectGeneration.setCallback([&]() {
            Vector2 particlePosition;
            IMAGE *frame = atlasRunEffect.getImage(0);
            particlePosition.x = position.x + (size.x - frame->getwidth()) / 2;
            particlePosition.y = position.y + size.y - frame->getheight();
            particleList.emplace_back(particlePosition, &atlasRunEffect, 150);
        });

        animationJumpEffect.setAtlas(&atlasJumpEffect);
        animationJumpEffect.setInterval(25);
        animationJumpEffect.setLoop(false);
        animationJumpEffect.setCallback([&]() {
            isJumpEffectVisible = false;
        });

        animationLandEffect.setAtlas(&atlasLandEffect);
        animationLandEffect.setInterval(50);
        animationLandEffect.setLoop(false);
        animationLandEffect.setCallback([&]() {
            isLandEffectVisible = false;
        });

        timerCursorVisibility.setWaitTime(2500);
        timerCursorVisibility.setOneShot(true);
        timerCursorVisibility.setCallback([&]() {
            isCursorVisible = false;
        });

    };


    ~Player() = default;

public:


    virtual void onUpdate(int delta) {
        int direction = isRightKeyDown - isLeftKeyDown;
        if (direction != 0) {
            if (!isAttackingEx)isFacingRight = direction > 0;
            currentAnimation = isFacingRight ? &animationRunRight : &animationRunLeft;
            float distance = direction * runVelocity * delta;
            onRun(distance);
        } else {
            currentAnimation = isFacingRight ? &animationIdleRight : &animationIdleLeft;
            timerRunEffectGeneration.pause();
        }


        if (isAttackingEx)currentAnimation = isFacingRight ? &animationAttackExRight : &animationAttackExLeft;

        if (hp <= 0)currentAnimation = lastHurtDirection.x < 0 ? &animationDieLeft : &animationDieRight;

        currentAnimation->onUpdate(delta);
        animationJumpEffect.onUpdate(delta);
        animationLandEffect.onUpdate(delta);

        timerAttcakCd.onUpdate(delta);
        timerInvulnerable.onUpdate(delta);
        timerInvulnerableBlink.onUpdate(delta);
        timerCursorVisibility.onUpdate(delta);
        timerRunEffectGeneration.onUpdate(delta);
        if (hp <= 0)timerDieEffectGeneration.onUpdate(delta);

        particleList.erase(std::remove_if(particleList.begin(), particleList.end(),
                                          [](const Particle &particle) {
                                              return !particle.checkValid();
                                          }), particleList.end());

        for (Particle &particle: particleList)particle.onUpdate(delta);

        if (isShowingSketchFrame)sketchImage(currentAnimation->getFrame(), &imgSketch);

        moveAndCollide(delta);

    }

    virtual void onDraw(const Camera &camera) {

        if (isJumpEffectVisible)
            animationJumpEffect.onDraw(camera, (int) positionJumpEffect.x, (int) positionJumpEffect.y);
        if (isLandEffectVisible)
            animationLandEffect.onDraw(camera, (int) positionLandEffect.x, (int) positionLandEffect.y);

        for (const Particle &particle: particleList)particle.onDraw(camera);

        if (hp > 0 && isInvulnerable && isShowingSketchFrame)
            putimageAlpha(camera, (int) position.x, (int) position.y, &imgSketch);
        else currentAnimation->onDraw(camera, (int) position.x, (int) position.y);

        if (isCursorVisible) {
            switch (pid) {
                case PlayerId::P1:
                    putimageAlpha(camera, (int) (position.x + (size.x - img1PCursor.getwidth()) / 2),
                                  (int) (position.y - img1PCursor.getheight()), &img1PCursor);
                    break;
                case PlayerId::P2:
                    putimageAlpha(camera, (int) (position.x + (size.x - img2PCursor.getwidth()) / 2),
                                  (int) (position.y - img2PCursor.getheight()), &img2PCursor);
                    break;
            }
        }

        if (isDebug) {
            setlinecolor(RGB(0, 125, 255));
            rectangle((int) position.x, (int) position.y, (int) (position.x + size.x), (int) (position.y + size.y));
        }
    }

    virtual void onInput(const ExMessage &msg) {
        switch (msg.message) {
            case WM_KEYDOWN:
                switch (pid) {
                    case PlayerId::P1:
                        switch (msg.vkcode) {
                            case 0x41:  //[A]
                                isLeftKeyDown = true;
                                break;
                            case 0x44:  //[D]
                                isRightKeyDown = true;
                                break;
                            case 0x57:  //[W]
                                onJump();
                                break;
                            case 0x46: //[F]
                                if (canAttack) {
                                    onAttack();
                                    canAttack = false;
                                    timerAttcakCd.restart();
                                }
                                break;
                            case 0x47: //[G]
                                if (mp >= 100) {
                                    onAttackEx();
                                    mp = 0;
                                }
                                break;
                        }
                        break;
                    case PlayerId::P2:
                        switch (msg.vkcode) {
                            case VK_LEFT:
                                isLeftKeyDown = true;
                                break;
                            case VK_RIGHT:
                                isRightKeyDown = true;
                                break;
                            case VK_UP:
                                onJump();
                                break;
                            case VK_OEM_PERIOD: //[.]
                                if (canAttack) {
                                    onAttack();
                                    canAttack = false;
                                    timerAttcakCd.restart();
                                }
                                break;
                            case VK_OEM_2: //[/]
                                if (mp >= 100) {
                                    onAttackEx();
                                    mp = 0;
                                }
                                break;
                        }
                        break;
                }
                break;
            case WM_KEYUP:
                switch (pid) {
                    case PlayerId::P1:
                        switch (msg.vkcode) {
                            case 0x41:  //[A]
                                isLeftKeyDown = false;
                                break;
                            case 0x44:  //[D]
                                isRightKeyDown = false;
                                break;
                        }
                        break;
                    case PlayerId::P2:
                        switch (msg.vkcode) {
                            case VK_LEFT:
                                isLeftKeyDown = false;
                                break;
                            case VK_RIGHT:
                                isRightKeyDown = false;
                                break;
                        }
                        break;
                }
                break;
        }
    }

protected:
    void moveAndCollide(int delta) {
        float lastVelocityY = velocity.y;

        velocity.y += gravity * delta;
        position += velocity * (float) delta;

        if (hp <= 0)return;

        if (velocity.y > 0) {
            for (const Platform &platform: platformList) {
                const Platform::CollisionShape &shape = platform.shape;
                bool isCollideX = (
                        max(position.x + size.x, shape.right) - min(position.x, shape.left)
                        <= size.x + (shape.right - shape.left));

                bool isCollideY = (shape.y >= position.y && shape.y <= position.y + size.y);


                if (isCollideX && isCollideY) {
                    float deltaPosY = velocity.y * delta;
                    float lastTickFootPosY = position.y + size.y - deltaPosY;
                    if (lastTickFootPosY <= shape.y) {
                        position.y = shape.y - size.y;
                        velocity.y = 0;

                        if (lastVelocityY != 0)onLand();
                        break;
                    }
                }


            }
        }

        if (!isInvulnerable) {
            for (Bullet *bullet: bulletList) {
                if (!bullet->getValid() || bullet->getCollideTarget() != pid)continue;

                if (bullet->checkCollision(position, size)) {
                    makeInvulnerable();
                    bullet->onCollide();
                    bullet->setValid(false);
                    hp -= bullet->getDamage();
                    lastHurtDirection = bullet->getPosition() - position;
                    if (hp <= 0) {
                        velocity.x = lastHurtDirection.x < 0 ? 0.35f : -0.35f;
                        velocity.y = -1.0f;
                    }
                }
            }
        }
    }


public:
    void setId(PlayerId id) {
        this->pid = id;
    }

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    const Vector2 &getPosition() const {
        return position;
    }

    const Vector2 &getSize() const {
        return size;
    }

    virtual void onRun(float distance) {
        if (isAttackingEx)return;

        position.x += distance;
        timerRunEffectGeneration.resume();
    }

    virtual void onJump() {
        if (velocity.y != 0 || isAttackingEx)return;
        velocity.y += jumpVelocity;

        isJumpEffectVisible = true;
        animationJumpEffect.reset();

        IMAGE *effectFrame = animationJumpEffect.getFrame();
        positionJumpEffect.x = position.x + (size.x - effectFrame->getwidth()) / 2;
        positionJumpEffect.y = position.y + (size.y - effectFrame->getheight());


    }

    virtual void onLand() {
        isLandEffectVisible = true;
        animationLandEffect.reset();

        IMAGE *effectFrame = animationLandEffect.getFrame();
        positionLandEffect.x = position.x + (size.x - effectFrame->getwidth()) / 2;
        positionLandEffect.y = position.y + (size.y - effectFrame->getheight());
    }

    virtual void onAttack() {}

    virtual void onAttackEx() {}

    void setHp(int val) {
        hp = val;
    }

    int getHp() const {
        return hp;
    }

    int getMp() const {
        return mp;
    }

    void makeInvulnerable() {
        isInvulnerable = true;
        timerInvulnerable.restart();
    }
};

#endif //PLANTSMASHBROS_PLAYER_H
