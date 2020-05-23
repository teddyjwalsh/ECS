#ifndef TMC_SIMPLEX_H_
#define TMC_SIMPLEX_H_

#pragma once

#include <algorithm>

#include "FastNoiseSIMD/FastNoiseSIMD.h"
#include "generation/generator.h"

namespace tmc
{

class Simplex :
    public Generator
{
 public:
    FastNoiseSIMD* myNoise;
    float* noiseSet;
    float scale;

 public:
    explicit Simplex(int in_seed, float in_scale = 0);
    ~Simplex();

    float get_point(int in_x, int in_y, int in_z) override;
    float get_point_2d(int in_x, int in_y) override;
    float * get_points(int in_x, int in_y, int in_z, int division) override;
    float * get_points_2d(int in_x, int in_y, int division) override;
    void set_scales(int in_x, int in_y, int in_z);
    void free();
};


}  // namespace tmc

#endif  // TMC_SIMPLEX_H_
