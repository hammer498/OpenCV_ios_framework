/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
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
//   * The name of Intel Corporation may not be used to endorse or promote products
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

#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

CV_SLMLTest::CV_SLMLTest( const char* _modelName ) : CV_MLBaseTest( _modelName )
{
    validationFN = "slvalidation.xml";
}

int CV_SLMLTest::run_test_case( int testCaseIdx )
{
    int code = cvtest::TS::OK;
    code = prepare_test_case( testCaseIdx );

    if( code == cvtest::TS::OK )
    {
            data.mix_train_and_test_idx();
            code = train( testCaseIdx );
            if( code == cvtest::TS::OK )
            {
                get_error( testCaseIdx, CV_TEST_ERROR, &test_resps1 );
                fname1 = tempfile();
                save( fname1.c_str() );
                load( fname1.c_str() );
                get_error( testCaseIdx, CV_TEST_ERROR, &test_resps2 );
                fname2 = tempfile();
                save( fname2.c_str() );
            }
            else
                ts->printf( cvtest::TS::LOG, "model can not be trained" );
    }
    return code;
}

int CV_SLMLTest::validate_test_results( int testCaseIdx )
{
    int code = cvtest::TS::OK;

    // 1. compare files
    ifstream f1( fname1.c_str() ), f2( fname2.c_str() );
    string s1, s2;
    int lineIdx = 0; 
    CV_Assert( f1.is_open() && f2.is_open() );
    for( ; !f1.eof() && !f2.eof(); lineIdx++ )
    {
        getline( f1, s1 );
        getline( f2, s2 );
        if( s1.compare(s2) )
        {
            ts->printf( cvtest::TS::LOG, "first and second saved files differ in %n-line; first %n line: %s; second %n-line: %s",
               lineIdx, lineIdx, s1.c_str(), lineIdx, s2.c_str() );
            code = cvtest::TS::FAIL_INVALID_OUTPUT;
        }
    }
    if( !f1.eof() || !f2.eof() )
    {
        ts->printf( cvtest::TS::LOG, "in test case %d first and second saved files differ in %n-line; first %n line: %s; second %n-line: %s",
            testCaseIdx, lineIdx, lineIdx, s1.c_str(), lineIdx, s2.c_str() );
        code = cvtest::TS::FAIL_INVALID_OUTPUT;
    }
    f1.close();
    f2.close();
    // delete temporary files
    remove( fname1.c_str() );
    remove( fname2.c_str() );

    // 2. compare responses
    CV_Assert( test_resps1.size() == test_resps2.size() );
    vector<float>::const_iterator it1 = test_resps1.begin(), it2 = test_resps2.begin();
    for( ; it1 != test_resps1.end(); ++it1, ++it2 )
    {
        if( fabs(*it1 - *it2) > FLT_EPSILON )
        {
            ts->printf( cvtest::TS::LOG, "in test case %d responses predicted before saving and after loading is different", testCaseIdx );
            code = cvtest::TS::FAIL_INVALID_OUTPUT;
        }
    }
    return code;
}

TEST(ML_NaiveBayes, save_load) { CV_SLMLTest test( CV_NBAYES ); test.safe_run(); }
//CV_SLMLTest lsmlknearest( CV_KNEAREST, "slknearest" ); // does not support save!
TEST(ML_SVM, save_load) { CV_SLMLTest test( CV_SVM ); test.safe_run(); }
//CV_SLMLTest lsmlem( CV_EM, "slem" ); // does not support save!
TEST(ML_ANN, save_load) { CV_SLMLTest test( CV_ANN ); test.safe_run(); }
TEST(ML_DTree, save_load) { CV_SLMLTest test( CV_DTREE ); test.safe_run(); }
TEST(ML_Boost, save_load) { CV_SLMLTest test( CV_BOOST ); test.safe_run(); }
TEST(ML_RTrees, save_load) { CV_SLMLTest test( CV_RTREES ); test.safe_run(); }
TEST(ML_ERTrees, save_load) { CV_SLMLTest test( CV_ERTREES ); test.safe_run(); }

/* End of file. */
