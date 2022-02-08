#
# Copyright 2020 greg-dd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_absl",
    strip_prefix = "abseil-cpp-732b5580f089101ce4b8cdff55bb6461c59a6720",
    urls = ["https://github.com/abseil/abseil-cpp/archive/732b5580f089101ce4b8cdff55bb6461c59a6720.tar.gz"],
)

http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/archive/011959aafddcd30611003de96cfd8d7a7685c700.tar.gz"],
    strip_prefix = "googletest-011959aafddcd30611003de96cfd8d7a7685c700",
)

http_archive(
    name = "com_github_gflags_gflags",
    sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
    strip_prefix = "gflags-2.2.2/",
    urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
)

http_archive(
    name = "com_google_glog",
    sha256 = "eede71f28371bf39aa69b45de23b329d37214016e2055269b3b5e7cfd40b59f5",
    strip_prefix = "glog-0.5.0/",
    urls = ["https://github.com/google/glog/archive/v0.5.0.tar.gz"],
)

git_repository(
    name = "boringssl",
    commit = "123eaaef26abc278f53ae338e9c758eb01c70b08",
    remote = "https://boringssl.googlesource.com/boringssl",
)
