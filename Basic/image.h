//
// Created by Administrator on 2025/1/4.
//

#ifndef PLANTSMASHBROS_IMAGE_H
#define PLANTSMASHBROS_IMAGE_H

#include <graphics.h>
#include "camera.h"

#pragma comment(lib,"MSIMG32.LIB")

//图片翻转
inline void flipImage(IMAGE* src, IMAGE* dst)
{
    int w = src->getwidth();
    int h = src->getheight();

    //对IMAGE对象内存分配的过程
    Resize(dst, w, h);

    //获取图片的像素色彩缓冲区，存储着RGB色彩和额外的透明通道的信息
    DWORD* srcBuffer = GetImageBuffer(src);
    DWORD* dstBuffer = GetImageBuffer(dst);

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int idx_left_img = y * w + x; //源像素索引
            int idx_right_img = y * w + (w - x - 1); //目标像素索引
            dstBuffer[idx_right_img] = srcBuffer[idx_left_img];
        }
    }
}


// 正确渲染带透明度的图片
inline void putimageAlpha(int dstX, int dstY, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();

    AlphaBlend(
            GetImageHDC(GetWorkingImage()), dstX, dstY, w, h,
            GetImageHDC(img), 0, 0, w, h,
            { AC_SRC_OVER,0,255,AC_SRC_ALPHA }
    );
}

// 正确渲染带透明度的图片
inline void putimageAlpha(const Camera camera, int dstX, int dstY, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();

    const Vector2& posCamera = camera.getPosition();

    AlphaBlend(
            GetImageHDC(GetWorkingImage()), (int)(dstX- posCamera.x), (int)(dstY - posCamera.y), w, h,
            GetImageHDC(img), 0, 0, w, h,
            { AC_SRC_OVER,0,255,AC_SRC_ALPHA }
    );
}

// 正确渲染带透明度的图片
inline void putimageAlpha(int dstX, int dstY,int width,int height, IMAGE* img,int srcX,int srcY)
{
    int w = width>0?width: img->getwidth();
    int h = height>0? height: img->getheight();

    AlphaBlend(
            GetImageHDC(GetWorkingImage()), dstX, dstY, w, h,
            GetImageHDC(img), srcX, srcY, w, h,
            { AC_SRC_OVER,0,255,AC_SRC_ALPHA }
    );
}

inline void line(const Camera& camera, int x1, int y1, int x2, int y2)
{
    const Vector2& posCamera = camera.getPosition();
    line((int)(x1 - posCamera.x), (int)(y1 - posCamera.y), (int)(x2 - posCamera.x), (int)(y2 - posCamera.y));
}

inline void sketchImage(IMAGE* src,IMAGE* dst)
{
    int w = src->getwidth();
    int h = src->getheight();

    Resize(dst, w, h);

    //获取图片的像素色彩缓冲区，存储着RGB色彩和额外的透明通道的信息
    DWORD* srcBuffer = GetImageBuffer(src);
    DWORD* dstBuffer = GetImageBuffer(dst);

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int idx = y * w + x; //源像素索引
            dstBuffer[idx] = BGR(RGB(255,255,255))|(srcBuffer[idx]&0xFF000000);
        }
    }
}

#endif //PLANTSMASHBROS_IMAGE_H
