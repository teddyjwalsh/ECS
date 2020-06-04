#pragma once
#ifndef GENERATION_ISLAND_H_
#define GENERATION_ISLAND_H_

#include <algorithm>
#include <vector>
#include <glm/glm.hpp>
#include <random>

#include "generation/simplex.h"

namespace generation
{

class Island
{
public:
    Island(int seed) :
        _seed(seed),
        _mountain(seed + 1, 0.05),
        _simplex2(seed + 2, 0.08),
        _simplex(seed + 3, 0.3),
        _simplex3(seed + 5, 2.0),
        _coarse_simplex(seed + 6, 8.0),
        _coarse_simplex_mod(seed + 7, 2.0),
        _radius(2560/2.0)
    {
        
	}

    std::vector<BlockType> get_chunk(int x, int y, int z,
        unsigned int size_x, unsigned int size_y, unsigned int size_z)
    {
        x = x + 5*128;
        z = z + 5*128;
        std::vector<int> out_vec;

        out_vec.reserve(size_x * size_z);
#ifdef FNSD
        _simp_noise = _simplex.get_points_2d(x, z, size_x);
        _simp_noise2 = _simplex2.get_points_2d(x, z, size_x);
        _simp_noise3 = _simplex3.get_points_2d(x, z, size_x);
        _coarse_simp_noise = _coarse_simplex.get_points_2d(x, z, size_x);
        _coarse_simp_noise_mod = _coarse_simplex_mod.get_points_2d(x, z, size_x);
        _mount_noise = _mountain.get_points_2d(x, z, size_x);
#endif  // FNSD
        bool b_contains = false;
        for (int i = 0; i < size_z; ++i)
        {
            for (int j = 0; j < size_y; ++j)
            {
                for (int k = 0; k < size_x; ++k)
                {
/*
                    if (y+j == 0)
                    { out_vec.push_back(1); b_contains = true; }
                    else
                    { out_vec.push_back(0); }
                    continue;
*/
#ifdef FNSD
                    float a = 10*std::max(-2.0f, float(log(10.5f * _simp_noise2[i + k * size_x])));
                    float b = pow(2.2 * (_mount_noise[i + k * size_x]+1), 3.2);
                    float c = 30 * (_simp_noise2[i + k * size_x]) + 8 * (_simp_noise[i + k * size_x]) + 2 * (_simp_noise3[i + k * size_x]);
                    float d = 2 * _coarse_simp_noise[i + k * size_x]*pow((_coarse_simp_noise_mod[i + k * size_x]), 2);
                    float r = glm::length(glm::vec2(x+k, z+i) - glm::vec2(_radius, _radius));
                    float val = (a+b+c+d)*10*std::pow((1.0 - r / _radius),2);
                    //val = 25 * (_simp_noise[i + k * (size_x)] + 1);

                    //if (y + j < val)
                    //{
                        //out_vec.push_back(2);
                    if (y + j == 0)
                    {
                        out_vec.push_back(4);
                        b_contains = true;
                    }
                    else if (y + j == 10 && y + j < val)
                    {
                        out_vec.push_back(21);
                        b_contains = true;
                    }
                    else if (y + j < 17 + 6 * sin(((x + k) ^ (z + i))) * cos((z + i) / 200.0) && y + j < val)
                    {
                        out_vec.push_back(4);
                        b_contains = true;
                    }
                    else if (y + j > 120+20*sin(((x+k)^(z+i)))*cos((z+i)/200.0) && y + j < val)
                    {
                        out_vec.push_back(2);
                        b_contains = true;
                    }
                    else if (y + j < val)
                    {
                        out_vec.push_back(1);
                        b_contains = true;
                    }
                    //}
                    else
                    {
                        if (y + j < 15)
                        {
                            out_vec.push_back(20);
                            b_contains = true;
                        }
                        else
                        {
                            out_vec.push_back(0);
                        }
                    }
#endif  // FNSD
                }
            }
        }
        if (!b_contains)
        {
            out_vec[0] = -1;
        }
        _simplex.free();
        _simplex2.free();
        _simplex3.free();
        _mountain.free();
        return out_vec;
    }

private:
    int _seed;
    tmc::Simplex _simplex;
    tmc::Simplex _simplex2;
    tmc::Simplex _simplex3;
    tmc::Simplex _coarse_simplex;
    tmc::Simplex _coarse_simplex_mod;
    tmc::Simplex _mountain;
    float* _simp_noise;
    float* _simp_noise2;
    float* _simp_noise3;
    float* _mount_noise;
    float* _coarse_simp_noise;
    float* _coarse_simp_noise_mod;
    float _radius;
};

}  // namespace generation

#endif  // GENERATION_ISLAND_H_
