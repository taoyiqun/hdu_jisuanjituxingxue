#define LOWPRECISION

#include <fstream>
#include "RTmaterial.h"
#include "RThit.h"
#include "camera.h"
#define stds std::
using namespace rt;

rtvec lerp(const ray& sight, intersect* world, int depth)
{
    hitInfo info;
    if (world->hit(sight, (rtvar)0.001, rtInf(), info))
    {
        ray scattered;
        rtvec attenuation;
        if (depth < 50 && info.materialp->scatter(sight, info, attenuation, scattered))
            return attenuation * lerp(scattered, world, depth + 1);
        else
            return rtvec(0, 0, 0);
    }
    else
    {
        rtvec unit_dir = sight.direction().ret_unitization();
        rtvar t = 0.5*(unit_dir.y() + 1.);
        return (1. - t)*rtvec(1., 1., 1.) + t*rtvec(0.5, 0.7, 1.0);
    }
}

intersect* random_sphere()
{
    int cnt = 500;
    intersect **list = new intersect*[cnt + 1];
    list[0] = new sphere(rtvec(0, -1000, 0), 1000, new lambertian(rtvec(0.5, 0.5, 0.5)));
    int size = 1;
    for (int a = -11; a < 11; ++a)
        for (int b = -11; b < 11; ++b)
        {
            rtvar choose_mat = lvgm::rand01();
            rtvec center(a + 0.9 * lvgm::rand01(), 0.2, b + 0.9*lvgm::rand01());
            if ((center - rtvec(4, 0.2, 0)).normal()>0.9)
            {
                if (choose_mat < 0.45)
                {
                    list[size++] = new sphere(center, 0.2, new lambertian(rtvec(lvgm::rand01()*lvgm::rand01(), lvgm::rand01()*lvgm::rand01(), lvgm::rand01()*lvgm::rand01())));
                }
                else if (choose_mat < 0.9)
                {
                    list[size++] = new sphere(center, 0.2, new metal(rtvec(0.5*(1 + lvgm::rand01()), 0.5*(1 + lvgm::rand01()), 0.5*(1 + lvgm::rand01())), 0.5*lvgm::rand01()));
                }
                else
                {
                    list[size++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }

    list[size++] = new sphere(rtvec(0, 1, 0), 1.0, new dielectric(1.5));
    list[size++] = new sphere(rtvec(-4, 1, 0), 1.0, new lambertian(rtvec(0.4, 0.2, 0.1)));
    list[size++] = new sphere(rtvec(4, 1, 0), 1.0, new metal(rtvec(0.7, 0.6, 0.5), 0.));


    return new intersections(list, size);
}

void build_12_1()
{
    stds ofstream file("graph12-1.ppm");
    size_t W = 1980, H = 1080, sample = 1;

    if (file.is_open())
    {
        file << "P3\n" << W << " " << H << "\n255\n" << stds endl;

        intersect* world = random_sphere();

        rtvec lookfrom(13, 2, 3);
        rtvec lookat(0, 0, 0);
        float dist_to_focus = (lookfrom - lookat).normal();
        float aperture = 0.0;
        camera cma(lookfrom, lookat, rtvec(0, 1, 0), 20, rtvar(W) / rtvar(H), aperture, 0.7*dist_to_focus);

        for (int y = H - 1; y >= 0; --y)
            for (int x = 0; x < W; ++x)
            {
                rtvec color;
                for (int cnt = 0; cnt < sample; ++cnt)
                {
                    lvgm::vec2<rtvar> para{
                            (lvgm::rand01() + x) / W,
                            (lvgm::rand01() + y) / H };
                    color += lerp(cma.get_ray(para), world, 0);
                }
                color /= sample;
                color = rtvec(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));    //gamma 校正
                int r = int(255.99 * color.r());
                int g = int(255.99 * color.g());
                int b = int(255.99 * color.b());
                file << r << " " << g << " " << b << stds endl;
            }
        file.close();

        if (world)delete world;

        stds cout << "complished" << stds endl;
    }
    else
        stds cerr << "open file error" << stds endl;
}


int main()
{
    build_12_1();
}