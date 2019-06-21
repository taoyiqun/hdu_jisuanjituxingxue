//
// Created by hdutyq on 2019/5/30.
//

#ifndef UNTITLED_RTF_H
#define UNTITLED_RTF_H

#endif //UNTITLED_RTF_H
#pragma once

#include "lvgm\type_vec\type_vec.h"
#include "lvgm\opticsfunc.hpp"
#include "lvgm\randfunc.hpp"

namespace rt
{
    using rtvar = lvgm::precision;

    using rtvec = lvgm::vec3<rtvar>;

    constexpr static rtvar rtInf() { return static_cast<rtvar>(0x3f3f3f3f); }        //最大值

    constexpr rtvar pi = 3.1415926;

}