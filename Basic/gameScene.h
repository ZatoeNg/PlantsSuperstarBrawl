//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_GAMESCENE_H
#define PLANTSMASHBROS_GAMESCENE_H

#include <iostream>

#include "SceneManager.h"
#include "image.h"
#include "camera.h"
#include "platform.h"
#include "player.h"
#include "sceneTemplate.h"
#include "bullet.h"
#include "statusBar.h"


#include  <vector>

extern IMAGE imgSky;                                //天空
extern IMAGE imgHills;                                //山脉
extern IMAGE imgPlatformLarge;                        //大型平台
extern IMAGE imgPlatformSmall;                        //小型平台

extern Camera mainCamera;
extern std::vector<Platform> platformList;
extern std::vector<Bullet *> bulletList;

extern IMAGE img1PWinner;                            //1P 获胜文本图片
extern IMAGE img2PWinner;                            //2P 获胜文本图片
extern IMAGE imgWinnerBar;                           //获胜玩家文本背景图片

extern Player *player1;
extern Player *player2;

extern IMAGE *imgPlayer1Avatar;
extern IMAGE *imgPlayer2Avatar;

extern SceneManager sceneManager;

class GameScene : public SceneTemplate {
private:
    POINT posImgSky = {0};        //天空背景图片位置
    POINT posImgHills = {0};      //山脉背景图片位置

    StatusBar statusBar1P; //状态条
    StatusBar statusBar2P; //状态条

    bool isGameOver = false; //游戏是否结束

    POINT posImgWinnerBar = {0}; //结算动效背景位置
    POINT posImgWinnerText = {0};//结算动效文本位置
    int posXImgWinnerBarDst = 0;//结算动效背景移动的目标位置
    int posXImgWinnerTextDst = 0;//结算动效文本移动的目标位置

    Timer timerWinnerSlideIn; //动效滑入定时器
    Timer timerWinnerSlideOut;//动效滑出定时器
    bool isSlideOutStarted = false; //结算动效是否滑出

    const float speedWinnerBar = 3.0f; //动效背景速度
    const float speedWinnerText = 1.5f;//动效文本速度

public:
    GameScene() = default;

    ~GameScene() = default;

public:
    void onEnter() {

        isGameOver = false;
        isSlideOutStarted = false;

        posImgWinnerBar.x = -imgWinnerBar.getwidth();
        posImgWinnerBar.y = (getheight() - imgWinnerBar.getheight()) / 2;
        posXImgWinnerBarDst = (getwidth() - imgWinnerBar.getwidth()) / 2;

        posImgWinnerText.x = -posImgWinnerBar.x;
        posImgWinnerText.y = (getheight() - img1PWinner.getheight()) / 2;
        posXImgWinnerTextDst = (getwidth() - img1PWinner.getwidth()) / 2;


        timerWinnerSlideIn.restart();
        timerWinnerSlideIn.setWaitTime(2500);
        timerWinnerSlideIn.setOneShot(true);
        timerWinnerSlideIn.setCallback([&]() {
            isSlideOutStarted = true;
        });

        timerWinnerSlideOut.restart();
        timerWinnerSlideOut.setWaitTime(1000);
        timerWinnerSlideOut.setOneShot(true);
        timerWinnerSlideOut.setCallback([&]() {
            sceneManager.switchTo(SceneManager::SceneType::Menu);
        });

        statusBar1P.setAvatar(imgPlayer1Avatar);
        statusBar2P.setAvatar(imgPlayer2Avatar);

        statusBar1P.setPosition(235, 625);
        statusBar2P.setPosition(675, 625);

        player1->setPosition(200, 50);
        player2->setPosition(975, 50);

        posImgSky.x = (getwidth() - imgSky.getwidth()) / 2;
        posImgSky.y = (getheight() - imgSky.getheight()) / 2;

        posImgHills.x = (getwidth() - imgHills.getwidth()) / 2;
        posImgHills.y = (getheight() - imgHills.getheight()) / 2;

        platformList.resize(4);

        Platform &largePlatform = platformList[0];
        largePlatform.img = &imgPlatformLarge;
        largePlatform.renderPosition.x = 122;
        largePlatform.renderPosition.y = 455;

        largePlatform.shape.left = (float) largePlatform.renderPosition.x + 30;
        largePlatform.shape.right = (float) largePlatform.renderPosition.x + imgPlatformLarge.getwidth() - 30;
        largePlatform.shape.y = (float) largePlatform.renderPosition.y + 60;

        Platform &smallPlatform1 = platformList[1];
        smallPlatform1.img = &imgPlatformSmall;
        smallPlatform1.renderPosition.x = 175;
        smallPlatform1.renderPosition.y = 360;

        smallPlatform1.shape.left = (float) smallPlatform1.renderPosition.x + 40;
        smallPlatform1.shape.right = (float) smallPlatform1.renderPosition.x + imgPlatformSmall.getwidth() - 40;
        smallPlatform1.shape.y = (float) smallPlatform1.renderPosition.y + imgPlatformSmall.getheight() / 2;

        Platform &smallPlatform2 = platformList[2];
        smallPlatform2.img = &imgPlatformSmall;
        smallPlatform2.renderPosition.x = 855;
        smallPlatform2.renderPosition.y = 360;

        smallPlatform2.shape.left = (float) smallPlatform2.renderPosition.x + 40;
        smallPlatform2.shape.right = (float) smallPlatform2.renderPosition.x + imgPlatformSmall.getwidth() - 40;
        smallPlatform2.shape.y = (float) smallPlatform2.renderPosition.y + imgPlatformSmall.getheight() / 2;


        Platform &smallPlatform3 = platformList[3];
        smallPlatform3.img = &imgPlatformSmall;
        smallPlatform3.renderPosition.x = 515;
        smallPlatform3.renderPosition.y = 225;

        smallPlatform3.shape.left = (float) smallPlatform3.renderPosition.x + 40;
        smallPlatform3.shape.right = (float) smallPlatform3.renderPosition.x + imgPlatformSmall.getwidth() - 40;
        smallPlatform3.shape.y = (float) smallPlatform3.renderPosition.y + imgPlatformSmall.getheight() / 2;

        mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);
    }

    void onUpdate(int delta) {
        player1->onUpdate(delta);
        player2->onUpdate(delta);

        mainCamera.onUpdate(delta);
        for (Bullet *bullet: bulletList)bullet->onUpdate(delta);

        bulletList.erase(std::remove_if(
                                 bulletList.begin(), bulletList.end(),
                                 [](const Bullet *bullet) {
                                     bool deletable = bullet->checkCanRemove();
                                     if (deletable)delete bullet;
                                     return deletable;
                                 }),
                         bulletList.end());

        for (Bullet *bullet: bulletList)bullet->onUpdate(delta);

        const Vector2 &positionPlayer1 = player1->getPosition();
        const Vector2 &positionPlayer2 = player2->getPosition();

        if (positionPlayer1.y >= getheight())player1->setHp(0);
        if (positionPlayer2.y >= getheight())player2->setHp(0);

        if (player1->getHp() <= 0 || player2->getHp() <= 0) {
            if (!isGameOver) {
                mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
                mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
            }
            isGameOver = true;
        }

        statusBar1P.setHp(player1->getHp());
        statusBar1P.setMp(player1->getMp());

        statusBar2P.setHp(player2->getHp());
        statusBar2P.setMp(player2->getMp());

        if (isGameOver) {
            posImgWinnerBar.x += (int) (speedWinnerBar * delta);
            posImgWinnerText.x += (int) (speedWinnerText * delta);

            if (!isSlideOutStarted) {
                timerWinnerSlideIn.onUpdate(delta);
                if (posImgWinnerBar.x > posXImgWinnerBarDst)posImgWinnerBar.x = posXImgWinnerBarDst;
                if (posImgWinnerText.x > posXImgWinnerTextDst)posImgWinnerText.x = posXImgWinnerTextDst;
            } else timerWinnerSlideOut.onUpdate(delta);
        }

    }

    void onDraw(const Camera &camera) {
        putimageAlpha(camera, posImgSky.x, posImgSky.y, &imgSky);
        putimageAlpha(camera, posImgHills.x, posImgHills.y, &imgHills);

        for (const Platform &platform: platformList)platform.onDraw(camera);

        if (isDebug) {
            settextcolor(RGB(255, 0, 0));
            outtextxy(15, 15, _T("已开启调试模式,按[Q]键关闭"));
        }

        player1->onDraw(camera);
        player2->onDraw(camera);

        for (const Bullet *bullet: bulletList)bullet->onDraw(camera);

        if (isGameOver) {
            putimageAlpha(posImgWinnerBar.x, posImgWinnerBar.y, &imgWinnerBar);
            putimageAlpha(posImgWinnerText.x, posImgWinnerText.y,
                          player1->getHp() > 0 ? &img1PWinner : &img2PWinner);
        } else {
            statusBar1P.onDraw();
            statusBar2P.onDraw();
        }

    }

    void onInput(const ExMessage &msg) {
        player1->onInput(msg);
        player2->onInput(msg);

        switch (msg.message) {
            case WM_KEYDOWN:
                // [Q]
                if (msg.vkcode == 0x51)isDebug = !isDebug;
                break;
            default:
                break;
        }
    }

    void onExit() {
        delete player1;
        player1=nullptr;

        delete player2;
        player2=nullptr;

        isDebug = false;
        bulletList.clear();
        mainCamera.reset();

    }


};

#endif //PLANTSMASHBROS_GAMESCENE_H
