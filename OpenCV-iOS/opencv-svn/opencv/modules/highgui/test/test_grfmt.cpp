/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "test_precomp.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;


class CV_GrfmtWriteBigImageTest : public cvtest::BaseTest
{
public:
    void run(int)
    {
        try
        {
            ts->printf(cvtest::TS::LOG, "start  reading big image\n");
            Mat img = imread(string(ts->get_data_path()) + "readwrite/read.png");
            ts->printf(cvtest::TS::LOG, "finish reading big image\n");
            if (img.empty()) ts->set_failed_test_info(cvtest::TS::FAIL_INVALID_TEST_DATA);
            ts->printf(cvtest::TS::LOG, "start  writing big image\n");
            imwrite(string(ts->get_data_path()) + "readwrite/write.png", img);
            ts->printf(cvtest::TS::LOG, "finish writing big image\n");
        }
        catch(...)
        {
            ts->set_failed_test_info(cvtest::TS::FAIL_EXCEPTION);
        }
        ts->set_failed_test_info(cvtest::TS::OK);
    }
};

string ext_from_int(int ext)
{
    if (ext == 0) return ".png";
    if (ext == 1) return ".bmp";
    if (ext == 2) return ".pgm";
    if (ext == 3) return ".tiff";
    return "";
}

class CV_GrfmtWriteSequenceImageTest : public cvtest::BaseTest
{
public:
    void run(int)
    {
        try
        {
            const int img_r = 640;
            const int img_c = 480;

            for (int k = 1; k <= 5; ++k)
            {
                for (int ext = 0; ext < 4; ++ext) // 0 - png, 1 - bmp, 2 - pgm, 3 - tiff
                    for (int num_channels = 1; num_channels <= 3; num_channels+=2)
                    {
                        ts->printf(ts->LOG, "image type depth:%d   channels:%d   ext: %s\n", CV_8U, num_channels, ext_from_int(ext).c_str());
                        Mat img(img_r * k, img_c * k, CV_MAKETYPE(CV_8U, num_channels), Scalar::all(0));
                        circle(img, Point2i((img_c * k) / 2, (img_r * k) / 2), cv::min((img_r * k), (img_c * k)) / 4 , Scalar::all(255));
                        ts->printf(ts->LOG, "writing      image : %s\n", string(string(ts->get_data_path()) + "readwrite/test" + ext_from_int(ext)).c_str());
                        imwrite(string(ts->get_data_path()) + "readwrite/test" + ext_from_int(ext), img);
                        ts->printf(ts->LOG, "reading test image : %s\n", string(string(ts->get_data_path()) + "readwrite/test" + ext_from_int(ext)).c_str());

                        Mat img_test = imread(string(ts->get_data_path()) + "readwrite/test" + ext_from_int(ext), CV_LOAD_IMAGE_UNCHANGED);

                        if (img_test.empty()) ts->set_failed_test_info(ts->FAIL_MISMATCH);

                        CV_Assert(img.size() == img_test.size());
                        CV_Assert(img.type() == img_test.type());

                        double n = norm(img, img_test);
                        if ( n > 1.0)
                        {
                            ts->printf(ts->LOG, "norm = %f \n", n);
                            ts->set_failed_test_info(ts->FAIL_MISMATCH);
                        }
                    }

                for (int num_channels = 1; num_channels <= 3; num_channels+=2)
                {
                    // jpeg
                    ts->printf(ts->LOG, "image type depth:%d   channels:%d   ext: %s\n", CV_8U, num_channels, ".jpg");
                    Mat img(img_r * k, img_c * k, CV_MAKETYPE(CV_8U, num_channels), Scalar::all(0));
                    circle(img, Point2i((img_c * k) / 2, (img_r * k) / 2), cv::min((img_r * k), (img_c * k)) / 4 , Scalar::all(255));
                    string filename = string(ts->get_data_path() + "readwrite/test_" + char(k + 48) + "_c" + char(num_channels + 48) + "_.jpg");
                    imwrite(filename, img);
                    img = imread(filename, CV_LOAD_IMAGE_UNCHANGED);

                    filename = string(ts->get_data_path() + "readwrite/test_" + char(k + 48) + "_c" + char(num_channels + 48) + ".jpg");
                    ts->printf(ts->LOG, "reading test image : %s\n", filename.c_str());
                    Mat img_test = imread(filename, CV_LOAD_IMAGE_UNCHANGED);

                    if (img_test.empty()) ts->set_failed_test_info(ts->FAIL_MISMATCH);

                    CV_Assert(img.size() == img_test.size());
                    CV_Assert(img.type() == img_test.type());

                    double n = norm(img, img_test);
                    if ( n > 1.0)
                    {
                        ts->printf(ts->LOG, "norm = %f \n", n);
                        ts->set_failed_test_info(ts->FAIL_MISMATCH);
                    }
                }

                for (int num_channels = 1; num_channels <= 3; num_channels+=2)
                {
                    // tiff
                    ts->printf(ts->LOG, "image type depth:%d   channels:%d   ext: %s\n", CV_16U, num_channels, ".tiff");
                    Mat img(img_r * k, img_c * k, CV_MAKETYPE(CV_16U, num_channels), Scalar::all(0));
                    circle(img, Point2i((img_c * k) / 2, (img_r * k) / 2), cv::min((img_r * k), (img_c * k)) / 4 , Scalar::all(255));
                    string filename = string(ts->get_data_path() + "readwrite/test.tiff");
                    imwrite(filename, img);
                    ts->printf(ts->LOG, "reading test image : %s\n", filename.c_str());
                    Mat img_test = imread(filename, CV_LOAD_IMAGE_UNCHANGED);

                    if (img_test.empty()) ts->set_failed_test_info(ts->FAIL_MISMATCH);

                    CV_Assert(img.size() == img_test.size());

                    ts->printf(ts->LOG, "img      : %d ; %d \n", img.channels(), img.depth());
                    ts->printf(ts->LOG, "img_test : %d ; %d \n", img_test.channels(), img_test.depth());

                    CV_Assert(img.type() == img_test.type());


                    double n = norm(img, img_test);
                    if ( n > 1.0)
                    {
                        ts->printf(ts->LOG, "norm = %f \n", n);
                        ts->set_failed_test_info(ts->FAIL_MISMATCH);
                    }
                }
            }
        }
        catch(const cv::Exception & e)
        {
            ts->printf(ts->LOG, "Exception: %s\n" , e.what());
            ts->set_failed_test_info(ts->FAIL_MISMATCH);
        }
    }
};

class CV_GrfmtReadBMPRLE8Test : public cvtest::BaseTest
{
public:
    void run(int)
    {
        try
        {
            Mat rle = imread(string(ts->get_data_path()) + "readwrite/rle8.bmp");
            Mat bmp = imread(string(ts->get_data_path()) + "readwrite/ordinary.bmp");
            if (norm(rle-bmp)>1.e-10)
                ts->set_failed_test_info(cvtest::TS::FAIL_BAD_ACCURACY);
        }
        catch(...)
        {
            ts->set_failed_test_info(cvtest::TS::FAIL_EXCEPTION);
        }
        ts->set_failed_test_info(cvtest::TS::OK);
    }
};

#ifdef HAVE_PNG
TEST(Highgui_Image, write_big) { CV_GrfmtWriteBigImageTest      test; test.safe_run(); }
#endif

#if defined(HAVE_PNG) && defined(HAVE_TIFF) && defined(HAVE_JPEG)
TEST(Highgui_Image, write_imageseq) { CV_GrfmtWriteSequenceImageTest test; test.safe_run(); }
#endif

TEST(Highgui_Image, read_bmp_rle8) { CV_GrfmtReadBMPRLE8Test test; test.safe_run(); }

