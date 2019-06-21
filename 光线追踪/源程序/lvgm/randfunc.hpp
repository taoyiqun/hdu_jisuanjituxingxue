//
// Created by hdutyq on 2019/5/30.
//

#ifndef UNTITLED_RANDFUNC_HPP
#define UNTITLED_RANDFUNC_HPP

#endif //UNTITLED_RANDFUNC_HPP
#pragma once

#include "type_vec\type_vec.h"
#include <random>

namespace lvgm
{

//@brief:    create a random number that from 0 to 1 completely
    template<typename T = lvgm::precision>
    const T rand01()
    {
        if (typeid(T) == typeid(int))
        {
            std::cerr << "integer doesn't have a random number from 0 to 1\n";
            throw "integer doesn't have a random number from 0 to 1\n";
        }

        static std::mt19937 mt;
        static std::uniform_real_distribution<T> r;
        return r(mt);
    }


//@brief:    find a random point in unit_sphere
    template<typename T = lvgm::precision>
    const lvgm::vec3<T> random_unit_sphere()
    {
        if (typeid(T) == typeid(int))
        {
            std::cerr << "integer doesn't have a random number from 0 to 1\n";
            throw "integer doesn't have a random number from 0 to 1\n";
        }

        lvgm::vec3<T> p;
        do
        {
            p = 2.0*lvgm::vec3<T>(rand01(), rand01(), rand01()) - lvgm::vec3<T>(1, 1, 1);
        } while (dot(p, p) >= 1.0);
        return p;
    }


//@brief:    find a random point in unit_plane
    template<typename T = lvgm::precision>
    const lvgm::vec2<T> random_unit_plane()
    {
        if (typeid(T) == typeid(int))
        {
            std::cerr << "integer doesn't have a random number from 0 to 1\n";
            throw "integer doesn't have a random number from 0 to 1\n";
        }

        lvgm::vec2<T> p;
        do
        {
            p = 2.0*lvgm::vec2<T>(rand01(), rand01()) - lvgm::vec2<T>(1, 1);
        } while (dot(p, p) >= 1.0);
        return p;
    }

}