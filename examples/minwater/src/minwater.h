// --------------------------------------------
// Copyright KAPSARC. Open source MIT License.
// --------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015 King Abdullah Petroleum Studies and Research Center
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software
// and associated documentation files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// --------------------------------------------

#ifndef DEMO_WATERMIN_H
#define DEMO_WATERMIN_H

#include <assert.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>

#include "kutils.h"
#include "prng.h"
#include "kmatrix.h"
#include "gaopt.h"
#include "hcsearch.h"
#include "kmodel.h"

namespace DemoWaterMin {
// namespace to which KBase has no access

using std::string;
using std::tuple;
using std::vector;

using KBase::KMatrix;
using KBase::PRNG;

using KBase::Actor;
using KBase::Position;
using KBase::State;
using KBase::Model;
using KBase::VotingRule;
using KBase::ReportingLevel;

/// Define a hard-coded scenario
//const unsigned int numA = 4;
//const unsigned int numP = 4;

const double uArray[] = { // numA x numP
    0.0000, 0.8383, 0.7532, 0.9660,
    1.0000, 1.0000, 1.0000, 0.7500,
    1.0000, 0.0000, 0.7500, 0.0000,
    0.0000, 0.6107, 0.3407, 0.9027
};


const unsigned int numA = 38;
const unsigned int numP = 17;
// 38 rows/actors, 17 columns/positions
// Column 0 is the base-year, Column 1 is the 'nominal policy'
double u2Array[] = {
    0.0000 , 0.8383 , 0.7993 , 0.7532 , 0.6996 , 0.6514 , 0.8556 , 0.9141 , 0.9660 , 1.0000 , 0.8183 , 0.8512 , 0.8957 , 0.9763 , 0.6094 , 0.6160 , 0.7528 , // 01
    1.0000 , 0.0000 , 0.0058 , 0.0098 , 0.0169 , 0.0208 , 0.0205 , 0.1003 , 0.1952 , 0.7010 , 0.0262 , 0.1112 , 0.2107 , 0.5013 , 0.9712 , 0.6064 , 0.3459 , // 02
    1.0000 , 0.0000 , 0.0060 , 0.0102 , 0.0177 , 0.0218 , 0.0214 , 0.1047 , 0.2036 , 0.7232 , 0.0274 , 0.1161 , 0.2197 , 0.5200 , 0.9826 , 0.6274 , 0.3599 , // 03
    1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 0.9975 , 0.9375 , 0.7500 , 0.0000 , 0.9975 , 0.9375 , 0.7500 , 0.0000 , 0.7500 , 0.9999 , 0.9996 , // 04
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 05
    1.0000 , 0.0000 , 0.4375 , 0.7500 , 0.9375 , 0.9975 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.4375 , 0.7500 , 0.9375 , 0.9975 , 0.9975 , 0.7500 , 0.4375 , // 06
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 07
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 08
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 09
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 10
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.8387 , 0.9600 , 0.6400 , 0.3600 , // 11
    0.0930 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 0.0000 , 0.4486 , 1.0000 , // 12
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 13
    0.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , // 14
    0.0930 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 0.0000 , 1.0000 , 1.0000 , // 15
    0.2439 , 1.0000 , 1.0000 , 1.0000 , 0.9478 , 0.4554 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 0.1664 , 0.0000 , 0.9617 , // 16
    0.0000 , 0.8179 , 0.8270 , 0.8333 , 0.8442 , 0.8500 , 0.8495 , 0.9458 , 0.9985 , 0.9824 , 0.8578 , 0.9555 , 1.0000 , 1.0000 , 0.3324 , 0.3881 , 0.6568 , // 17
    0.3600 , 0.5637 , 0.1578 , 0.0000 , 0.0000 , 0.0000 , 0.6399 , 0.8715 , 0.9968 , 1.0000 , 0.2651 , 0.2382 , 0.3147 , 0.6399 , 0.2944 , 0.1536 , 0.0784 , // 18
    0.4762 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.3932 , 0.2088 , 0.1074 , // 19
    0.3600 , 1.0000 , 1.0000 , 0.4229 , 0.0000 , 0.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 0.2944 , 0.1536 , 0.0784 , // 20
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 21
    0.3600 , 1.0000 , 1.0000 , 1.0000 , 0.0000 , 0.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 0.2944 , 0.1536 , 0.0784 , // 22
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 23
    0.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , // 24
    0.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 0.9912 , 1.0000 , 1.0000 , // 25
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 26
    0.0930 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 0.0000 , 1.0000 , 1.0000 , // 27
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 28
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 29
    0.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , // 30
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 31
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 32
    0.3600 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 1.0000 , 0.0000 , 0.0000 , 0.0000 , 1.0000 , 0.2944 , 0.1536 , 0.0784 , // 33
    0.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , // 34
    1.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.0000 , 0.9600 , 0.6400 , 0.3600 , // 35
    0.0930 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 0.0000 , 1.0000 , 1.0000 , // 36
    0.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , // 37
    0.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000 , 1.0000   // 38
};

// all but the first are base-year total revenue
double w2Array[] {
   2000000.0 ,   // 01
    744645.7 ,   // 02
    369065.2 ,   // 03
    558530.62 ,  // 04
    126000.0 ,   // 05
    105623.2 ,   // 06
    602330.0 ,   // 07
    44558.6 ,    // 08
    16544.9 ,    // 09
    13349.8 ,    // 10
    857680.0 ,   // 11
    66344.0 ,    // 12
    76655.9 ,    // 13
    201451.7 ,   // 14
    44116.4 ,    // 15
    41444.3 ,    // 16
    469800.0 ,   // 17
    100017.5 ,   // 18
    199953.6 ,   // 19
    21577.1 ,    // 20
    7840.0 ,     // 21
    12394.8 ,    // 22
    35700.0 ,    // 23
    49397.2 ,    // 24
    23620.4 ,    // 25
    27200.0 ,    // 26
    14030.3 ,    // 27
    26520.0 ,    // 28
    807.5 ,      // 29
    28450.6 ,    // 30
    1352.0 ,     // 31
    1691.2 ,     // 32
    47359.2 ,    // 33
    44273.4 ,    // 34
    922.5 ,      // 35
    1173.3 ,     // 36
    8001.6 ,     // 37
    271.1        // 38
};

const double pArray[] = { 0.10, 0.80, 0.05, 0.05 }; // numP


double wArray[] = { 1600, 7000, 100, 1300 }; // numA


double trgtP0 = 0.90; // probability of base-year scenario (#0) when waterMin actor has little strength
double trgtP1 = 0.80; // probability of nominal-policy scenario (#1) when waterMin actor has full strength
double prmsW = 0.020; //  weight of RMS weight-factors, compared to weight 1 of RMS prob-error

const KMatrix w0 = KMatrix::arrayInit(w2Array, numA, 1);

const KMatrix uInit = KMatrix::arrayInit(u2Array, numA, numP);
const KMatrix pInit = KMatrix::arrayInit(pArray, numP, 1);



// -------------------------------------------------
// define a simple class of Linear Programs that
// minimize resource usage, subject to three kinds of constraints:
// 1: Bounds on reduction or growth of each item
//    (1-r)*x0 <= x <= (1+g)*x0
// 2: Bounds on reduction of portfolio components. 
//    For example, total livestock production cannot fall more than 5%.
//    dot(p, x) >= (1-r) * dot(p, x0)
// 3: Minimum supply-to-meet-demand constraints.
//    For example, Livestock creates demand for nutrition, fodder supplies nutrition, fodder/livestock ratio cannot decrease.
//    final fodder/livestock = dot(s,x)/dot(d,x) >= dot(s,x0)/dot(d,x0) = initial fodder/livestock
//    dot(s,x) * (dot(d, x0) / dot(s,x0)) >= dot(d, x)

class RsrcMinLP {
public:
  RsrcMinLP();
  virtual ~RsrcMinLP();
  static RsrcMinLP* makeRMLP(PRNG* rng, unsigned int numPd, unsigned int numPt);
  tuple<KMatrix, KMatrix> makeMq() const;

  unsigned int numProd; // number of products
  KMatrix xInit;
  KMatrix rCosts;
  KMatrix bounds;
  // first column is max reduction fraction, second is max growth
  // i.e. (1-ri)*xInit <= x <= (1+gi)*xInit
  // Note that -1 <= gi < 0 is allowed to force reductions, provided
  // that 0 <= (1-r1) <= (1+gi)
  unsigned int numPortC; // number of portfolio constraints
  KMatrix portWghts; // matrix of portfolio weights (all non-negative, probably all 0 or 1)
  KMatrix portRed; // column vector of max reduction fractions
  
  unsigned int numSpplyC; // number of supply constraints
  KMatrix spplyWghts; // matrix of supply weights (all non-negative, probably all 0 or 1)
  KMatrix dmndWghts; // matrix of demand weights (all non-negative, probably all 0 or 1)
  
  vector<string> pNames; // product names

protected:
private:
  void clear();

};

}; // end of namespace

// -------------------------------------------------
#endif
// --------------------------------------------
// Copyright KAPSARC. Open source MIT License.
// --------------------------------------------
