//
// Created by hdutyq on 2019/5/30.
//

#include "lvgm/lv_precision.h"
#include "RTdef.h"
#include "ray.h"


#ifndef UNTITLED_INTERSECT_H
#define UNTITLED_INTERSECT_H

#endif //UNTITLED_INTERSECT_H

#pragma once

namespace rt
{
    class material;

struct hitInfo
    {
    lvgm::precision _t;        //ray 中的系数t
    rtvec _p;                //相交点、撞击点
    rtvec _n;                //_p点的表面法线
    material* materialp;    //材质
    };

class intersect
    {
public:
    intersect() {  }

    /*
    @brief: 撞击函数，求取撞击点相关记录信息
    @param: sight->视线
    系数t的上下界->筛选撞击点
    rec->返回撞击点信息
    @retur: 是否存在合法撞击点
    */
    virtual bool hit(const ray& sight, rtvar t_min, rtvar t_max, hitInfo& rec)const = 0;

    virtual ~intersect() {  }
    };

}