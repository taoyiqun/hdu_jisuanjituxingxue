//
// Created by hdutyq on 2019/5/30.
//

#ifndef UNTITLED_LV_PRECISION_H
#define UNTITLED_LV_PRECISION_H
 //UNTITLED_LV_PRECISION_H
#pragma once



namespace lvgm
{

#    ifdef HIGHPRECISION            //set the high precision
    using precision = long double;

#    elif(defined LOWPRECISION)    //set the low preciion
    using precision = float;

#    else
    using precision = double;        //default precision

#    endif                        //set precision


}    //namespace lvgm

#endif        //LV_PRECISION_H
