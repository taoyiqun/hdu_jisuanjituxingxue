//
// Created by hdutyq on 2019/5/30.
//

#include "intersect.h"

#ifndef UNTITLED_SPHERE_H
#define UNTITLED_SPHERE_H

#endif //UNTITLED_SPHERE_H
#pragma once

namespace rt
{

    class sphere :public intersect
    {
    public:
        sphere() {  }

        /*
        @para1: 球心坐标
        @para2: 球半径
        @para3: 材质
        */
        sphere(const rtvec& h, rtvar r, material* ma) :_heart(h), _radius(r), _materialp(ma) {  }

        ~sphere() { if (_materialp)    delete _materialp; }

        virtual bool hit(const ray& sight, rtvar t_min, rtvar t_max, hitInfo& rec)const override;

        inline const rtvar r()const            { return _radius;    }

        inline const rtvec& heart()const    { return _heart;    }

        inline rtvar& r()                    { return _radius;    }

        inline rtvec& heart()                { return _heart;    }

    private:
        rtvec _heart;

        rtvar _radius;

        material* _materialp;
    };



    bool sphere::hit(const ray& sight, rtvar t_min, rtvar t_max, hitInfo& rec)const
    {
        rtvec trace = sight.origin() - _heart;
        rtvar a = dot(sight.direction(), sight.direction());
        rtvar b = 2.0 * dot(trace, sight.direction());
        rtvar c = dot(trace, trace) - _radius * _radius;
        rtvar delt = b*b - 4.0*a*c;
        if (delt > 0)
        {
            rec.materialp = _materialp;
            rtvar x = (-b - sqrt(delt)) / (2.0*a);
            if (x < t_max && x > t_min)
            {
                rec._t = x;
                rec._p = sight.go(rec._t);
                rec._n = (rec._p - _heart) / _radius;
                return true;
            }
            x = (-b + sqrt(delt)) / (2.0*a);
            if (x < t_max && x > t_min)
            {
                rec._t = x;
                rec._p = sight.go(x);
                rec._n = (rec._p - _heart) / _radius;
                return true;
            }
        }
        return false;
    }

}