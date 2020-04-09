# SFND-Term1-P2-2D-Feature-Tracking
Project 2 of Udacity Sensor Fusion Nanodegree  
<img src="images/keypoints.png" width="820" height="248" />

## Overview  
In this project, you will create a C++ script to recognize and track the feature from a series of images. You are going to evaluate the performance of feature tracking with various combinations of detectors, descriptors, matchers. Then pick the best combination for your future objection detection and tracking use purpose. This 2D feature tracking technique will be used in a collision detection system in later course. This project consists of four parts:

* First, you will focus on loading images, setting up data structures and putting everything into a ring buffer to optimize memory load. 
* Then, you will integrate several keypoint detectors such as HARRIS, FAST, BRISK and SIFT and compare them with regard to number of keypoints and speed. 
* In the next part, you will then focus on descriptor extraction and matching using brute force and also the FLANN approach we discussed in the previous lesson. 
* In the last part, once the code framework is complete, you will test the various algorithms in different combinations and compare them with regard to some performance measures. 

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
You are reading it.  
### 2. Data Buffer  
#### 2.1 MP.1 Data Buffer Optimization  
This feature is implemented here [MidTermProject_Camera_Student.cpp (Line 140-149)](./src/MidTermProject_Camera_Student.cpp#L140-149).  
### 3. Keypoints  
#### 3.1 MP.2 Keypoint Detection  
Detector HARRIS, FAST, BRISK, ORB, AKAZE and SIFT are implemented here [matching2D_Student.cpp (Line 187-305)](./src/matching2D_Student.cpp#L187-305).  
They are selectable by a string here [MidTermProject_Camera_Student.cpp (Line 162-190)](./src/MidTermProject_Camera_Student.cpp#L162-190).  
#### 3.2 MP.3 Keypoint Removal  
This feature is implemented here [MidTermProject_Camera_Student.cpp (Line 199-213)](./src/MidTermProject_Camera_Student.cpp#L199-213).  
### 4. Descriptors  
#### 4.1 MP.4 Keypoint Descriptors  
Descriptor BRIEF, ORB, FREAK, AKAZE and SIFT are implemented here [matching2D_Student.cpp (Line 98-135)](./src/matching2D_Student.cpp#L98-135).  
They are selectable by a string here [MidTermProject_Camera_Student.cpp (Line 248-256)](./src/MidTermProject_Camera_Student.cpp#L248-256).  
#### 4.2 MP.5 Descriptor Matching  
Matcher FLANN is implemented here [matching2D_Student.cpp (Line 23-46)](./src/matching2D_Student.cpp#L23-46).  
Selector KNN is implemented here [matching2D_Student.cpp (Line 59-95)](./src/matching2D_Student.cpp#L59-95).  
They are selectable by a string here [MidTermProject_Camera_Student.cpp (Line 263-296)](./src/MidTermProject_Camera_Student.cpp#L263-296).  
#### 4.3 MP.6 Descriptor Distance Ratio  
This feature is implemented here [matching2D_Student.cpp (Line 74-87)](./src/matching2D_Student.cpp#L74-87).  
### 5. Performance  
#### 5.1 (TODO) MP.7 Performance Evaluation 1  
(Process the data and generate a table for comparison and visualization)  
#### 5.2 (TODO) MP.8 Performance Evaluation 2  
(Process the data and generate a table for comparison and visualization)  
#### 5.3 (TODO) MP.9 Performance Evaluation 3  
(Process the data and generate a table for comparison and visualization)  
