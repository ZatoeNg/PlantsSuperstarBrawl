//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_ATLAS_H
#define PLANTSMASHBROS_ATLAS_H


#include <vector>
#include <iostream>

#include "graphics.h"


/*
 * 图集功能
 * */
class Atlas {
private:
    std::vector<IMAGE> imgList;

public:
    Atlas() = default;

    ~Atlas() = default;

public:
    void loadFromFile(LPCTSTR pathTemplate, int num)
    {
        imgList.clear();
        imgList.resize(num);

        TCHAR pathFile[256];
        for (int i = 0; i < num; i++)
        {
            _stprintf_s(pathFile, pathTemplate, i + 1);
            loadimage(&imgList[i], pathFile);
        }
    }

    //清空图集中已加载的图片对象
    void clear()
    {
        imgList.clear();
    }

    //获取图集中图片的数量
    int getSize()
    {
        return (int)imgList.size();
    }

    //获取实际渲染的动画帧
    IMAGE* getImage(int idx)
    {
        if (idx < 0 || idx >= imgList.size())
        {
            return nullptr;
        }

        return &imgList[idx];
    }

    // 向图集添加图片对象
    void addImage(const IMAGE& img)
    {
        imgList.push_back(img);
    }


};

#endif //PLANTSMASHBROS_ATLAS_H
