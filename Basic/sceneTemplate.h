//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_SCENETEMPLATE_H
#define PLANTSMASHBROS_SCENETEMPLATE_H

#include "graphics.h"
#include "camera.h"

class SceneTemplate {
private:

public:
    SceneTemplate() = default;
    ~SceneTemplate() = default;

public:
    virtual void onEnter() {}
    virtual void onUpdate(int delta) {}
    virtual void onDraw(const Camera& camera) {}
    virtual void onInput(const ExMessage& msg) {}
    virtual void onExit() {}



};

#endif //PLANTSMASHBROS_SCENETEMPLATE_H
