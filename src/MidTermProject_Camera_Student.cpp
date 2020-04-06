/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"

/* STUDENT INCLUDES*/
#include <deque>
#include <ctime>
/* END OF STUDENT INCLUDES*/

using namespace std;

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{
    // Create csv file with date and time
    time_t t_current;
    struct tm* t_info;
    char buf[100];
    string fn_output;

    time(&t_current); // Get time now
    t_info = localtime(&t_current);

    strftime(buf, 100, "%Y_%m_%d_%H_%M_%S.csv", t_info );
    fn_output = string(buf);

    ofstream outfile(fn_output);

    // Create file header
    outfile << "Detector, Descriptor, Matcher, Selector, Number of Keypoints, Size of Neighborhood, Number of Matched Keypoints, Time (Keypoints Detection), Time (Descriptor Extraction), Time (Total)"<< endl;

    // Initialize detector array
    // Initialize descriptor array
    // Initialize matcher array
    // Initialize selector array
    vector<string> v_detector;
    vector<string> v_descriptor;
    vector<string> v_matcher;
    vector<string> v_selector;

    v_detector = {"SHITOMASI", "HARRIS", "FAST", "BRISK", "ORB", "AKAZE", "SIFT"};
    v_descriptor = {"BRISK", "BRIEF", "ORB", "FREAK", "AKAZE", "SIFT"};
    v_matcher = {"MAT_BF", "MAT_FLANN"};
    v_selector = {"SEL_NN", "SEL_KNN"};

    for (auto e_detector : v_detector) {
        for (auto e_descriptor : v_descriptor) {
            for (auto e_matcher : v_matcher) {
                for (auto e_selector : v_selector) {
                    // Write data to csv file with comma delimiter
                    // cout << detector << ", " << descriptor << ", " << matcher << ", " << selector << endl;
                    // outfile << detector << ", " << descriptor << ", " << matcher << ", " << selector << endl;
                    
                    /* INIT VARIABLES AND DATA STRUCTURES */

                    // data location
                    string dataPath = "../";

                    // camera
                    string imgBasePath = dataPath + "images/";
                    string imgPrefix = "KITTI/2011_09_26/image_00/data/000000"; // left camera, color
                    string imgFileType = ".png";
                    int imgStartIndex = 0; // first file index to load (assumes Lidar and camera names have identical naming convention)
                    int imgEndIndex = 9;   // last file index to load
                    int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)

                    // misc
                    int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time
                    // vector<DataFrame> dataBuffer; // list of data frames which are held in memory at the same time
                    deque<DataFrame> dataBuffer;
                    bool bVis = false;            // visualize results

                    /* MAIN LOOP OVER ALL IMAGES */

                    for (size_t imgIndex = 0; imgIndex <= imgEndIndex - imgStartIndex; imgIndex++)
                    {
                        /* LOAD IMAGE INTO BUFFER */

                        // assemble filenames for current index
                        ostringstream imgNumber;
                        imgNumber << setfill('0') << setw(imgFillWidth) << imgStartIndex + imgIndex;
                        string imgFullFilename = imgBasePath + imgPrefix + imgNumber.str() + imgFileType;

                        // load image from file and convert to grayscale
                        cv::Mat img, imgGray;
                        img = cv::imread(imgFullFilename);
                        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

                        //// STUDENT ASSIGNMENT
                        //// TASK MP.1 -> replace the following code with ring buffer of size dataBufferSize

                        // push image into data frame buffer
                        DataFrame frame;
                        frame.cameraImg = imgGray;
                        dataBuffer.push_back(frame);

                        // Check the size of dataBuffer
                        // If it is larger than dataBufferSize, remove the frame in the front
                        if (dataBuffer.size() > dataBufferSize) {
                            dataBuffer.pop_front();
                        }

                        // Check size again
                        assert(dataBuffer.size() <= dataBufferSize);

                        //// EOF STUDENT ASSIGNMENT
                        cout << "#1 : LOAD IMAGE INTO BUFFER done" << endl;

                        /* DETECT IMAGE KEYPOINTS */

                        // extract 2D keypoints from current image
                        vector<cv::KeyPoint> keypoints; // create empty feature list for current image
                        // string detectorType = "SHITOMASI";
                        string detectorType = e_detector;

                        //// STUDENT ASSIGNMENT
                        //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
                        //// -> HARRIS, FAST, BRISK, ORB, AKAZE, SIFT

                        //// TASK MP.9 -> Log detector running time
                        double t_detector = (double)cv::getTickCount();

                        if (detectorType.compare("SHITOMASI") == 0)
                        {
                            detKeypointsShiTomasi(keypoints, imgGray, false);
                        }
                        else if (detectorType.compare("HARRIS") == 0) {
                            detKeypointsHarris(keypoints, imgGray, false);
                        }
                        else if (detectorType.compare("FAST")  == 0 ||
                                detectorType.compare("BRISK") == 0 ||
                                detectorType.compare("ORB")   == 0 ||
                                detectorType.compare("AKAZE") == 0 ||
                                detectorType.compare("SIFT") == 0   ) {
                            detKeypointsModern(keypoints, imgGray, detectorType, false);
                        }
                        else
                        {
                            //...
                            // Throw invalid argument error
                            throw invalid_argument("Invalid detector type: " + detectorType);
                        }
                        //// EOF STUDENT ASSIGNMENT

                        //// TASK MP.9 -> Log detector running time
                        t_detector = ((double)cv::getTickCount() - t_detector) / cv::getTickFrequency();

                        //// STUDENT ASSIGNMENT
                        //// TASK MP.3 -> only keep keypoints on the preceding vehicle

                        // only keep keypoints on the preceding vehicle
                        bool bFocusOnVehicle = true;
                        cv::Rect vehicleRect(535, 180, 180, 150);
                        if (bFocusOnVehicle)
                        {
                            // ...
                            // Keep keypoints only inside the rectangle 
                            vector<cv::KeyPoint> kp_filtered;
                            for (auto kp : keypoints) {
                                if (vehicleRect.contains(kp.pt)) {
                                    kp_filtered.push_back(kp);
                                }
                            }
                            keypoints = kp_filtered;
                        }

                        //// EOF STUDENT ASSIGNMENT

                        // optional : limit number of keypoints (helpful for debugging and learning)
                        bool bLimitKpts = false;
                        if (bLimitKpts)
                        {
                            int maxKeypoints = 50;

                            if (detectorType.compare("SHITOMASI") == 0)
                            { // there is no response info, so keep the first 50 as they are sorted in descending quality order
                                keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
                            }
                            cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
                            cout << " NOTE: Keypoints have been limited!" << endl;
                        }

                        // push keypoints and descriptor for current frame to end of data buffer
                        (dataBuffer.end() - 1)->keypoints = keypoints;
                        cout << "#2 : DETECT KEYPOINTS done" << endl;

                        //// TASK MP.7 -> Count the number of keypoints and note the neighborhood size for all detectors you've implemented
                        cout << "Detector type = " << detectorType << endl;
                        cout << "Number of filtered keypoints = " << keypoints.size() << endl;
                        cout << "Neighborhood size = " << keypoints[0].size << endl;

                        /* EXTRACT KEYPOINT DESCRIPTORS */

                        //// STUDENT ASSIGNMENT
                        //// TASK MP.4 -> add the following descriptors in file matching2D.cpp and enable string-based selection based on descriptorType
                        //// -> BRIEF, ORB, FREAK, AKAZE, SIFT

                        cv::Mat descriptors;
                        // string descriptorType = "BRISK"; // BRIEF, ORB, FREAK, AKAZE, SIFT
                        string descriptorType = e_descriptor; // BRIEF, ORB, FREAK, AKAZE, SIFT
                        descKeypoints((dataBuffer.end() - 1)->keypoints, (dataBuffer.end() - 1)->cameraImg, descriptors, descriptorType);
                        //// EOF STUDENT ASSIGNMENT

                        // push descriptors for current frame to end of data buffer
                        (dataBuffer.end() - 1)->descriptors = descriptors;

                        cout << "#3 : EXTRACT DESCRIPTORS done" << endl;

                        if (dataBuffer.size() > 1) // wait until at least two images have been processed
                        {

                            /* MATCH KEYPOINT DESCRIPTORS */

                            vector<cv::DMatch> matches;
                            // string matcherType = "MAT_BF";        // MAT_BF, MAT_FLANN
                            string matcherType = e_matcher;        // MAT_BF, MAT_FLANN
                            // string descriptorCategory = "DES_BINARY"; // DES_BINARY, DES_HOG
                            // string selectorType = "SEL_NN";       // SEL_NN, SEL_KNN
                            string selectorType = e_selector;       // SEL_NN, SEL_KNN

                            // In matcher, for descriptor category, select binary or histogram of gradients
                            // Binary descriptor category includes: BRISK, BRIEF, ORB, FREAK and AKAZE
                            // Histogram of gradients descriptor category includes: SIFT
                            string descriptorCategory = "DES_BINARY"; // DES_BINARY, DES_HOG
                            if (descriptorType.compare("SIFT") == 0) {
                                descriptorCategory = "DES_HOG";
                            }
                            else {
                                descriptorCategory = "DES_BINARY";
                            }

                            //// STUDENT ASSIGNMENT
                            //// TASK MP.5 -> add FLANN matching in file matching2D.cpp
                            //// TASK MP.6 -> add KNN match selection and perform descriptor distance ratio filtering with t=0.8 in file matching2D.cpp

                            //// TASK MP.9 -> Log descriptor running time
                            double t_descriptor = (double)cv::getTickCount();

                            matchDescriptors((dataBuffer.end() - 2)->keypoints, (dataBuffer.end() - 1)->keypoints,
                                            (dataBuffer.end() - 2)->descriptors, (dataBuffer.end() - 1)->descriptors,
                                            matches, descriptorCategory, matcherType, selectorType);

                            //// EOF STUDENT ASSIGNMENT
                            //// TASK MP.9 -> Log descriptor running time
                            t_descriptor = ((double)cv::getTickCount() - t_descriptor) / cv::getTickFrequency();

                            // store matches in current data frame
                            (dataBuffer.end() - 1)->kptMatches = matches;

                            cout << "#4 : MATCH KEYPOINT DESCRIPTORS done" << endl;
                            //// TASK MP.8 -> Count the number of matched keypoints for all possible combinations of detectors and descriptors
                            // Use the BF aaproach with the descriptor distance ratio set to 0.8

                            cout << "Detector type = " << detectorType << endl;
                            cout << "Descriptor type = " << descriptorType << endl;
                            cout << "Matcher type = " << matcherType << endl;
                            cout << "Selector type = " << selectorType << endl;
                            cout << "Number of matched keypoints = " << matches.size() << endl;
                            cout << "Detector running time = " << 1000 * t_detector / 1.0 << " ms" << endl;
                            cout << "Descriptor running time = " << 1000 * t_descriptor / 1.0 << " ms" << endl;
                            cout << "Total running time = " << 1000 * (t_detector +t_descriptor) / 1.0 << " ms" << endl;

                            // Write data to csv file
                            outfile << detector << ", " << descriptor << ", " << matcher << ", " << selector << ", " << keypoints.size()  << ", " << keypoints[0].size  << ", " << matches.size()  << ", " << 1000 * t_detector / 1.0  << ", " << 1000 * t_descriptor / 1.0  << ", " <<1000 * (t_detector +t_descriptor) / 1.0 << endl;

                            // visualize matches between current and previous image
                            bVis = false;
                            if (bVis)
                            {
                                cv::Mat matchImg = ((dataBuffer.end() - 1)->cameraImg).clone();
                                cv::drawMatches((dataBuffer.end() - 2)->cameraImg, (dataBuffer.end() - 2)->keypoints,
                                                (dataBuffer.end() - 1)->cameraImg, (dataBuffer.end() - 1)->keypoints,
                                                matches, matchImg,
                                                cv::Scalar::all(-1), cv::Scalar::all(-1),
                                                vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

                                string windowName = "Matching keypoints between two camera images";
                                cv::namedWindow(windowName, 7);
                                cv::imshow(windowName, matchImg);
                                cout << "Press key to continue to next image" << endl;
                                cv::waitKey(0); // wait for key to be pressed
                            }
                            bVis = false;
                        }

                    } // eof loop over all images
                }
            }
        }
    }

    // Close csv file
    outfile.close();

    return 0;
}
