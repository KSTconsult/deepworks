#pragma once

#include <string>
#include <gtest/gtest.h>

namespace deepworks::testutils {
inline std::string GetTestDataPath() {
    return TEST_DATA_PATH;
}

inline void AssertTensorEqual(const deepworks::Tensor& actual, const deepworks::Tensor& expected) {
    ASSERT_EQ(actual.shape()  , expected.shape());
    ASSERT_EQ(actual.strides(), expected.strides());

    auto* actual_p   = actual.data();
    auto* expected_p = expected.data();

    auto total = actual.total();
    for (int i = 0; i < total; ++i) {
        ASSERT_FLOAT_EQ(expected_p[i], actual_p[i]);
    }
}
} // deepworks::testutils