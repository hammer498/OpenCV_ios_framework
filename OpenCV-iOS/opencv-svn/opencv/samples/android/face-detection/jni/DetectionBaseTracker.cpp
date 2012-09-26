#include <DetectionBaseTracker.h>
#include <opencv2/core/core.hpp> 
#include <opencv2/contrib/detection_based_tracker.hpp>

#include <string>
#include <vector>

#include <android/log.h>

#define LOG_TAG "FaceDetection/DetectionBasedTracker"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))

using namespace std;
using namespace cv;

vector<Rect> RectFaces;

inline void vector_Rect_to_Mat(vector<Rect>& v_rect, Mat& mat)
{
    mat = Mat(v_rect, true);
}

JNIEXPORT jlong JNICALL Java_org_opencv_samples_fd_DetectionBaseTracker_nativeCreateObject
(JNIEnv * jenv, jclass jobj, jstring jFileName, jint faceSize)
{
    const char* jnamestr = jenv->GetStringUTFChars(jFileName, NULL);    
    string stdFileName(jnamestr);
    jlong result = 0;
    
    try
    {
	DetectionBasedTracker::Parameters DetectorParams;
	if (faceSize > 0)
	    DetectorParams.minObjectSize = faceSize;
	result = (jlong)new DetectionBasedTracker(stdFileName, DetectorParams);
    }
    catch(cv::Exception e)
    {
	LOGD("nativeCreateObject catched cv::Exception: %s", e.what());
	jclass je = jenv->FindClass("org/opencv/core/CvException");
	if(!je) 
	    je = jenv->FindClass("java/lang/Exception");
	jenv->ThrowNew(je, e.what());
    }
    
    return result;
}

JNIEXPORT void JNICALL Java_org_opencv_samples_fd_DetectionBaseTracker_nativeDestroyObject
(JNIEnv * jenv, jclass jobj, jlong thiz)
{
    try
    {
	((DetectionBasedTracker*)thiz)->stop();
	delete (DetectionBasedTracker*)thiz;
    }
    catch(cv::Exception e)
    {
 	LOGD("nativeestroyObject catched cv::Exception: %s", e.what());
	jclass je = jenv->FindClass("org/opencv/core/CvException");
	if(!je) 
	    je = jenv->FindClass("java/lang/Exception");
	jenv->ThrowNew(je, e.what());
    }
}

JNIEXPORT void JNICALL Java_org_opencv_samples_fd_DetectionBaseTracker_nativeStart
(JNIEnv * jenv, jclass jobj, jlong thiz)
{
    try
    {
	((DetectionBasedTracker*)thiz)->run();
    }
    catch(cv::Exception e)
    {
	LOGD("nativeStart catched cv::Exception: %s", e.what());
	jclass je = jenv->FindClass("org/opencv/core/CvException");
	if(!je) 
	    je = jenv->FindClass("java/lang/Exception");
	jenv->ThrowNew(je, e.what());
    }
    
}

JNIEXPORT void JNICALL Java_org_opencv_samples_fd_DetectionBaseTracker_nativeStop
(JNIEnv * jenv, jclass jobj, jlong thiz)
{
    try
    {
	((DetectionBasedTracker*)thiz)->stop();
    }
    catch(cv::Exception e)
    {
	LOGD("nativeStop catched cv::Exception: %s", e.what());
	jclass je = jenv->FindClass("org/opencv/core/CvException");
	if(!je) 
	    je = jenv->FindClass("java/lang/Exception");
	jenv->ThrowNew(je, e.what());
    }
}

JNIEXPORT void JNICALL Java_org_opencv_samples_fd_DetectionBaseTracker_nativeSetFaceSize
(JNIEnv * jenv, jclass jobj, jlong thiz, jint faceSize)
{
    try
    {
	if (faceSize > 0)
	{
	    DetectionBasedTracker::Parameters DetectorParams = \
		((DetectionBasedTracker*)thiz)->getParameters();
	    DetectorParams.minObjectSize = faceSize;
	    ((DetectionBasedTracker*)thiz)->setParameters(DetectorParams);
	}

    }
    catch(cv::Exception e)
    {
	LOGD("nativeStop catched cv::Exception: %s", e.what());
	jclass je = jenv->FindClass("org/opencv/core/CvException");
	if(!je) 
	    je = jenv->FindClass("java/lang/Exception");
	jenv->ThrowNew(je, e.what());
    }    
}


JNIEXPORT void JNICALL Java_org_opencv_samples_fd_DetectionBaseTracker_nativeDetect
(JNIEnv * jenv, jclass jobj, jlong thiz, jlong imageGray, jlong faces)
{
    try
    {
	((DetectionBasedTracker*)thiz)->process(*((Mat*)imageGray));
	((DetectionBasedTracker*)thiz)->getObjects(RectFaces);
	vector_Rect_to_Mat(RectFaces, *((Mat*)faces));
    }
    catch(cv::Exception e)
    {
	LOGD("nativeCreateObject catched cv::Exception: %s", e.what());
	jclass je = jenv->FindClass("org/opencv/core/CvException");
	if(!je) 
	    je = jenv->FindClass("java/lang/Exception");
	jenv->ThrowNew(je, e.what());
    }
}