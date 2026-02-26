//
// Created by Administrator on 2025/1/6.
//

#ifndef PLANTSMASHBROS_BULLET_H
#define PLANTSMASHBROS_BULLET_H

#include <functional>
#include <graphics.h>
#include "vector2.h"
#include "playerId.h"
#include "camera.h"

extern bool isDebug;

class Bullet {
private:

protected:
    Vector2 size;      //子弹尺寸
    Vector2 position;  //子弹位置
    Vector2 velocity; //子弹速度
    int damage = 10;   //子弹伤害
    bool valid = true; //判断子弹是否有效
    bool canRemove = false; //判断子弹是否可以被移除
    std::function<void()> callback; //子弹碰撞回调函数
    PlayerId targetId = PlayerId::P1; //子弹碰撞目标玩家Id

public:
    Bullet() = default;

    ~Bullet() = default;

protected:
    bool checkIfExceedsScreen() {
        return (
                position.x + size.x <= 0 || position.x >= getwidth()
                || position.y + size.y <= 0 || position.y >= getheight()
        );
    }

public:
    void setDamage(int val) {
        damage = val;
    }

    int getDamage() {
        return damage;
    }

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    Vector2 getPosition() const {
        return position;
    }

    const Vector2 &getSize() const {
        return size;
    }

    void setVelocity(float x, float y) {
        velocity.x = x;
        velocity.y = y;
    }

    void setCollideTarget(PlayerId target) {
        this->targetId = target;
    }

    PlayerId getCollideTarget() const {
        return targetId;
    }

    void setCallback(std::function<void()> callback) {
        this->callback = callback;
    }

    void setValid(bool flag) {
        valid = flag;
    }

    bool getValid() const {
        return valid;
    }

    bool checkCanRemove() const {
        return canRemove;
    }

public:
    virtual void onCollide() {
        if (callback)callback();
    }

    virtual bool checkCollision(const Vector2 &position, const Vector2 &size) {
        return (
                this->position.x + this->size.x / 2 >= position.x
                && this->position.x + this->size.x / 2 <= position.x + size.x
                && this->position.y + this->size.y / 2 >= position.y
                && this->position.y + this->size.y / 2 <= position.y + size.y
        );
    }

public:
    virtual void onUpdate(int delta) {}

    virtual void onDraw(const Camera &camera) const {
        if(isDebug)
        {
            setfillcolor(RGB(255,255,255));
            setlinecolor(RGB(255,255,255));
            rectangle((int)position.x,(int)position.y,(int)(position.x+size.x),(int)(position.y+size.y));
            solidcircle((int)(position.x+size.x/2),(int)(position.y+size.y/2),5);
        }
    }
};


#endif //PLANTSMASHBROS_BULLET_H
