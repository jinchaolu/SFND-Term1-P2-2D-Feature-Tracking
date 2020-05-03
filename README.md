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
│   ├── 2020_04_07_03_26_37.csv                     # Raw data
│   └── report.xlsx                                 # Processed data
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
git clone https://github.com/jinchaolu/SFND-Term1-P2-2D-Feature-Tracking.git
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

## Project Rubric  
### 1. Mid-Term Report  
#### 1.1 MP.0 Mid-Term Report  
You are reading it.  
### 2. Data Buffer  
#### 2.1 MP.1 Data Buffer Optimization  
This feature is implemented here [MidTermProject_Camera_Student.cpp (Line 140-149)](./src/MidTermProject_Camera_Student.cpp#L140-L149).  
### 3. Keypoints  
#### 3.1 MP.2 Keypoint Detection  
Detector HARRIS, FAST, BRISK, ORB, AKAZE and SIFT are implemented here [matching2D_Student.cpp (Line 187-305)](./src/matching2D_Student.cpp#L187-L305).  
They are selectable by a string here [MidTermProject_Camera_Student.cpp (Line 162-190)](./src/MidTermProject_Camera_Student.cpp#L162-L190).  
#### 3.2 MP.3 Keypoint Removal  
This feature is implemented here [MidTermProject_Camera_Student.cpp (Line 199-213)](./src/MidTermProject_Camera_Student.cpp#L199-L213).  
### 4. Descriptors  
#### 4.1 MP.4 Keypoint Descriptors  
Descriptor BRIEF, ORB, FREAK, AKAZE and SIFT are implemented here [matching2D_Student.cpp (Line 98-135)](./src/matching2D_Student.cpp#L98-L135).  
They are selectable by a string here [MidTermProject_Camera_Student.cpp (Line 248-256)](./src/MidTermProject_Camera_Student.cpp#L248-L256).  
#### 4.2 MP.5 Descriptor Matching  
Matcher FLANN is implemented here [matching2D_Student.cpp (Line 23-46)](./src/matching2D_Student.cpp#L23-L46).  
Selector KNN is implemented here [matching2D_Student.cpp (Line 59-95)](./src/matching2D_Student.cpp#L59-L95).  
They are selectable by a string here [MidTermProject_Camera_Student.cpp (Line 263-296)](./src/MidTermProject_Camera_Student.cpp#L263-L296).  
#### 4.3 MP.6 Descriptor Distance Ratio  
This feature is implemented here [matching2D_Student.cpp (Line 74-87)](./src/matching2D_Student.cpp#L74-L87).  
### 5. Performance  
#### 5.1 MP.7 Performance Evaluation 1  
The number of **keypoints** on the preceding vehicle within the giving boundary for all 10 images were counted with different combinations of detectors, descriptors, matchers and selectors.  
The neighborhood size was recorded for analysis.

The full comparison result could be found here in sheet **MP.7** of ["report.xlsx"](./results/report.xlsx).  
Raw data could be found here in sheet **Raw Data** of ["report.xlsx"](./results/report.xlsx).  

A table created for performance evaluation and score is given.  
| Detector | Descriptor | Neighborhood Size | Score |
|----------|------------|-------------------|-------|
| FAST     | BRISK      | 7                 | 5     |
| FAST     | BRIEF      | 7                 | 4     |
| FAST     | ORB        | 7                 | 3     |
| FAST     | FREAK      | 7                 | 2     |
| FAST     | SIFT       | 7                 | 1     |  
#### 5.2 MP.8 Performance Evaluation 2  
The number of **matched keypoints** on the preceding vehicle within the giving boundary for all 10 images were counted with different combinations of detectors, descriptors, matchers and selectors.  

The full comparison result could be found here in sheet **MP.8** of ["report.xlsx"](./results/report.xlsx).  
Raw data could be found here in sheet **Raw Data** of ["report.xlsx"](./results/report.xlsx).  

A table created for performance evaluation and score is given.  
| Detector | Descriptor | Score |
|----------|------------|-------|
| FAST     | BRISK      | 5     |
| FAST     | BRIEF      | 4     |
| FAST     | ORB        | 3     |
| FAST     | FREAK      | 2     |
| FAST     | SIFT       | 1     |  

#### 5.3 MP.9 Performance Evaluation 3  
The time of **keypoint detection** and the time for **descriptor extraction** were logged with different combinations of detectors, descriptors, matchers and selectors.  

The full comparison result could be found here in sheet **MP.9** of ["report.xlsx"](./results/report.xlsx).  
Raw data could be found here in sheet **Raw Data** of ["report.xlsx"](./results/report.xlsx).  

A table created for performance evaluation and score is given.  
| Detector | Descriptor | Score |
|----------|------------|-------|
| FAST     | ORB        | 5     |
| FAST     | BRIEF      | 4     |
| FAST     | FREAK      | 3     |
| FAST     | BRISK      | 2     |
| FAST     | SIFT       | 1     |  

**Summary**  
The TOP3 detector / descriptor combinations are recommened here as the best choice for our purpose of detecting keypoints on vehicles.  
* **FAST + BRIEF**
* **FAST + BRISK**
* **FAST + ORB**

A table created for performance evaluation and final score is calculated by summing up all previous scores.  
| No.  | Detector | Descriptor | Score from MP.7 | Score from MP.8 | Score from MP.9 | Final Score |
|------|----------|------------|-----------------|-----------------|-----------------|-------------|
| No.1 | FAST     | BRIEF      | 4               | 4               | 4               | 12          |
| No.2 | FAST     | BRISK      | 5               | 5               | 2               | 12          |
| No.3 | FAST     | ORB        | 3               | 3               | 5               | 11          |
| No.4 | FAST     | FREAK      | 2               | 2               | 3               | 7           |
| No.5 | FAST     | SIFT       | 1               | 1               | 1               | 3           |  
