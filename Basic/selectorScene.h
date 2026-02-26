//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_SELECTORSCENE_H
#define PLANTSMASHBROS_SELECTORSCENE_H


#include "SceneManager.h"
#include "player.h"
#include "atlas.h"
#include "animation.h"
#include "peashooterPlayer.h"
#include "sunflowerPlayer.h"
#include "playerId.h"


extern Player* player1;
extern Player* player2;


extern IMAGE imgVS;									//VS艺术字体图片
extern IMAGE img1P;									//1P 艺术字体
extern IMAGE img2P;									//2P 艺术字体
extern IMAGE img1PDesc;							//1P 键位描述图片
extern IMAGE img2PDesc;							//2P 键位描述图片
extern IMAGE imgGravestoneLeft;						//朝向左的墓碑图片
extern IMAGE imgGravestoneRight;						//朝向右的墓碑图片
extern IMAGE imgSelectorTip;							//选角界面的提示信息文本图片
extern IMAGE imgSelectorBackground;					//选角界面的背景
extern IMAGE img1PSelectorBtnIdleLeft;			//1P 向左选择按钮默认状态图片
extern IMAGE img1PSelectorBtnIdleRight;			//1P 向右选择按钮默认状态图片
extern IMAGE img1PSelectorBtnDownLeft;			//1P 向左选择按钮按下状态图片
extern IMAGE img1PSelectorBtnDownRight;			//1P 向右选择按钮按下状态图片
extern IMAGE img2PSelectorBtnIdleLeft;			//2P 向左选择按钮默认状态图片
extern IMAGE img2PSelectorBtnIdleRight;			//2P 向右选择按钮默认状态图片
extern IMAGE img2PSelectorBtnDownLeft;			//2P 向左选择按钮按下状态图片
extern IMAGE img2PSelectorBtnDownRight;			//2P 向右选择按钮按下状态图片
extern IMAGE imgPeashooterSelectorBackgroundLeft;	//选角界面朝向左的豌豆射手背景图片
extern IMAGE imgPeashooterSelectorBackgroundRight;	//选角界面朝向右的豌豆射手背景图片
extern IMAGE imgSunflowerSelectorBackgroundLeft;	//选角界面朝向左的龙日葵背景图片
extern IMAGE imgSunflowerSelectorBackgroundRight;	//选角界面朝向右的龙日葵背景图片


extern Atlas atlasPeashooterIdleRight;				//豌豆射手朝向右的默认动画图集
extern Atlas atlasSunflowerIdleRight;				//龙日葵朝向右的默认动画图集

extern IMAGE imgAvatarPeashooter;					//豌豆射手头像图片
extern IMAGE imgAvatarSunflower;						//龙日葵头像图片

extern SceneManager sceneManager;

extern IMAGE* imgPlayer1Avatar;
extern IMAGE* imgPlayer2Avatar;

class SelectorScene : public SceneTemplate {
private:
    POINT PosImgVS = { 0 }; //VS艺术字体图片位置
    POINT PosImgTip = { 0 };//提示信息文本图片位置
    POINT PosImg1P = { 0 };   //1P 艺术字体位置
    POINT PosImg2P = { 0 };   //2P 艺术字体位置
    POINT PosImg1PDesc = { 0 };  //1P 键位描述图片位置
    POINT PosImg2PDesc = { 0 };  //2P 键位描述图片位置
    POINT PosImg1PName = { 0 }; //1P 角色姓名文本位置
    POINT PosImg2PName = { 0 }; //2P 角色姓名文本位置
    POINT PosAnimation1P = { 0 }; //1P 角色动画位置
    POINT PosAnimation2P = { 0 }; //2P 角色动画位置
    POINT PosImg1PGravestone = { 0 };//1P 墓碑图片位置
    POINT PosImg2PGravestone = { 0 };//2P 墓碑图片位置
    POINT Pos1PSelectorBtnLeft = { 0 };//1P 向左切换按钮位置
    POINT Pos1PSelectorBtnRight = { 0 };//1P 向右切换按钮位置;
    POINT Pos2PSelectorBtnLeft = { 0 };//2P 向左切换按钮位置
    POINT Pos2PSelectorBtnRight = { 0 };//2P 向右切换按钮位置

private:
    enum class PlayerType
    {
        Peashooter = 0,
        Sunflower,
        Invalid
    };

private:
    Animation animationPeashooter;  //豌豆射手动画
    Animation animationSunflower; 	//龙日葵动画

    PlayerType PlayerTyper1 = PlayerType::Peashooter;
    PlayerType PlayerTyper2 = PlayerType::Sunflower;

    LPCTSTR StrPeashooterName = _T("豌豆射手");
    LPCTSTR StrSunflowerName = _T("龙日葵");

    int SelectorBackgroundScorllOffsetX = 0; //控制背景板滚动

    bool isBth1PLeftDown = false;
    bool isBth1PRightDown = false;
    bool isBth2PLeftDown = false;
    bool isBth2PRightDown = false;


public:
    SelectorScene() = default;
    ~SelectorScene() = default;

public:
    void onEnter() {
        animationPeashooter.setAtlas(&atlasPeashooterIdleRight);
        animationPeashooter.setInterval(100);
        animationSunflower.setAtlas(&atlasSunflowerIdleRight);
        animationSunflower.setInterval(100);

        static const int OFFSET_X = 50;

        PosImgVS.x = (getwidth() / 2 - imgVS.getwidth() / 2);
        PosImgVS.y = (getheight() / 2 - imgVS.getheight() / 2);
        PosImgTip.y = getheight() - 125;
        PosImgTip.x = (getwidth() / 2 - imgSelectorTip.getwidth()/2);

        PosImg1P.x = (getwidth() / 2 - img1P.getwidth()) / 2 - OFFSET_X;
        PosImg1P.y = 35;
        PosImg2P.x = getwidth() / 2 + (getwidth() /2 - img2P.getwidth()) / 2 + OFFSET_X;
        PosImg2P.y = PosImg1P.y;

        PosImg1PDesc.y = getheight() - 150;
        PosImg1PDesc.x = (getwidth() / 2 - img1PDesc.getwidth()) / 2 - OFFSET_X;
        PosImg2PDesc.y = PosImg1PDesc.y;
        PosImg2PDesc.x = getwidth() / 2 + (getwidth() / 2 - img2PDesc.getwidth()) / 2 + OFFSET_X;

        PosImg1PGravestone.x = (getwidth() / 2 - imgGravestoneRight.getwidth()) / 2 - OFFSET_X;
        PosImg1PGravestone.y = PosImg1P.y + img1P.getheight() + 35;

        PosImg2PGravestone.x = getwidth() / 2 + (getwidth() / 2 - imgGravestoneRight.getwidth()) / 2 + OFFSET_X;
        PosImg2PGravestone.y = PosImg1PGravestone.y;

        PosAnimation1P.x = (getwidth() / 2 - atlasPeashooterIdleRight.getImage(0)->getwidth()) / 2 - OFFSET_X;
        PosAnimation1P.y = PosImg1PGravestone.y + 80;
        PosAnimation2P.x = getwidth() / 2 + (getwidth() / 2 - atlasPeashooterIdleRight.getImage(0)->getwidth()) / 2 + OFFSET_X;
        PosAnimation2P.y = PosAnimation1P.y;


        PosImg1PName.y = PosAnimation1P.y + 155;
        PosImg2PName.y = PosImg1PName.y;


        Pos1PSelectorBtnLeft.x = PosImg1PGravestone.x- img1PSelectorBtnIdleLeft.getwidth();
        Pos1PSelectorBtnLeft.y = PosImg1PGravestone.y + (imgGravestoneRight.getheight() - img1PSelectorBtnIdleLeft.getheight()) / 2;
        Pos1PSelectorBtnRight.x = PosImg1PGravestone.x + imgGravestoneRight.getwidth();
        Pos1PSelectorBtnRight.y = Pos1PSelectorBtnLeft.y;
        Pos2PSelectorBtnLeft.x = PosImg2PGravestone.x - img2PSelectorBtnIdleLeft.getwidth();
        Pos2PSelectorBtnLeft.y = Pos1PSelectorBtnLeft.y;
        Pos2PSelectorBtnRight.x = PosImg2PGravestone.x + imgGravestoneLeft.getwidth();
        Pos2PSelectorBtnRight.y = Pos1PSelectorBtnLeft.y;


    }
    void onUpdate(int delta) {
        animationPeashooter.onUpdate(delta);
        animationSunflower.onUpdate(delta);

        SelectorBackgroundScorllOffsetX += 5;
        if (SelectorBackgroundScorllOffsetX >= imgPeashooterSelectorBackgroundLeft.getwidth())
        {
            SelectorBackgroundScorllOffsetX = 0;
        }
    }
    void onDraw(const Camera& camera)
    {
        IMAGE* imgP1SelectorBackground = nullptr;
        IMAGE* imgP2SelectorBackground = nullptr;

        switch (PlayerTyper2)
        {
            case PlayerType::Peashooter:
                imgP1SelectorBackground = &imgPeashooterSelectorBackgroundRight;
                break;
            case PlayerType::Sunflower:
                imgP1SelectorBackground = &imgSunflowerSelectorBackgroundRight;
            default:
                imgP1SelectorBackground = &imgPeashooterSelectorBackgroundRight;
        }

        switch (PlayerTyper1)
        {
            case PlayerType::Peashooter:
                imgP2SelectorBackground = &imgPeashooterSelectorBackgroundLeft;
                break;
            case PlayerType::Sunflower:
                imgP2SelectorBackground = &imgSunflowerSelectorBackgroundLeft;
            default:
                imgP2SelectorBackground = &imgPeashooterSelectorBackgroundLeft;
        }

        putimage(0, 0, &imgSelectorBackground);


        putimageAlpha(SelectorBackgroundScorllOffsetX-imgP1SelectorBackground->getwidth(),
                      0,imgP1SelectorBackground);

        putimageAlpha(SelectorBackgroundScorllOffsetX, 0
                , imgP1SelectorBackground->getwidth() - SelectorBackgroundScorllOffsetX
                , 0, imgP1SelectorBackground, 0, 0);

        putimageAlpha(getwidth()- imgP2SelectorBackground->getwidth(), 0
                , imgP2SelectorBackground->getwidth() - SelectorBackgroundScorllOffsetX
                , 0, imgP2SelectorBackground, SelectorBackgroundScorllOffsetX, 0);

        putimageAlpha(getwidth() - SelectorBackgroundScorllOffsetX, 0
                , imgP2SelectorBackground);

        putimageAlpha(camera,PosImgVS.x,  PosImgVS.y, &imgVS);
        putimageAlpha(camera,PosImgTip.x, PosImgTip.y, &imgSelectorTip);

        putimageAlpha(camera,PosImg1P.x, PosImg1P.y, &img1P);
        putimageAlpha(camera,PosImg2P.x, PosImg2P.y, &img2P);

        putimageAlpha(camera,PosImg1PGravestone.x, PosImg1PGravestone.y, &imgGravestoneRight);
        putimageAlpha(camera,PosImg2PGravestone.x, PosImg2PGravestone.y, &imgGravestoneLeft);

        switch (PlayerTyper1)
        {
            case PlayerType::Peashooter:
                animationPeashooter.onDraw(camera, PosAnimation1P.x, PosAnimation1P.y);
                PosImg1PName.x = PosImg1PGravestone.x + (imgGravestoneRight.getwidth() - textwidth(StrPeashooterName))/2;
                outtextxyShaded(PosImg1PName.x, PosImg1PName.y, StrPeashooterName);
                break;
            case PlayerType::Sunflower:
                animationSunflower.onDraw(camera, PosAnimation1P.x, PosAnimation1P.y);
                PosImg1PName.x = PosImg1PGravestone.x + (imgGravestoneRight.getwidth() - textwidth(StrSunflowerName)) / 2;
                outtextxyShaded(PosImg1PName.x, PosImg1PName.y, StrSunflowerName);
                break;
        }

        switch (PlayerTyper2)
        {
            case PlayerType::Peashooter:
                animationPeashooter.onDraw(camera, PosAnimation2P.x, PosAnimation2P.y);
                PosImg2PName.x = PosImg2PGravestone.x + (imgGravestoneLeft.getwidth() - textwidth(StrPeashooterName)) / 2;
                outtextxyShaded(PosImg2PName.x, PosImg2PName.y, StrPeashooterName);
                break;
            case PlayerType::Sunflower:
                animationSunflower.onDraw(camera, PosAnimation2P.x, PosAnimation2P.y);
                PosImg2PName.x = PosImg2PGravestone.x + (imgGravestoneLeft.getwidth() - textwidth(StrSunflowerName)) / 2;
                outtextxyShaded(PosImg2PName.x, PosImg2PName.y, StrSunflowerName);
                break;
        }

        putimageAlpha(Pos1PSelectorBtnLeft.x, Pos1PSelectorBtnLeft.y
                , isBth1PLeftDown ? &img1PSelectorBtnDownLeft : &img1PSelectorBtnIdleLeft);

        putimageAlpha(Pos1PSelectorBtnRight.x, Pos1PSelectorBtnRight.y
                , isBth1PRightDown ? &img1PSelectorBtnDownRight : &img1PSelectorBtnIdleRight);

        putimageAlpha(Pos2PSelectorBtnLeft.x, Pos2PSelectorBtnLeft.y
                , isBth2PLeftDown ? &img2PSelectorBtnDownLeft : &img2PSelectorBtnIdleLeft);

        putimageAlpha(Pos2PSelectorBtnRight.x, Pos2PSelectorBtnRight.y
                , isBth2PRightDown ? &img2PSelectorBtnDownRight : &img2PSelectorBtnIdleRight);

        putimageAlpha(camera, PosImg1PDesc.x, PosImg1PDesc.y, &img1PDesc);
        putimageAlpha(camera, PosImg2PDesc.x, PosImg2PDesc.y, &img2PDesc);

        putimageAlpha(camera, PosImgTip.x, PosImgTip.y,&imgSelectorTip);

    }
    void onInput(const ExMessage& msg) {
        switch (msg.message)
        {
            case WM_KEYDOWN:
                switch (msg.vkcode)
                {
                    case 0x41://[A]
                        isBth1PLeftDown = true;
                        break;
                    case 0x44://[B]
                        isBth1PRightDown = true;
                        break;
                    case VK_LEFT: // [<-]
                        isBth2PLeftDown = true;
                        break;
                    case VK_RIGHT: // [->]
                        isBth2PRightDown = true;
                        break;
                }
                break;
            case WM_KEYUP:
                switch (msg.vkcode)
                {
                    case 0x41://[A]
                        isBth1PLeftDown = false;
                        PlayerTyper1 = (PlayerType)(((int)PlayerType::Invalid + (int)PlayerTyper1 - 1) % (int)PlayerType::Invalid);
                        mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
                        break;
                    case 0x44://[B]
                        isBth1PRightDown = false;
                        PlayerTyper1 = (PlayerType)(((int)PlayerTyper1 + 1) % (int)PlayerType::Invalid);
                        mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
                        break;
                    case VK_LEFT: // [<-]
                        isBth2PLeftDown = false;
                        PlayerTyper2 = (PlayerType)(((int)PlayerType::Invalid + (int)PlayerTyper2 - 1) % (int)PlayerType::Invalid);
                        mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
                        break;
                    case VK_RIGHT: // [->]
                        isBth2PRightDown = false;
                        PlayerTyper2 = (PlayerType)(((int)PlayerTyper2 + 1) % (int)PlayerType::Invalid);
                        mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
                        break;
                    case VK_RETURN:
                        sceneManager.switchTo(SceneManager::SceneType::Game);
                        mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
                        break;
                }
                break;
            default:
                break;
        }
    }
    void onExit() {

        switch (PlayerTyper1)
        {
            case PlayerType::Peashooter:
                player1 = new PeashooterPlayer();
                imgPlayer1Avatar = &imgAvatarPeashooter;
                break;
            case PlayerType::Sunflower:
                player1 = new SunflowerPlayer();
                imgPlayer1Avatar = &imgAvatarSunflower;
                break;
        }
        player1->setId(PlayerId::P1);

        switch (PlayerTyper2)
        {
            case PlayerType::Peashooter:
                player2 = new PeashooterPlayer(false);
                imgPlayer2Avatar = &imgAvatarPeashooter;
                break;
            case PlayerType::Sunflower:
                player2 = new SunflowerPlayer(false);
                imgPlayer2Avatar = &imgAvatarSunflower;
                break;
        }
        player2->setId(PlayerId::P2);

        mciSendString(_T("stop bgm_menu"),NULL,0,NULL);
    }

public:
    void outtextxyShaded(int x, int y, LPCTSTR str)
    {
        settextcolor(RGB(45, 45, 45));
        outtextxy(x + 3, y + 3, str);
        settextcolor(RGB(255, 255, 255));
        outtextxy(x, y, str);
    }

};

#endif //PLANTSMASHBROS_SELECTORSCENE_H
