#include "perf_cpu_precomp.hpp"

#ifdef HAVE_CUDA

//////////////////////////////////////////////////////////////////////
// SetTo

GPU_PERF_TEST(SetTo, cv::gpu::DeviceInfo, cv::Size, MatType)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);

    cv::Mat src(size, type);
    cv::Scalar val(1, 2, 3, 4);

    src.setTo(val);

    TEST_CYCLE()
    {
        src.setTo(val);
    }
}

INSTANTIATE_TEST_CASE_P(MatOp, SetTo, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC3), MatType(CV_8UC4),
                    MatType(CV_16UC1), MatType(CV_16UC3), MatType(CV_16UC4),
                    MatType(CV_32FC1), MatType(CV_32FC3), MatType(CV_32FC4),
                    MatType(CV_64FC1), MatType(CV_64FC3), MatType(CV_64FC4))));

//////////////////////////////////////////////////////////////////////
// SetToMasked

GPU_PERF_TEST(SetToMasked, cv::gpu::DeviceInfo, cv::Size, MatType)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);

    cv::Mat src(size, type);
    fill(src, 0, 255);

    cv::Mat mask(size, CV_8UC1);
    fill(mask, 0, 2);

    cv::Scalar val(1, 2, 3, 4);

    src.setTo(val, mask);

    TEST_CYCLE()
    {
        src.setTo(val, mask);
    }
}

INSTANTIATE_TEST_CASE_P(MatOp, SetToMasked, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC3), MatType(CV_8UC4),
                    MatType(CV_16UC1), MatType(CV_16UC3), MatType(CV_16UC4),
                    MatType(CV_32FC1), MatType(CV_32FC3), MatType(CV_32FC4),
                    MatType(CV_64FC1), MatType(CV_64FC3), MatType(CV_64FC4))));

//////////////////////////////////////////////////////////////////////
// CopyToMasked

GPU_PERF_TEST(CopyToMasked, cv::gpu::DeviceInfo, cv::Size, MatType)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);

    cv::Mat src(size, type);
    fill(src, 0, 255);

    cv::Mat mask(size, CV_8UC1);
    fill(mask, 0, 2);

    cv::Mat dst;

    src.copyTo(dst, mask);

    TEST_CYCLE()
    {
        src.copyTo(dst, mask);
    }
}

INSTANTIATE_TEST_CASE_P(MatOp, CopyToMasked, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC3), MatType(CV_8UC4),
                    MatType(CV_16UC1), MatType(CV_16UC3), MatType(CV_16UC4),
                    MatType(CV_32FC1), MatType(CV_32FC3), MatType(CV_32FC4),
                    MatType(CV_64FC1), MatType(CV_64FC3), MatType(CV_64FC4))));

//////////////////////////////////////////////////////////////////////
// ConvertTo

GPU_PERF_TEST(ConvertTo, cv::gpu::DeviceInfo, cv::Size, MatDepth, MatDepth)
{
    cv::Size size = GET_PARAM(1);
    int depth1 = GET_PARAM(2);
    int depth2 = GET_PARAM(3);

    cv::Mat src(size, depth1);
    fill(src, 0, 255);

    cv::Mat dst;

    src.convertTo(dst, depth2, 0.5, 1.0);

    TEST_CYCLE()
    {
        src.convertTo(dst, depth2, 0.5, 1.0);
    }
}

INSTANTIATE_TEST_CASE_P(MatOp, ConvertTo, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatDepth(CV_8U), MatDepth(CV_16U), MatDepth(CV_32F), MatDepth(CV_64F)),
    testing::Values(MatDepth(CV_8U), MatDepth(CV_16U), MatDepth(CV_32F), MatDepth(CV_64F))));

#endif
