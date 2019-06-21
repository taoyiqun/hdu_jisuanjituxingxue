//
// Created by hdutyq on 2019/5/30.
//

#include "material.h"

#ifndef UNTITLED_DIELECTRIC_HPP
#define UNTITLED_DIELECTRIC_HPP

#endif //UNTITLED_DIELECTRIC_HPP

#pragma once

namespace rt
{
    class dielectric :public material
    {
    public:
        dielectric(const rtvar RI) :_RI(RI) {  }

        virtual bool scatter(const ray& InRay, const hitInfo& info, rtvec& attenuation, ray& scattered)const override;

    protected:
        rtvar _RI;

        inline rtvar schlick(const rtvar cosine)const;
    };



    bool dielectric::scatter(const ray& InRay, const hitInfo& info, rtvec& attenuation, ray& scattered)const
    {
        rtvec outward_normal;
        rtvec refracted;
        rtvec reflected = reflect(InRay.direction(), info._n);
        rtvar eta;
        rtvar reflect_prob;
        rtvar cos;
        attenuation = rtvec(1., 1., 1.);

        if (dot(InRay.direction(), info._n) > 0)
        {
            outward_normal = -info._n;
            eta = _RI;
            cos = _RI * dot(InRay.direction(), info._n) / InRay.direction().normal();
        }
        else
        {
            outward_normal = info._n;
            eta = 1.0 / _RI;
            cos = -dot(InRay.direction(), info._n) / InRay.direction().normal();
        }

        if (refract(InRay.direction(), outward_normal, eta, refracted))
            reflect_prob = schlick(cos);    //如果有折射，计算反射系数
        else
            reflect_prob = 1.0;        //如果没有折射，那么为全反射

        if (lvgm::rand01() < reflect_prob)
            scattered = ray(info._p, reflected);
        else
            scattered = ray(info._p, refracted);

        return true;
    }

    inline rtvar dielectric::schlick(const rtvar cosine)const
    {
        rtvar r0 = (1. - _RI) / (1. + _RI);
        r0 *= r0;
        return r0 + (1 - r0)*pow((1 - cosine), 5);
    }
}