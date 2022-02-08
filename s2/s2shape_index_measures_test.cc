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
//
// Note that the "real" testing of these methods is in s2loop_measures_test
// and s2polyline_measures_test.  This file only checks the handling of
// multiple shapes and shapes of different dimensions.

#include "s2//s2shape_index_measures.h"

#include "gtest/gtest.h"
#include "absl/memory/memory.h"
#include "s2//mutable_s2shape_index.h"
#include "s2//s2lax_polygon_shape.h"
#include "s2//s2lax_polyline_shape.h"
#include "s2//s2point_vector_shape.h"
#include "s2//s2pointutil.h"
#include "s2//s2text_format.h"

using absl::make_unique;
using s2::s2textformat::MakeIndexOrDie;

namespace s2 {

TEST(GetDimension, Empty) {
  EXPECT_EQ(-1, GetDimension(*MakeIndexOrDie("# #")));
}

TEST(GetDimension, Points) {
  EXPECT_EQ(0, GetDimension(*MakeIndexOrDie("0:0 # #")));

  // Create an index with an empty point set.
  MutableS2ShapeIndex index;
  index.Add(make_unique<S2PointVectorShape>());
  EXPECT_EQ(0, GetDimension(index));
}

TEST(GetDimension, PointsAndLines) {
  EXPECT_EQ(1, GetDimension(*MakeIndexOrDie("0:0 # 1:1, 1:2 #")));

  // Note that a polyline with one vertex has no edges, so it is effectively
  // empty for the purpose of testing GetDimension().
  EXPECT_EQ(1, GetDimension(*MakeIndexOrDie("0:0 # 1:1 #")));
}

TEST(GetDimension, PointsLinesAndPolygons) {
  EXPECT_EQ(2, GetDimension(*MakeIndexOrDie(
      "0:0 # 1:1, 2:2 # 3:3, 3:4, 4:3")));

  EXPECT_EQ(2, GetDimension(*MakeIndexOrDie("# # empty")));
}

TEST(GetNumPoints, Empty) {
  EXPECT_EQ(0, GetNumPoints(*MakeIndexOrDie("# #")));
}

TEST(GetNumPoints, TwoPoints) {
  EXPECT_EQ(2, GetNumPoints(*MakeIndexOrDie("0:0 | 1:0 # #")));
}

TEST(GetNumPoints, LineAndPolygon) {
  EXPECT_EQ(0, GetNumPoints(*MakeIndexOrDie(
      "# 1:1, 1:2 # 0:3, 0:5, 2:5")));
}

TEST(GetLength, Empty) {
  EXPECT_EQ(S1Angle::Zero(), GetLength(*MakeIndexOrDie("# #")));
}

TEST(GetLength, TwoLines) {
  EXPECT_EQ(S1Angle::Degrees(2), GetLength(*MakeIndexOrDie(
      "4:4 # 0:0, 1:0 | 1:0, 2:0 # 5:5, 5:6, 6:5")));
}

TEST(GetPerimeter, Empty) {
  EXPECT_EQ(S1Angle::Zero(), GetPerimeter(*MakeIndexOrDie("# #")));
}

TEST(GetPerimeter, DegeneratePolygon) {
  EXPECT_DOUBLE_EQ(4.0, GetPerimeter(*MakeIndexOrDie(
      "4:4 # 0:0, 1:0 | 2:0, 3:0 # 0:1, 0:2, 0:3")).degrees());
}

TEST(GetArea, Empty) {
  EXPECT_EQ(0.0, GetArea(*MakeIndexOrDie("# #")));
}

TEST(GetArea, TwoFullPolygons) {
  EXPECT_EQ(8 * M_PI, GetArea(*MakeIndexOrDie("# # full | full")));
}

TEST(GetApproxArea, Empty) {
  EXPECT_EQ(0.0, GetApproxArea(*MakeIndexOrDie("# #")));
}

TEST(GetApproxArea, TwoFullPolygons) {
  EXPECT_EQ(8 * M_PI, GetApproxArea(*MakeIndexOrDie("# # full | full")));
}

TEST(GetCentroid, Empty) {
  EXPECT_EQ(S2Point(0, 0, 0), GetCentroid(*MakeIndexOrDie("# #")));
}

TEST(GetCentroid, Points) {
  EXPECT_EQ(S2Point(1, 1, 0),
            GetCentroid(*MakeIndexOrDie("0:0 | 0:90 # #")));
}

TEST(GetCentroid, Polyline) {
  // Checks that points are ignored when computing the centroid.
  EXPECT_TRUE(ApproxEquals(
      S2Point(1, 1, 0),
      GetCentroid(*MakeIndexOrDie("5:5 | 6:6 # 0:0, 0:90 #"))));
}

TEST(GetCentroid, Polygon) {
  // Checks that points and polylines are ignored when computing the centroid.
  EXPECT_TRUE(ApproxEquals(
      S2Point(M_PI_4, M_PI_4, M_PI_4),
      GetCentroid(*MakeIndexOrDie("5:5 # 6:6, 7:7 # 0:0, 0:90, 90:0"))));
}

}  // namespace s2
