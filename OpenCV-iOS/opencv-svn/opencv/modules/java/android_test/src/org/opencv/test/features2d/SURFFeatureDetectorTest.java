package org.opencv.test.features2d;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.MatOfKeyPoint;
import org.opencv.core.Point;
import org.opencv.core.Scalar;
import org.opencv.features2d.FeatureDetector;
import org.opencv.features2d.KeyPoint;
import org.opencv.test.OpenCVTestCase;
import org.opencv.test.OpenCVTestRunner;

public class SURFFeatureDetectorTest extends OpenCVTestCase {

    FeatureDetector detector;
    int matSize;
    KeyPoint[] truth;

    private Mat getMaskImg() {
        Mat mask = new Mat(matSize, matSize, CvType.CV_8U, new Scalar(255));
        Mat right = mask.submat(0, matSize, matSize / 2, matSize);
        right.setTo(new Scalar(0));
        return mask;
    }

    private Mat getTestImg() {
        Mat cross = new Mat(matSize, matSize, CvType.CV_8U, new Scalar(255));
        Core.line(cross, new Point(20, matSize / 2), new Point(matSize - 21, matSize / 2), new Scalar(100), 2);
        Core.line(cross, new Point(matSize / 2, 20), new Point(matSize / 2, matSize - 21), new Scalar(100), 2);

        return cross;
    }

    private void order(List<KeyPoint> points) {
        Collections.sort(points, new Comparator<KeyPoint>() {
            public int compare(KeyPoint p1, KeyPoint p2) {
                if (p1.angle < p2.angle)
                    return -1;
                if (p1.angle > p2.angle)
                    return 1;
                return 0;
            }
        });
    }

    @Override
    protected void setUp() throws Exception {
        detector = FeatureDetector.create(FeatureDetector.SURF);

        matSize = 100;

        truth = new KeyPoint[] {
        		/*
        		new KeyPoint(55.775577545166016f, 44.224422454833984f, 16, 9.754629f, 8617.863f, 1, -1),
                new KeyPoint(44.224422454833984f, 44.224422454833984f, 16, 99.75463f, 8617.863f, 1, -1),
                new KeyPoint(44.224422454833984f, 55.775577545166016f, 16, 189.7546f, 8617.863f, 1, -1),
                new KeyPoint(55.775577545166016f, 55.775577545166016f, 16, 279.75464f, 8617.863f, 1, -1)
                */
        		new KeyPoint(55.7755f, 44.2244f, 16,   9.754f, 8617.863f, 0, -1), 
        		new KeyPoint(44.2244f, 44.2244f, 16,  99.754f, 8617.863f, 0, -1), 
        		new KeyPoint(44.2244f, 55.7755f, 16, 189.754f, 8617.863f, 0, -1), 
        		new KeyPoint(55.7755f, 55.7755f, 16, 279.754f, 8617.863f, 0, -1)
        	};

        super.setUp();
    }

    public void testCreate() {
        assertNotNull(detector);
    }

    public void testDetectListOfMatListOfListOfKeyPoint() {
        String filename = OpenCVTestRunner.getTempFileName("yml");
        writeFile(filename, "%YAML:1.0\nhessianThreshold: 8000.\noctaves: 3\noctaveLayers: 4\nupright: 0\n");
        detector.read(filename);

        List<MatOfKeyPoint> keypoints = new ArrayList<MatOfKeyPoint>();
        Mat cross = getTestImg();
        List<Mat> crosses = new ArrayList<Mat>(3);
        crosses.add(cross);
        crosses.add(cross);
        crosses.add(cross);

        detector.detect(crosses, keypoints);

        assertEquals(3, keypoints.size());

        for (MatOfKeyPoint mkp : keypoints) {
        	List<KeyPoint> lkp = mkp.toList();
            order(lkp);
            assertListKeyPointEquals(Arrays.asList(truth), lkp, EPS);
        }
    }

    public void testDetectListOfMatListOfListOfKeyPointListOfMat() {
        fail("Not yet implemented");
    }

    public void testDetectMatListOfKeyPoint() {
        String filename = OpenCVTestRunner.getTempFileName("yml");
        writeFile(filename, "%YAML:1.0\nhessianThreshold: 8000.\noctaves: 3\noctaveLayers: 4\nupright: 0\n");
        detector.read(filename);

        MatOfKeyPoint keypoints = new MatOfKeyPoint();
        Mat cross = getTestImg();

        detector.detect(cross, keypoints);

        List<KeyPoint> lkp = keypoints.toList();
        order(lkp);
        assertListKeyPointEquals(Arrays.asList(truth), lkp, EPS);
    }

    public void testDetectMatListOfKeyPointMat() {
        String filename = OpenCVTestRunner.getTempFileName("yml");
        writeFile(filename, "%YAML:1.0\nhessianThreshold: 8000.\noctaves: 3\noctaveLayers: 4\nupright: 0\n");
        detector.read(filename);

        Mat img = getTestImg();
        Mat mask = getMaskImg();
        MatOfKeyPoint keypoints = new MatOfKeyPoint();

        detector.detect(img, keypoints, mask);

        List<KeyPoint> lkp = keypoints.toList();
        order(lkp);
        assertListKeyPointEquals(Arrays.asList(truth[1], truth[2]), lkp, EPS);
    }

    public void testEmpty() {
        assertFalse(detector.empty());
    }

    public void testRead() {
        Mat cross = getTestImg();

        MatOfKeyPoint keypoints1 = new MatOfKeyPoint();
        detector.detect(cross, keypoints1);

        String filename = OpenCVTestRunner.getTempFileName("yml");
        writeFile(filename, "%YAML:1.0\nhessianThreshold: 8000.\noctaves: 3\noctaveLayers: 4\nupright: 0\n");
        detector.read(filename);

        MatOfKeyPoint keypoints2 = new MatOfKeyPoint();
        detector.detect(cross, keypoints2);

        assertTrue(keypoints2.total() <= keypoints1.total());
    }

    public void testWrite() {
        String filename = OpenCVTestRunner.getTempFileName("xml");

        detector.write(filename);

        String truth = "<?xml version=\"1.0\"?>\n<opencv_storage>\n<name>Feature2D.SURF</name>\n<extended>1</extended>\n<hessianThreshold>100.</hessianThreshold>\n<nOctaveLayers>2</nOctaveLayers>\n<nOctaves>4</nOctaves>\n<upright>0</upright>\n</opencv_storage>\n";
        assertEquals(truth, readFile(filename));
    }

    public void testWriteYml() {
        String filename = OpenCVTestRunner.getTempFileName("yml");

        detector.write(filename);

        String truth = "%YAML:1.0\nname: \"Feature2D.SURF\"\nextended: 1\nhessianThreshold: 100.\nnOctaveLayers: 2\nnOctaves: 4\nupright: 0\n";
        assertEquals(truth, readFile(filename));
    }

}
