//
// Created by hdutyq on 2019/5/30.
//

#include "intersect.h"

#ifndef UNTITLED_INTERSECTIONS_H
#define UNTITLED_INTERSECTIONS_H

#endif
#pragma once

namespace rt
{

    class intersections :public intersect
    {
    public:
        intersections() {  }

        intersections(intersect** list, size_t n) :_list(list), _size(n) {  }

        virtual bool hit(const ray& sight, rtvar t_min, rtvar t_max, hitInfo& rec)const override;

    private:
        intersect** _list;

        size_t _size;
    };


    bool intersections::hit(const ray& sight, rtvar t_min, rtvar t_max, hitInfo& rec)const
    {
        hitInfo t_rec;
        bool hitSomething = false;
        rtvar far = t_max;            //刚开始可以看到无限远
        for (int i = 0; i < _size; ++i)
        {
            if (_list[i]->hit(sight, t_min, far, t_rec))
            {
                hitSomething = true;
                far = t_rec._t;            //将上一次的最近撞击点作为视线可达最远处
                rec = t_rec;
            }
        }
        return hitSomething;
    }


}