//
// Created by hdutyq on 2019/5/30.
//

#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H

#endif //UNTITLED_CAMERA_H


#pragma once

#include "ray.h"

namespace rt
{

    class camera
    {
    public:
        camera(rtvec lookfrom, rtvec lookat, rtvec vup, rtvar vfov, rtvar aspect, rtvar aperture, rtvar focus)
                :_eye(lookfrom)
                , _lens_radius(aperture / 2)
        {
            rtvar theta = vfov * pi / 180;
            rtvar half_height = tan(theta / 2) * focus;        //tan(theta/2) = (height/2) / 焦距
            rtvar half_width = aspect * half_height;
            _w = (lookfrom - lookat).ret_unitization();
            _u = cross(vup, _w).ret_unitization();
            _v = cross(_w, _u);

            //向量运算
            _start = _eye - half_width * _u - half_height * _v - focus * _w;//高和宽都乘了焦距，w也要乘，不然公式是错的
            _horizontal = 2 * half_width * _u;
            _vertical = 2 * half_height * _v;
        }

        const ray get_ray(const rtvar u, const rtvar v)const
        {
            rtvec rd = rtvec(_lens_radius * lvgm::random_unit_plane());
            rtvec offset = _u * rd.x() + _v * rd.y();
            return ray{ _eye + offset, _start + u*_horizontal + v*_vertical - (_eye + offset) };
        }

        const ray get_ray(const lvgm::vec2<rtvar>& para)const    {    return get_ray(para.u(), para.v());    }

        inline const rtvec& eye()const { return _eye; }

        inline const rtvec& start()const { return _start; }

        inline const rtvec& horizontal()const { return _horizontal; }

        inline const rtvec& vertical()const { return _vertical; }

        inline const rtvec& u()const { return _u; }

        inline const rtvec& v()const { return _v; }

        inline const rtvec& w()const { return _w; }

        inline const rtvar lens_r()const { return _lens_radius; }

    private:
        rtvec _u;

        rtvec _v;

        rtvec _w;

        rtvec _eye;

        rtvec _start;        //left-bottom

        rtvec _horizontal;

        rtvec _vertical;

        rtvar _lens_radius;  //the radius of lens

    };

}