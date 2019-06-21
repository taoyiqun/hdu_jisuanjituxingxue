//
// Created by hdutyq on 2019/5/30.
//

#include "material.h"

#ifndef UNTITLED_METAL_HPP
#define UNTITLED_METAL_HPP

#endif //UNTITLED_METAL_HPP

#pragma once

namespace rt
{
//metal material
    class metal :public material
    {
    public:

        metal(const rtvec& a, const rtvar f = 0.) :_albedo(a)
        {
            if (f < 1 && f >= 0)_fuzz = f;
            else _fuzz = 1;
        }

        virtual bool scatter(const ray& rIn, const hitInfo& info, rtvec& attenuation, ray& scattered)const
        {
            rtvec target = reflect(rIn.direction().ret_unitization(), info._n);
            scattered = ray{ info._p, target + _fuzz * lvgm::random_unit_sphere() };
            attenuation = _albedo;
            return dot(scattered.direction(), info._n) != 0;
        }

        inline static rtvec reflect(const rtvec& in, const rtvec& n) { return in - 2 * dot(in, n)*n; }

    protected:

        rtvec _albedo;

        rtvar _fuzz;
    };

}