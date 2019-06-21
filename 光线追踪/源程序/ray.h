//
// Created by hdutyq on 2019/5/30.
//


#pragma once

#include "RTdef.h"

namespace rt
{

    class ray
    {
    public:
        ray()
                :_a{ rtvec() }
                , _b{ rtvec() }
        {  }

        ray(const rtvec& a, const rtvec& b)
                :_a(a)
                , _b(b)
        {  }

        ray(const ray& r)
                :_a(r._a)
                , _b(r._b)
        {    }

        inline rtvec origin()const { return _a; }

        inline rtvec direction()const { return _b; }

        inline rtvec go(const rtvar t)const { return _a + t * _b; }

    private:
        rtvec _a;

        rtvec _b;

    };
}