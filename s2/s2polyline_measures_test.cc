// Copyright 2018 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS-IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Author: ericv@google.com (Eric Veach)

#include "third_party/s2/s2polyline_measures.h"

#include <cmath>
#include <vector>

#include "gtest/gtest.h"
#include "third_party/s2/s1angle.h"
#include "third_party/s2/s2testing.h"

using std::fabs;
using std::vector;

namespace s2 {

TEST(GetLengthAndCentroid, GreatCircles) {
  // Construct random great circles and divide them randomly into segments.
  // Then make sure that the length and centroid are correct.  Note that
  // because of the way the centroid is computed, it does not matter how
  // we split the great circle into segments.

  for (int iter = 0; iter < 100; ++iter) {
    // Choose a coordinate frame for the great circle.
    S2Point x, y, z;
    S2Testing::GetRandomFrame(&x, &y, &z);

    vector<S2Point> line;
    for (double theta = 0; theta < 2 * M_PI;
         theta += pow(S2Testing::rnd.RandDouble(), 10)) {
      line.push_back(std::cos(theta) * x + std::sin(theta) * y);
    }
    // Close the circle.
    line.push_back(line[0]);
    S1Angle length = GetLength(line);
    EXPECT_LE(fabs(length.radians() - 2 * M_PI), 2e-14);
    S2Point centroid = GetCentroid(line);
    EXPECT_LE(centroid.Norm(), 2e-14);
  }
}

}  // namespace s2
