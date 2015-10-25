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

#ifndef DEMO_WATERMIN_SCEN_H
#define DEMO_WATERMIN_SCEN_H

#include "kutils.h"
#include "prng.h"
#include "kmatrix.h"

// --------------------------------------------
// The first row is percentage decline in water, compared to scenario 0.
// Each following row is the tons/year of the corresponding product
// --------------------------------------------

namespace DemoWaterMin {
  using KBase::KMatrix;
  // 38 rows, 27 columns
  //0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15 , 16 , 17 , 18 , 19 , 20 , 21 , 22 , 23 , 24 , 25 , 26
  const double scenQuantArray[] = {
    0.0, 16.7946033487, 15.4958220400, 14.1324053729, 12.6907952775, 11.5022790889, 17.4053031696, 22.9016018373, 28.0786254161, 16.1065218678, 17.2505399647, 19.0052577898, 23.7595155634, 10.5288011747, 10.6826059248, 14.1225177514, 55.7993867603, 15.9037256808, 18.5399796726, 19.8481025930, 21.7902526034, 24.8691413358, 35.4857328146, 47.1452012761, 60.6003322715, 61.2461096007, 68.8942043503,
    2659449, 2125256.67, 2126795.54, 2127874.47, 2129788.88, 2130852.23, 2130754, 2180229.97, 2367355.73, 2132292.87, 2155821.07, 2184846.6, 2282212.26, 2568762.66, 2324302.5, 2227422.8, 0, 2157018.13832099, 1994586.75, 2152743.32, 1994586.75, 1994586.75, 1117448.09618236, 0, 132972.45, 664862.25, 0,
    1318090, 1062628.33, 1063397.77, 1063937.23, 1064894.44, 1065426.11, 1065377, 1090114.99, 1183677.86, 1066146.44, 1077910.53, 1092423.3, 1141106.13, 1284381.33, 1162151.25, 1113711.4, 0, 1078509.0691605, 988567.5, 1076371.66, 988567.5, 988567.5, 558724.048091179, 0, 65904.5, 329522.5, 0,
    1095158, 1095158, 1095158, 1095158, 1095158, 1095158, 1040400.1, 547579, 0, 1040400.1, 821368.5, 547579, 0, 547579, 1084206.42, 1073254.84, 1095158, 821368.5, 1095158, 821368.5, 821368.5, 821368.5, 1095158, 1095158, 1095158, 273789.5, 54757.9,
    360000, 270000, 270000, 270000, 270000, 270000, 270000, 270000, 270000, 270000, 270000, 270000, 270000, 342000, 306000, 288000, 18000, 270000, 270000, 270000, 270000, 270000, 90000, 270000, 18000, 90000, 18000,
    660145, 0, 165036.25, 330072.5, 495108.75, 627137.75, 0, 0, 0, 165036.25, 330072.5, 495108.75, 627137.75, 627137.75, 330072.5, 165036.25, 0, 495108.75, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1943000, 1457250, 1457250, 1457250, 1457250, 1457250, 1457250, 1457250, 1457250, 1457250, 1457250, 1457250, 1457250, 1845850, 1651550, 1554400, 0, 1457250, 1457250, 1457250, 1457250, 3886000, 485750, 3886000, 7682500.27578485, 6893812.81592716, 0,
    99019, 74264.25, 74264.25, 74264.25, 74264.25, 74264.25, 74264.25, 74264.25, 74264.25, 74264.25, 74264.25, 74264.25, 74264.25, 94068.05, 84166.15, 79215.2, 4950.95, 74264.25, 74264.25, 74264.25, 74264.25, 74264.25, 24754.75, 74264.25, 4950.95, 24754.75, 4950.95,
    110299, 82724.25, 82724.25, 82724.25, 82724.25, 82724.25, 82724.25, 82724.25, 82724.25, 82724.25, 82724.25, 82724.25, 82724.25, 104784.05, 93754.15, 88239.2, 5514.95, 82724.25, 82724.25, 82724.25, 82724.25, 82724.25, 27574.75, 82724.25, 5514.95, 27574.75, 5514.95,
    95356, 71517, 71517, 71517, 71517, 71517, 71517, 71517, 71517, 71517, 71517, 71517, 71517, 90588.2, 81052.6, 76284.8, 4767.8, 71517, 71517, 71517, 71517, 71517, 23839, 71517, 4767.8, 23839, 4767.8,
    604000, 453000, 453000, 453000, 453000, 453000, 453000, 453000, 453000, 453000, 453000, 453000, 543348.43, 573800, 513400, 483200, 2416000, 453000, 453000, 453000, 453000, 453000, 151000, 1208000, 30200, 151000, 2416000,
    390259, 780518, 780518, 780518, 780518, 780518, 780518, 780518, 780518, 780518, 780518, 780518, 780518, 370746.05, 476241.06, 780518, 1561036, 780518, 780518, 780518, 780518, 292694.25, 1170777, 780518, 19512.95, 97564.75, 1561036,
    134484, 100863, 100863, 100863, 100863, 100863, 100863, 100863, 100863, 100863, 100863, 100863, 100863, 127759.8, 114311.4, 107587.2, 6724.2, 100863, 100863, 100863, 100863, 100863, 33621, 100863, 6724.2, 33621, 6724.2,
    544464, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 1088928, 2177856, 1088928, 1088928, 1088928, 1088928, 594562.937427576, 1633392, 1088928, 27223.2, 136116, 2177856,
    401058, 802116, 802116, 802116, 802116, 802116, 802116, 802116, 802116, 802116, 802116, 802116, 802116, 381005.1, 802116, 802116, 1604232, 802116, 802116, 802116, 802116, 300793.5, 1203174, 802116, 20052.9, 100264.5, 1604232,
    230246, 460492, 460492, 460492, 400020.76, 265090.58, 460492, 460492, 460492, 460492, 460492, 460492, 460492, 218733.7, 195709.1, 408679.31, 920984, 460492, 460492, 460492, 460492, 172684.5, 690738, 460492, 11512.3, 57561.5, 920984,
    174000, 273742.03, 275632.3, 276957.6, 279309.17, 280615.33, 280494.67, 341268.49, 324918.99, 282384.95, 311285.81, 346939.32, 348000, 205830.62, 211893.97, 246064.8, 669929.399999998, 312756.230206593, 228119.481000428, 307505.26, 275359.87015641, 130500, 522000, 130500, 50398.0742151536, 89475.4340728349, 696000,
    526408, 618188.97, 448954.14, 394806, 394806, 394806, 657948.23, 1015781.55, 1052816, 488713.39, 478515.59, 508077.04, 657979.44, 500087.6, 447446.8, 421126.4, 26320.4, 394806, 717615.1208, 816985.26, 991404.6208, 394806, 1571675.48678086, 394806, 26320.4, 131602, 334010.700000001,
    240908, 180681, 180681, 180681, 180681, 180681, 180681, 180681, 398696.42, 180681, 180681, 180681, 180681, 228862.6, 204771.8, 192726.4, 0, 180681, 303418.148199572, 180681, 256177.759043589, 481816, 60227, 481816, 963632, 963632, 0,
    119873, 239746, 239746, 125914.2, 89904.75, 89904.75, 239746, 239746, 239746, 239746, 239746, 239746, 239746, 113879.35, 101892.05, 95898.4, 5993.65, 155153.312311915, 239746, 239746, 239746, 89904.75, 359619, 89904.75, 5993.65, 29968.25, 479492,
    14000, 10500, 10500, 10500, 10500, 10500, 10500, 10500, 10500, 10500, 10500, 10500, 10500, 13300, 11900, 11200, 700, 10500, 10500, 10500, 10500, 10500, 3500, 10500, 700, 3500, 700,
    59023, 118046, 118046, 118046, 44267.25, 44267.25, 118046, 118046, 118046, 118046, 118046, 118046, 118046, 56071.85, 50169.55, 47218.4, 2951.15, 118046, 118046, 118046, 118046, 44267.25, 177069, 44267.25, 2951.15, 14755.75, 236092,
    105000, 78750, 78750, 78750, 78750, 78750, 78750, 78750, 78750, 78750, 78750, 78750, 78750, 99750, 89250, 84000, 0, 78750, 78750, 78750, 78750, 210000, 26250, 210000, 420000, 420000, 0,
    246986, 493972, 493972, 493972, 493972, 493972, 493972, 493972, 493972, 493972, 493972, 493972, 493972, 493972, 493972, 493972, 987944, 493972, 493972, 493972, 493972, 493972, 740958, 493972, 987944, 987944, 987944,
    112478, 224956, 224956, 224956, 224956, 224956, 224956, 224956, 224956, 224956, 224956, 224956, 224956, 214391.53, 224956, 224956, 449912, 224956, 224956, 224956, 224956, 224956, 337434, 224956, 449912, 449912, 449912,
    80000, 60000, 60000, 60000, 60000, 60000, 60000, 60000, 60000, 60000, 60000, 60000, 60000, 76000, 68000, 64000, 0, 60000, 60000, 60000, 60000, 160000, 20000, 160000, 320000, 320000, 0,
    56121, 112242, 112242, 112242, 112242, 112242, 112242, 112242, 112242, 112242, 112242, 112242, 112242, 53314.95, 112242, 112242, 224484, 112242, 112242, 112242, 112242, 42090.75, 168363, 112242, 2806.05, 14030.25, 224484,
    68000, 51000, 51000, 51000, 51000, 51000, 51000, 51000, 51000, 51000, 51000, 51000, 51000, 64600, 57800, 54400, 0, 51000, 51000, 51000, 51000, 51000, 17000, 84805, 3400, 17000, 0,
    4486, 3364.5, 3364.5, 3364.5, 3364.5, 3364.5, 3364.5, 3364.5, 3364.5, 3364.5, 3364.5, 3364.5, 3364.5, 4261.7, 3813.1, 3588.8, 224.3, 3364.5, 3364.5, 3364.5, 3364.5, 3364.5, 1121.5, 3364.5, 224.3, 1121.5, 224.3,
    44454, 88908, 88908, 88908, 88908, 88908, 88908, 88908, 88908, 88908, 88908, 88908, 88908, 88908, 88908, 88908, 177816, 88908, 88908, 88908, 88908, 33340.5, 133362, 88908, 2222.7, 11113.5, 177816,
    11267, 8450.25, 8450.25, 8450.25, 8450.25, 8450.25, 8450.25, 8450.25, 8450.25, 8450.25, 8450.25, 8450.25, 8450.25, 10703.65, 9576.95, 9013.6, 563.35, 8450.25, 8450.25, 8450.25, 8450.25, 8450.25, 2816.75, 8450.25, 563.35, 2816.75, 563.35,
    2487, 1865.25, 1865.25, 1865.25, 1865.25, 1865.25, 1865.25, 1865.25, 1865.25, 1865.25, 1865.25, 1865.25, 1865.25, 2362.65, 2113.95, 1989.6, 124.35, 1865.25, 1865.25, 1865.25, 1865.25, 1865.25, 621.75, 1865.25, 124.35, 621.75, 124.35,
    22552, 16914, 16914, 16914, 16914, 16914, 16914, 16914, 45104, 16914, 16914, 16914, 45104, 21424.4, 19169.2, 18041.6, 90208, 16914, 45104, 16914, 45104, 21581.8125724236, 31557.3689455995, 45104, 90208, 90208, 90208,
    16277, 32554, 32554, 32554, 32554, 32554, 32554, 32554, 32554, 32554, 32554, 32554, 32554, 32554, 32554, 32554, 65108, 32554, 32554, 32554, 32554, 32554, 48831, 32554, 65108, 65108, 65108,
    2050, 1537.5, 1537.5, 1537.5, 1537.5, 1537.5, 1537.5, 1537.5, 1537.5, 1537.5, 1537.5, 1537.5, 1537.5, 1947.5, 1742.5, 1640, 102.5, 1537.5, 1537.5, 1537.5, 1537.5, 1537.5, 512.5, 1537.5, 102.5, 512.5, 102.5,
    7822, 15644, 15644, 15644, 15644, 15644, 15644, 15644, 15644, 15644, 15644, 15644, 15644, 7430.9, 15644, 15644, 31288, 15644, 15644, 15644, 15644, 15644, 23466, 15644, 31288, 31288, 31288,
    3334, 6668, 6668, 6668, 6668, 6668, 6668, 6668, 6668, 6668, 6668, 6668, 6668, 6668, 6668, 6668, 13336, 6668, 6668, 6668, 6668, 6668, 10002, 6668, 13336, 13336, 13336,
    108, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 432, 216, 216, 216, 216, 216, 324, 216, 432, 432, 432
  };

  const KMatrix scenQuant = KMatrix::arrayInit(scenQuantArray, 38, 27);

  // row 0: waterchange 
  // row 3: Dates
  // row 5: Wheat

  // So scenarios with at least 75% cut to water and at most 5% cut to dates
  // are those with date_i/date_0 >= 0.9499 and wheat_i/wheat_0 <= 0.2501

  vector<unsigned int> likelyScenarios;
  void setLikelyScenarios(const KMatrix & scen);

  KMatrix uInit;
  void setUInit(const KMatrix* sq);


}; // end of namespace
// --------------------------------------------
#endif
// --------------------------------------------
// Copyright KAPSARC. Open source MIT License.
// --------------------------------------------
