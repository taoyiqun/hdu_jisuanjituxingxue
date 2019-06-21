cmake_minimum_required(VERSION 3.13)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp lvgm/type_vec/lv_vec2.h lvgm/type_vec/lv_vec3.h lvgm/type_vec/type_vec.h lvgm/type_vec/vec_inout.h lvgm/lv_precision.h lvgm/lvgm.h ray.h lvgm/opticsfunc.hpp lvgm/randfunc.hpp RTdef.h camera.h intersect.h intersections.hpp sphere.hpp RThit.h material.h diffuse.hpp metal.hpp dielectric.hpp RTmaterial.h)