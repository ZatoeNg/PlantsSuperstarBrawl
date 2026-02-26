//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_SCENEMANAGER_H
#define PLANTSMASHBROS_SCENEMANAGER_H

#include <graphics.h>
#include "camera.h"
#include "sceneTemplate.h"

extern SceneTemplate* menuScene;
extern SceneTemplate* gameScene;
extern SceneTemplate* selectorScene;


class SceneManager {
public:
    enum class SceneType {
        Menu,
        Game,
        Selector,
    };
private:
    SceneTemplate* currentScene = nullptr;

public:
    SceneManager() = default;

    ~SceneManager() = default;

public:
    //    设置当前场景
    void setCurrentScene(SceneTemplate* scene) {
        currentScene = scene;
        currentScene->onEnter();
    }

    //    场景跳转
    void switchTo(SceneType type) {
        currentScene->onExit();
        switch (type) {
            case SceneType::Menu:
                currentScene = menuScene;
                break;
            case SceneType::Game:
                currentScene = gameScene;
                break;
            case SceneType::Selector:
                currentScene = selectorScene;
                break;
            default:
                break;
        }
        currentScene->onEnter();
    }

    void onUpdate(int delta)
    {
        currentScene->onUpdate(delta);
    }

    void onDraw(const Camera& camera)
    {
        currentScene->onDraw(camera);
    }

    void onInput(const ExMessage& msg)
    {
        currentScene->onInput(msg);
    }

};

#endif //PLANTSMASHBROS_SCENEMANAGER_H
