// Copyright 2005 Google Inc. All Rights Reserved.
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

#include "s2/s2pointutil.h"

#include "gtest/gtest.h"
#include "s2/s2cell.h"
#include "s2/s2coords.h"
#include "s2/s2edge_distances.h"
#include "s2/s2latlng.h"
#include "s2/s2measures.h"
#include "s2/s2predicates.h"
#include "s2/s2testing.h"

namespace s2 {

TEST(S2, Frames) {
  Matrix3x3_d m;
  S2Point z = S2Point(0.2, 0.5, -3.3).Normalize();
  GetFrame(z, &m);
  EXPECT_TRUE(ApproxEquals(m.Col(2), z));
  EXPECT_TRUE(IsUnitLength(m.Col(0)));
  EXPECT_TRUE(IsUnitLength(m.Col(1)));
  EXPECT_DOUBLE_EQ(m.Det(), 1);

  EXPECT_TRUE(ApproxEquals(ToFrame(m, m.Col(0)), S2Point(1, 0, 0)));
  EXPECT_TRUE(ApproxEquals(ToFrame(m, m.Col(1)), S2Point(0, 1, 0)));
  EXPECT_TRUE(ApproxEquals(ToFrame(m, m.Col(2)), S2Point(0, 0, 1)));

  EXPECT_TRUE(ApproxEquals(FromFrame(m, S2Point(1, 0, 0)), m.Col(0)));
  EXPECT_TRUE(ApproxEquals(FromFrame(m, S2Point(0, 1, 0)), m.Col(1)));
  EXPECT_TRUE(ApproxEquals(FromFrame(m, S2Point(0, 0, 1)), m.Col(2)));
}

static void TestRotate(const S2Point& p, const S2Point& axis, S1Angle angle) {
  S2Point result = Rotate(p, axis, angle);

  // "result" should be unit length.
  EXPECT_TRUE(IsUnitLength(result));

  // "result" and "p" should be the same distance from "axis".
  double kMaxPositionError = 1e-15;
  EXPECT_LE((S1Angle(result, axis) - S1Angle(p, axis)).abs().radians(),
            kMaxPositionError);

  // Check that the rotation angle is correct.  We allow a fixed error in the
  // *position* of the result, so we need to convert this into a rotation
  // angle.  The allowable error can be very large as "p" approaches "axis".
  double axis_distance = p.CrossProd(axis).Norm();
  double max_rotation_error;
  if (axis_distance < kMaxPositionError) {
    max_rotation_error = 2 * M_PI;
  } else {
    max_rotation_error = asin(kMaxPositionError / axis_distance);
  }
  double actual_rotation = TurnAngle(p, axis, result) + M_PI;
  double rotation_error = remainder(angle.radians() - actual_rotation,
                                    2 * M_PI);
  EXPECT_LE(rotation_error, max_rotation_error);
}

TEST(S2, Rotate) {
  for (int iter = 0; iter < 1000; ++iter) {
    S2Point axis = S2Testing::RandomPoint();
    S2Point target = S2Testing::RandomPoint();
    // Choose a distance whose logarithm is uniformly distributed.
    double distance = M_PI * pow(1e-15, S2Testing::rnd.RandDouble());
    // Sometimes choose points near the far side of the axis.
    if (S2Testing::rnd.OneIn(5)) distance = M_PI - distance;
    S2Point p = InterpolateAtDistance(S1Angle::Radians(distance),
                                                  axis, target);
    // Choose the rotation angle.
    double angle = 2 * M_PI * pow(1e-15, S2Testing::rnd.RandDouble());
    if (S2Testing::rnd.OneIn(3)) angle = -angle;
    if (S2Testing::rnd.OneIn(10)) angle = 0;
    TestRotate(p, axis, S1Angle::Radians(angle));
  }
}

// Given a point P, return the minimum level at which an edge of some S2Cell
// parent of P is nearly collinear with Origin().  This is the minimum
// level for which Sign() may need to resort to expensive calculations in
// order to determine which side of an edge the origin lies on.
static int GetMinExpensiveLevel(const S2Point& p) {
  S2CellId id(p);
  for (int level = 0; level <= S2CellId::kMaxLevel; ++level) {
    S2Cell cell(id.parent(level));
    for (int k = 0; k < 4; ++k) {
      S2Point a = cell.GetVertex(k);
      S2Point b = cell.GetVertex(k + 1);
      if (s2pred::TriageSign(a, b, Origin(), a.CrossProd(b)) == 0) {
        return level;
      }
    }
  }
  return S2CellId::kMaxLevel + 1;
}

}  // namespace s2
