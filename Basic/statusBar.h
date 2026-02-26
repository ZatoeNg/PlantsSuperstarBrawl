//
// Created by Administrator on 2025/1/7.
//

#ifndef PLANTSMASHBROS_STATUSBAR_H
#define PLANTSMASHBROS_STATUSBAR_H


#include <windef.h>
#include "image.h"

class StatusBar
{
private:
    int hp = 0;
    int mp = 0;
    POINT position={0};
    IMAGE* imgAvatar = nullptr;

    const int width=275;

public:
    StatusBar()=default;
    ~StatusBar()=default;

public:
    void onDraw()
    {
        putimageAlpha((int)position.x,(int)position.y,imgAvatar);

        setfillcolor(RGB(5,5,5));
        solidroundrect((int)(position.x+100),(int)(position.y+10),position.x+100+width+3*2,position.y+36,8,8);
        solidroundrect((int)(position.x+100),(int)(position.y+45),position.x+100+width+3*2,position.y+71,8,8);


        setfillcolor(RGB(67,47,47));
        solidroundrect((int)(position.x+100),(int)(position.y+10),position.x+100+width+3,position.y+33,8,8);
        solidroundrect((int)(position.x+100),(int)(position.y+45),position.x+100+width+3,position.y+68,8,8);

        float hpBarWidth = width *max(0,hp)/100.0f;
        float mpBarWidth = width *min(100,mp)/100.0f;

        setfillcolor(RGB(197,61,67));
        solidroundrect(position.x+100,position.y+10,position.x+100+hpBarWidth+3,position.y+33,8,8);

        setfillcolor(RGB(83,131,195));
        solidroundrect(position.x+100,position.y+45,position.x+100+mpBarWidth+3,position.y+68,8,8);
    }

public:
    void setAvatar(IMAGE* img)
    {
        imgAvatar=img;
    }

    void setPosition(int x,int y)
    {
        position.x=x;
        position.y=y;
    }

    void setHp(int val)
    {
        hp=val;
    }

    void setMp(int val)
    {
        mp=val;
    }
};

#endif //PLANTSMASHBROS_STATUSBAR_H
