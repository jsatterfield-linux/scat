#ifndef SCAT2_HPP
#define SCAT2_HPP

// SCAT version 3.0.3

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <cmath>
#include "string.h"
#include <map>

const double PI = 3.141592; 
const std::string VERSION="3.0.3";

const int FLAGINT = -1;
    
const int MAXSPECIES = 2;
// This line is 120 for microsats and 2 for SNPs
// const int MAXNALLELE = 120; 
const int MARGIN = 7;  // margin around grid

typedef std::vector<double> DoubleVec1d;
typedef std::vector<DoubleVec1d> DoubleVec2d;
typedef std::vector<DoubleVec2d> DoubleVec3d;
typedef std::vector<DoubleVec3d> DoubleVec4d;
typedef std::vector<int> IntVec1d;
typedef std::vector<IntVec1d> IntVec2d;
typedef std::vector<IntVec2d> IntVec3d;
typedef std::vector<IntVec3d> IntVec4d;

const int ValidateAssumptions = 1;

const double EPSILON = 1e-100;

#endif  // SCAT2_HPP
