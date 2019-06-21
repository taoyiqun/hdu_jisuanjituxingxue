//
// Created by hdutyq on 2019/5/30.
//

#include "material.h"
#include "RTdef.h"
#include "ray.h"
#include "intersect.h"

#ifndef UNTITLED_DIFFUSE_HPP
#define UNTITLED_DIFFUSE_HPP

#endif //UNTITLED_DIFFUSE_HPP

#pragma once

namespace rt
{
//diffuse material
    class lambertian : public material
    {
    public:
        lambertian(const rtvec& a) :_albedo(a) {  }

        bool scatter(const ray& rIn, const hitInfo& info, rtvec& attenuation, ray& scattered)const override
        {
            rtvec target = info._p + info._n + lvgm::random_unit_sphere();
            scattered = ray{ info._p, target - info._p };
            attenuation = _albedo;
            return true;
        }
    protected:

        rtvec _albedo;
    };

}