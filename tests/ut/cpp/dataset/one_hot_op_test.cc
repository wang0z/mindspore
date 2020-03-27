/**
 * Copyright 2019 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "common/common.h"
#include "common/cvop_common.h"
#include "dataset/kernels/data/one_hot_op.h"
#include "dataset/core/cv_tensor.h"
#include "utils/log_adapter.h"

using namespace mindspore::dataset;
using mindspore::MsLogLevel::INFO;
using mindspore::ExceptionType::NoExceptionType;
using mindspore::LogStream;

class MindDataTestOneHotOp : public UT::CVOP::CVOpCommon {
 protected:
    MindDataTestOneHotOp() : CVOpCommon() {}
};

TEST_F(MindDataTestOneHotOp, TestOp) {
  MS_LOG(INFO) << "Doing MindDataTestOneHotOp.";
  uint64_t labels[3] = {0, 1, 2};
  TensorShape shape({3});
  std::shared_ptr<Tensor> input = std::make_shared<Tensor>(shape, DataType(DataType::DE_UINT64),
                                                           reinterpret_cast <unsigned char *>(labels));
  std::shared_ptr<Tensor> output;

  std::unique_ptr<OneHotOp> op(new OneHotOp(5));
  Status s = op->Compute(input, &output);
  uint64_t out[15] = {1, 0, 0, 0, 0,
                      0, 1, 0, 0, 0,
                      0, 0, 1, 0, 0};
  std::shared_ptr<Tensor> expected = std::make_shared<Tensor>(TensorShape{3, 5}, DataType(DataType::DE_UINT64),
                                                              reinterpret_cast <unsigned char *>(out));
  EXPECT_TRUE(s.IsOk());
  ASSERT_TRUE(output->shape() == expected->shape());
  ASSERT_TRUE(output->type() == expected->type());
  std::cout << *output << std::endl;
  std::cout << *expected << std::endl;

  ASSERT_TRUE(*output == *expected);
  MS_LOG(INFO) << "MindDataTestOneHotOp end.";
}