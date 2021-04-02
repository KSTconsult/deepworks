#include <gtest/gtest.h>

#include "kernels_reference.hpp"
#include "test_utils.hpp"
#include <deepworks/initializers.hpp>
#include <deepworks/tensor.hpp>
#include <deepworks/optimizer.hpp>
#include <deepworks/parameter.hpp>

namespace dw = deepworks;

struct SGDOptimizerTest : public ::testing::Test {

    void init(const std::vector<dw::Shape>& shapes) {
        for (auto&& sh : shapes) {
            params.emplace_back(dw::Tensor(sh));
            expected.emplace_back(dw::Tensor(sh));

            dw::initializer::uniform(params.back().data());
            dw::initializer::uniform(params.back().grad());
            params.back().data().copyTo(expected.back().data());
            params.back().grad().copyTo(expected.back().grad());
        }
    }

    dw::Parameters params;
    dw::Parameters expected;
};

TEST_F(SGDOptimizerTest, TestVariousShape) {
    init({dw::Shape{16, 32}, dw::Shape{10}, dw::Shape{2, 3, 4}, dw::Shape{10, 15, 16, 4}});
    float lr = 0.01;

    // Deepworks
    dw::optimizer::SGD sgd(params, lr);
    sgd.step();

    // Reference
    dw::reference::SGDStep(expected, lr);

    for (int i = 0; i < params.size(); ++i) {
        dw::testutils::AssertTensorEqual(expected[i].data(), params[i].data());
    }
}