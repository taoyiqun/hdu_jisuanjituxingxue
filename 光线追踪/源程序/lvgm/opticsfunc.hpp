//
// Created by hdutyq on 2019/5/30.
//

#ifndef UNTITLED_OPTICSFUNC_HPP
#define UNTITLED_OPTICSFUNC_HPP

#endif //UNTITLED_OPTICSFUNC_HPP


#pragma once

#include "type_vec\type_vec.h"
#include <typeinfo>
namespace lvgm
{

    /*
    @in:    the Incident light
    @n:    the Surface normal
    @ret:    the reflected light
    */
    template<typename T>
    const T reflect(const T& in, const T& n)
    {
        return in - 2 * dot(in, n)*n;
    }



    /*
    @in:    the Incident light
    @n:    the Surface normal
    @eta:    the Refractive indices
    @ret:    if it has a refracted light or not
    */
    template<typename T>
    const bool refract(const T& in, const T& n, lvgm::precision eta, T& refracted)
    {
        if (typeid(T) == typeid(lvgm::vec2<int>))
        {
            std::cerr << "the refract is adapted to float and percision-upper\n";
            return false;
        }

        T unitIn = in.ret_unitization();    //将入射光线单位化

        lvgm::precision cos1 = dot(-unitIn, n);
        lvgm::precision cos2 = 1. - eta*eta*(1. - cos1*cos1);
        if (cos2 > 0)
        {
            refracted = eta * unitIn + n * (eta * cos1 - std::sqrt(cos2));
            return true;
        }
        return false;
    }
}