// Copyright 2019 Alexander Liniger

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

#ifndef MPCC_CONFIG_H
#define MPCC_CONFIG_H

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>

namespace mpcc{

// #define MAX(a,b) (a < b) ? b : a

#define NX 7
#define NU 3

#define NB 10 // Number of bounds
#define NPC 3 // Number of polytopic constraints
#define NS 1 // Number of slack variables

static constexpr int N = 40;
static constexpr double INF = 1E5;
static constexpr int N_SPLINE = 5000;

struct StateInputIndex{
    int X = 0;
    int Y = 1;
    int th = 2;
    int v = 3;
    int w = 4;
    int s = 5;
    int vs = 6;

    int dV = 0;
    int dW = 1;
    int dVs = 2;

    int con_track = 0;
    int con_leftwheel = 1;
    int con_rightwheel = 2;
};

static const StateInputIndex si_index;

}
#endif //MPCC_CONFIG_H
