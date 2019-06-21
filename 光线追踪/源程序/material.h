//
// Created by hdutyq on 2019/5/30.
//

#include "ray.h"
#include "intersect.h"

#ifndef UNTITLED_METERIAL_H
#define UNTITLED_METERIAL_H

#endif //UNTITLED_METERIAL_H
#pragma once

namespace rt
{

//abstract basic class
    class material
    {
    public:

        /*
        @brief: produce a scattered ray
        @param: InRay -> Incident light
                info -> the information of intersect-point(hit-point)
                attenuation -> when scattered, how much the ray should be attenuated by tis reflectance R
                scattered -> as we talk, it is a new sight; or
                             it is the scattered ray with the intersect-point
        @retur: the function calculate a scattered ray or not
        */
        virtual bool scatter(const ray& InRay, const hitInfo& info, rtvec& attenuation, ray& scattered)const = 0;

    };

}