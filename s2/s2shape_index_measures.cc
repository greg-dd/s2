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

#include "s2/s2shape_index_measures.h"

#include "s2/s2shape_measures.h"

namespace s2 {

int GetDimension(const S2ShapeIndex& index) {
  int dim = -1;
  for (int i = 0; i < index.num_shape_ids(); ++i) {
    S2Shape* shape = index.shape(i);
    if (shape) dim = std::max(dim, shape->dimension());
  }
  return dim;
}

int GetNumPoints(const S2ShapeIndex& index) {
  int count = 0;
  for (int i = 0; i < index.num_shape_ids(); ++i) {
    S2Shape* shape = index.shape(i);
    if (shape && shape->dimension() == 0) {
      count += shape->num_edges();
    }
  }
  return count;
}

S1Angle GetLength(const S2ShapeIndex& index) {
  S1Angle length;
  for (int i = 0; i < index.num_shape_ids(); ++i) {
    S2Shape* shape = index.shape(i);
    if (shape) length += s2::GetLength(*shape);
  }
  return length;
}

S1Angle GetPerimeter(const S2ShapeIndex& index) {
  S1Angle perimeter;
  for (int i = 0; i < index.num_shape_ids(); ++i) {
    S2Shape* shape = index.shape(i);
    if (shape) perimeter += s2::GetPerimeter(*shape);
  }
  return perimeter;
}

double GetArea(const S2ShapeIndex& index) {
  double area = 0;
  for (int i = 0; i < index.num_shape_ids(); ++i) {
    S2Shape* shape = index.shape(i);
    if (shape) area += s2::GetArea(*shape);
  }
  return area;
}

double GetApproxArea(const S2ShapeIndex& index) {
  double area = 0;
  for (int i = 0; i < index.num_shape_ids(); ++i) {
    S2Shape* shape = index.shape(i);
    if (shape) area += s2::GetApproxArea(*shape);
  }
  return area;
}

S2Point GetCentroid(const S2ShapeIndex& index) {
  int dim = GetDimension(index);
  S2Point centroid;
  for (int i = 0; i < index.num_shape_ids(); ++i) {
    S2Shape* shape = index.shape(i);
    if (shape && shape->dimension() == dim) {
      centroid += s2::GetCentroid(*shape);
    }
  }
  return centroid;
}

}  // namespace s2
