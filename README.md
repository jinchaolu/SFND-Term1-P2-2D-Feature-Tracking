# SFND-Term1-P2-2D-Feature-Tracking
Project 2 of Udacity Sensor Fusion Nanodegree  
<img src="images/keypoints.png" width="820" height="248" />

## (TODO)Overview  
In this project, you will create a C++ script to render the simulation environment with given Lidar dataset which you should recoginze and detect the objects, clustering and drawing 3D bounding boxes on those objects across frames in the video consistently.  

You will learn what is and how to use PCL (Point Cloud Library) then create and represent a Lidar sensor in a simulator.  

Then, you will learn how to use RANSAC (stands for Random Sample Consensus, is a method for detecting outliers in data) algorithm for robust line fitting with outliers.  

Next, you will learn how to clustering obstacles with euclidean clustering function from PCL, inserting points into KD-Tree and drawing a 3D box on those obstacles.  

Finally, you will implement all you have learned above in the C++ script and analyze given Lidar data to recognize and detect the obstacles from frame to frame in a given video stream consistently.  


(Below from original repository)  
The idea of the camera course is to build a collision detection system - that's the overall goal for the Final Project. As a preparation for this, you will now build the feature tracking part and test various detector / descriptor combinations to see which ones perform best. This mid-term project consists of four parts:

* First, you will focus on loading images, setting up data structures and putting everything into a ring buffer to optimize memory load. 
* Then, you will integrate several keypoint detectors such as HARRIS, FAST, BRISK and SIFT and compare them with regard to number of keypoints and speed. 
* In the next part, you will then focus on descriptor extraction and matching using brute force and also the FLANN approach we discussed in the previous lesson. 
* In the last part, once the code framework is complete, you will test the various algorithms in different combinations and compare them with regard to some performance measures. 

See the classroom instruction and code comments for more details on each of these parts. Once you are finished with this project, the keypoint matching part will be set up and you can proceed to the next lesson, where the focus is on integrating Lidar points and on object detection using deep-learning. 

## Prerequisites/Dependencies  
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * This must be compiled from source using the `-D OPENCV_ENABLE_NONFREE=ON` cmake flag for testing the SIFT and SURF detectors.
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Project Description  
Directory Structure
```
.SFND-Term1-P2-2D-Feature-Tracking                  # 2D Feature Tracking Project
├── CMakeLists.txt                                  # compiler instructions
├── images                                          # Image files
│   ├── keypoints.png
│   └── KITTI                                       # KITTI database
│       └── 2011_09_26
│           └── image_00
│               └── data
│                   ├── 0000000000.png
│                   ├── 0000000001.png
│                   ├── 0000000002.png
│                   ├── 0000000003.png
│                   ├── 0000000004.png
│                   ├── 0000000005.png
│                   ├── 0000000006.png
│                   ├── 0000000007.png
│                   ├── 0000000008.png
│                   └── 0000000009.png
├── LICENSE
├── README.md                                       # Readme file
├── results                                         # Result data for analysis
│   └── 2020_04_07_03_26_37.csv
└── src
    ├── dataStructures.h                            # Data structure header file
    ├── matching2D.hpp                              # matching2D header file
    ├── matching2D_Student.cpp                      # Create detector and descriptor, and compute matched keypoints
    └── MidTermProject_Camera_Student.cpp           # Main function to load and analyze images
```

- [CMakeLists.txt](/src/CMakeLists.txt): File to link the C++ code to libraries.  
- [MidTermProject_Camera_Student.cpp](/src/MidTermProject_Camera_Student.cpp): C++ script, main function to load and analyze images  
- [matching2D_Student.cpp](/src/matching2D_Student.cpp): C++ script, helper function, create detector and descriptor, and compute the matched keypoint with given threshold and ratio  
- [matching2D.h](/src/matching2D.hpp): Header file, define libraries and functions for matching2D_Student.cpp  
- [dataStructures.h](/src/quiz/cluster/kdtree.h): Header file, define libraries and functions for data structure  

## Run the project  

* Clone this repository  
```
git clone https://github.com/udacity/SFND_2D_Feature_Tracking.git
```
* Navigate to the `SFND-Term1-P2-2D-Feature-Tracking` folder  
```
cd SFND-Term1-P2-2D-Feature-Tracking
```
* Create and open `build` folder  
```
mkdir build && cd build
```
* Compile your code  
```
cmake .. && make
```
* Run `2D_feature_tracking` application  
```
./2D_feature_tracking
```

## Tips  
1. It's recommended to update and upgrade your environment before running the code.  
```
sudo apt-get update && sudo apt-get upgrade -y
```

## Code Style  
Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).  

## (TODO)Project Rubric  
### 1. Mid-Term Report  
#### 1.1 MP.0 Mid-Term Report  
Yes, it does compile.  
### 2. Data Buffer  
#### 2.1 MP.1 Data Buffer Optimization  
Yes, it does.  
### 3. Keypoints  
#### 3.1 MP.2 Keypoint Detection  
Yes, it does.  
#### 3.2 MP.3 Keypoint Removal  
Yes, it does.  
### 4. Descriptors  
#### 4.1 MP.4 Keypoint Descriptors  
Yes, it does.  
#### 4.2 MP.5 Descriptor Matching  
Yes, it does.  
#### 4.3 MP.6 Descriptor Distance Ratio  
Yes, it does.  
### 5. Performance  
#### 5.1 MP.7 Performance Evaluation 1  
Yes, it does.  
#### 5.2 MP.8 Performance Evaluation 2  
Yes, it does.  
#### 5.3 MP.9 Performance Evaluation 3  
Yes, it does.  
