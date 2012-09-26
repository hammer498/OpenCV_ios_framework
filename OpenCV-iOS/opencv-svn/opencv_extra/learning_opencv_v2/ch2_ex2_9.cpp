/* License:
   July 20, 2011
   Standard BSD

   BOOK: It would be nice if you cited it:
   Learning OpenCV 2: Computer Vision with the OpenCV Library
     by Gary Bradski and Adrian Kaehler
     Published by O'Reilly Media
 
   AVAILABLE AT: 
     http://www.amazon.com/Learning-OpenCV-Computer-Vision-Library/dp/0596516134
     Or: http://oreilly.com/catalog/9780596516130/
     ISBN-10: 0596516134 or: ISBN-13: 978-0596516130    

   Main OpenCV site
   http://opencv.willowgarage.com/wiki/
   * An active user group is at:
     http://tech.groups.yahoo.com/group/OpenCV/
   * The minutes of weekly OpenCV development meetings are at:
     http://pr.willowgarage.com/wiki/OpenCV
*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

void help()
{
	cout << "Call: ./ch2_ex2_9, or ./ch2_ex2_9 tree.avi" << endl;
}
int main( int argc, char** argv ) { 
    namedWindow( "Example2_9", CV_WINDOW_AUTOSIZE );
    help();
    VideoCapture cap;
    if (argc==1) {
    	cap.open(0); // open the default camera
    } else {
    	cap.open(argv[1]);
    }
    if(!cap.isOpened())  // check if we succeeded
    {
    	cerr << "Couldn't open capture." << endl;
        return -1;
    }

    Mat frame;
    while(1) {
    	cap >> frame;
   		if(!frame.data) break;
        imshow( "Example2_9", frame );
        char c = waitKey(10);
        if( c == 27 ) break;
    }
}
