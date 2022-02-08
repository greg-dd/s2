# Cloned from https://github.com/google/s2geometry/tree/v0.9.0
#
# The following modifications were made so as to compile with Bazel and
# integrate into our existing codebase:
# i) changing all header includes from "s2/..." to "third_party/s2/...";
#
# ii) using our own third_party abseil library rather than `third_party/absl/`,
#     which was accordingly deleted.
#
# iii) switching all mentions of "string" to "std::string";
#
# iv) getting rid of each and every s2 strings namespace;
#
# v) introducing a testing bazel macro instantiating an `cc_test` rule for S2 tests
#    under s2test.bzl;
#
# vi) deleting `third_party/cmake`;
#
# vii) making use of our own third_party openssl library;
#
# viii) replacing all instances of "namespace S2" with "namespace s2", given that we
#       added the s2 namespace around all previously non-namespaced code.
#
# ix) moving Mutex and CondVar from base/mutex.h out of the absl namespace and into
#     the s2 namespace, changing at all sites that define a Mutex or CondVar.
#
# x) commenting out all non-essential macros and global variables in base/port.h

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

DEFAULT_COPTS = [
    "-DS2_USE_GFLAGS",
    "-DS2_USE_GLOG",
    "-DS2_USE_EXACTFLOAT",
    "-DHASH_NAMESPACE=std",
    "-Wno-deprecated-declarations",
    "-Wno-format",
    "-Wno-non-virtual-dtor",
    "-Wno-parentheses",
    "-Wno-sign-compare",
    "-Wno-strict-aliasing",
    "-Wno-unused-function",
    "-Wno-unused-private-field",
    "-Wno-unused-variable",
    "-Wno-unused-function",
]

cc_library(
    name = "s2",
    srcs = glob(
        ["**/*.cc"],
        exclude = [
            "*_test.cc",
            "*_testing.cc",
            "doc/**",
        ],
    ),
    hdrs = glob(
        ["**/*.h"],
        exclude = ["*_testing.h"],
    ),
    copts = DEFAULT_COPTS,
    linkstatic = False,
    deps = [
        "@boringssl//:crypto",
        "@com_github_gflags_gflags//:gflags",
        "@com_google_absl//absl/algorithm",
        "@com_google_absl//absl/base",
        "@com_google_absl//absl/container:container_memory",
        "@com_google_absl//absl/container:fixed_array",
        "@com_google_absl//absl/container:inlined_vector",
        "@com_google_absl//absl/container:layout",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/meta:type_traits",
        "@com_google_absl//absl/numeric:int128",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:span",
        "@com_google_absl//absl/utility",
        "@com_google_glog//:glog",
    ],
)

# Common deps for tests.
cc_library(
    name = "s2testing",
    srcs = glob(["*testing.*"]),
    copts = DEFAULT_COPTS,
    deps = [
        ":s2",
        "@com_google_googletest//:gtest_main",
    ],
)

# For running all tests.
test_suite(
    name = "smoke_tests",
)

# Load testing macro.
load(":s2test.bzl", "s2test")

s2test(name = "encoded_s2cell_id_vector_test")

s2test(name = "encoded_s2point_vector_test")

s2test(name = "encoded_s2shape_index_test")

s2test(name = "encoded_string_vector_test")

s2test(name = "encoded_uint_vector_test")

s2test(name = "id_set_lexicon_test")

s2test(name = "mutable_s2shape_index_test")

s2test(name = "r1interval_test")

s2test(name = "r2rect_test")

s2test(name = "s1angle_test")

s2test(name = "s1chord_angle_test")

s2test(name = "s1interval_test")

s2test(name = "s2boolean_operation_test")

s2test(name = "s2builder_graph_test")

s2test(name = "s2builder_test")

s2test(name = "s2builderutil_closed_set_normalizer_test")

s2test(name = "s2builderutil_find_polygon_degeneracies_test")

s2test(name = "s2builderutil_lax_polygon_layer_test")

s2test(name = "s2builderutil_s2point_vector_layer_test")

s2test(name = "s2builderutil_s2polygon_layer_test")

s2test(name = "s2builderutil_s2polyline_layer_test")

s2test(name = "s2builderutil_s2polyline_vector_layer_test")

s2test(
    name = "s2builderutil_snap_functions_test",
    size = "medium",
)

s2test(name = "s2builderutil_testing_test")

s2test(name = "s2cap_test")

s2test(name = "s2cell_id_test")

s2test(name = "s2cell_index_test")

s2test(name = "s2cell_test")

s2test(name = "s2cell_union_test")

s2test(name = "s2centroids_test")

s2test(name = "s2closest_cell_query_base_test")

s2test(name = "s2closest_cell_query_test")

s2test(name = "s2closest_edge_query_base_test")

s2test(name = "s2closest_edge_query_test")

s2test(name = "s2closest_point_query_base_test")

s2test(name = "s2closest_point_query_test")

s2test(name = "s2contains_point_query_test")

s2test(name = "s2contains_vertex_query_test")

s2test(name = "s2convex_hull_query_test")

s2test(name = "s2coords_test")

s2test(name = "s2crossing_edge_query_test")

s2test(name = "s2earth_test")

s2test(name = "s2edge_clipping_test")

s2test(name = "s2edge_crosser_test")

s2test(name = "s2edge_crossings_test")

s2test(name = "s2edge_distances_test")

s2test(
    name = "s2edge_tessellator_test",
    size = "medium",
)

s2test(name = "s2edge_vector_shape_test")

s2test(name = "s2error_test")

s2test(name = "s2furthest_edge_query_test")

s2test(name = "s2latlng_rect_bounder_test")

s2test(name = "s2latlng_rect_test")

s2test(name = "s2latlng_test")

s2test(name = "s2lax_loop_shape_test")

s2test(name = "s2lax_polygon_shape_test")

s2test(name = "s2lax_polyline_shape_test")

s2test(name = "s2loop_measures_test")

s2test(name = "s2loop_test")

s2test(name = "s2max_distance_targets_test")

s2test(name = "s2measures_test")

s2test(name = "s2min_distance_targets_test")

s2test(name = "s2padded_cell_test")

s2test(name = "s2point_compression_test")

s2test(name = "s2point_index_test")

s2test(name = "s2point_region_test")

s2test(name = "s2point_test")

s2test(name = "s2pointutil_test")

s2test(name = "s2point_vector_shape_test")

s2test(
    name = "s2polygon_test",
    size = "medium",
)

s2test(name = "s2polyline_alignment_test")

s2test(name = "s2polyline_measures_test")

s2test(name = "s2polyline_simplifier_test")

s2test(name = "s2polyline_test")

s2test(name = "s2predicates_test")

s2test(name = "s2projections_test")

s2test(name = "s2r2rect_test")

s2test(name = "s2region_coverer_test")

s2test(name = "s2region_term_indexer_test")

s2test(name = "s2region_test")

s2test(name = "s2region_union_test")

s2test(name = "s2shape_index_buffered_region_test")

s2test(name = "s2shape_index_measures_test")

s2test(name = "s2shape_index_region_test")

s2test(name = "s2shape_index_test")

s2test(name = "s2shape_measures_test")

s2test(name = "s2shapeutil_build_polygon_boundaries_test")

s2test(name = "s2shapeutil_coding_test")

s2test(name = "s2shapeutil_contains_brute_force_test")

s2test(name = "s2shapeutil_count_edges_test")

s2test(name = "s2shapeutil_edge_iterator_test")

s2test(name = "s2shapeutil_get_reference_point_test")

s2test(name = "s2shapeutil_range_iterator_test")

s2test(name = "s2shapeutil_visit_crossing_edge_pairs_test")

s2test(name = "s2testing_test")

s2test(name = "s2text_format_test")

s2test(name = "s2wedge_relations_test")

s2test(name = "sequence_lexicon_test")

s2test(name = "value_lexicon_test")
