//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_MENUSCENE_H
#define PLANTSMASHBROS_MENUSCENE_H

#include <iostream>

#include "SceneManager.h"
#include "image.h"
#include "sceneTemplate.h"


extern SceneManager sceneManager;

extern IMAGE imgMenuBackground;


class MenuScene : public SceneTemplate {
private:

public:
    MenuScene() = default;
    ~MenuScene() = default;

public:
    void onEnter()
    {
        mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);

    }

    void onDraw(const Camera& camera)
    {
        putimage(0, 0, &imgMenuBackground);
    }

    void onInput(const ExMessage& msg)
    {
        if (msg.message == WM_KEYUP)
        {
            mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
            sceneManager.switchTo(SceneManager::SceneType::Selector);
        }
    }

    void onExit()
    {
        /*std::cout << "退出主菜单" << std::endl;*/
    }



};

#endif //PLANTSMASHBROS_MENUSCENE_H
