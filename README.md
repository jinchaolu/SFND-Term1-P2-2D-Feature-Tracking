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

## (TODO)Project Description  
Directory Structure
```
.SFND_Lidar_Obstacle_Detection                          # Lidar Obstacle Detection Project
├── CMakeLists.txt                                      # compiler instructions
├── media                                               # media files
│   └── ObstacleDetectionFPS.gif
├── README.md                                           # Readme file
└── src
    ├── environment.cpp                                 # Render car's surrouding environment for visualization
    ├── processPointClouds.cpp                          # Process Lidar data for visualization, source file
    ├── processPointClouds.h                            # Process Lidar data for visualization, header file
    ├── quiz                                            # Quizzes
    │   ├── cluster
    │   │   ├── cluster.cpp                             # Cluster the given point clouds into groups  
    │   │   ├── CMakeLists.txt
    │   │   └── kdtree.h                                # KD tree function for sorting the given point clouds  
    │   └── ransac
    │       ├── CMakeLists.txt
    │       └── ransac2d.cpp                            # Compute random sample consensus on point clouds on a 2D plane  
    ├── render                                          # Render functions
    │   ├── box.h                                       # Draw 3D box around the point clouds  
    │   ├── render.cpp                                  # Render point clouds and other objects
    │   └── render.h                                    # Define libraries and functions for render.cpp
    └── sensors                                         # Recorded Lidar data
        ├── data
        │   └── pcd
        │       ├── data_1
        │       │   ├── 0000000000.pcd
        │       │   ├── 0000000001.pcd
        │       │   ├── 0000000002.pcd
        │       │   ├── 0000000003.pcd
        │       │   ├── 0000000004.pcd
        │       │   ├── 0000000005.pcd
        │       │   ├── 0000000006.pcd
        │       │   ├── 0000000007.pcd
        │       │   ├── 0000000008.pcd
        │       │   ├── 0000000009.pcd
        │       │   ├── 0000000010.pcd
        │       │   ├── 0000000011.pcd
        │       │   ├── 0000000012.pcd
        │       │   ├── 0000000013.pcd
        │       │   ├── 0000000014.pcd
        │       │   ├── 0000000015.pcd
        │       │   ├── 0000000016.pcd
        │       │   ├── 0000000017.pcd
        │       │   ├── 0000000018.pcd
        │       │   ├── 0000000019.pcd
        │       │   ├── 0000000020.pcd
        │       │   └── 0000000021.pcd
        │       ├── data_2
        │       │   ├── 0000000000.pcd
        │       │   ├── 0000000001.pcd
        │       │   ├── 0000000002.pcd
        │       │   ├── 0000000003.pcd
        │       │   ├── 0000000004.pcd
        │       │   ├── 0000000005.pcd
        │       │   ├── 0000000006.pcd
        │       │   ├── 0000000007.pcd
        │       │   ├── 0000000008.pcd
        │       │   ├── 0000000009.pcd
        │       │   ├── 0000000010.pcd
        │       │   ├── 0000000011.pcd
        │       │   ├── 0000000012.pcd
        │       │   ├── 0000000013.pcd
        │       │   ├── 0000000014.pcd
        │       │   ├── 0000000015.pcd
        │       │   ├── 0000000016.pcd
        │       │   ├── 0000000017.pcd
        │       │   ├── 0000000018.pcd
        │       │   ├── 0000000019.pcd
        │       │   ├── 0000000020.pcd
        │       │   ├── 0000000021.pcd
        │       │   ├── 0000000022.pcd
        │       │   ├── 0000000023.pcd
        │       │   ├── 0000000024.pcd
        │       │   ├── 0000000025.pcd
        │       │   ├── 0000000026.pcd
        │       │   ├── 0000000027.pcd
        │       │   ├── 0000000028.pcd
        │       │   ├── 0000000029.pcd
        │       │   ├── 0000000030.pcd
        │       │   ├── 0000000031.pcd
        │       │   ├── 0000000032.pcd
        │       │   ├── 0000000033.pcd
        │       │   ├── 0000000034.pcd
        │       │   ├── 0000000035.pcd
        │       │   ├── 0000000036.pcd
        │       │   ├── 0000000037.pcd
        │       │   ├── 0000000038.pcd
        │       │   ├── 0000000039.pcd
        │       │   ├── 0000000040.pcd
        │       │   ├── 0000000041.pcd
        │       │   ├── 0000000042.pcd
        │       │   ├── 0000000043.pcd
        │       │   ├── 0000000044.pcd
        │       │   ├── 0000000045.pcd
        │       │   ├── 0000000046.pcd
        │       │   ├── 0000000047.pcd
        │       │   ├── 0000000048.pcd
        │       │   ├── 0000000049.pcd
        │       │   ├── 0000000050.pcd
        │       │   ├── 0000000051.pcd
        │       │   ├── 0000000052.pcd
        │       │   ├── 0000000053.pcd
        │       │   ├── 0000000054.pcd
        │       │   ├── 0000000055.pcd
        │       │   ├── 0000000056.pcd
        │       │   ├── 0000000057.pcd
        │       │   ├── 0000000058.pcd
        │       │   ├── 0000000059.pcd
        │       │   ├── 0000000060.pcd
        │       │   ├── 0000000061.pcd
        │       │   ├── 0000000062.pcd
        │       │   ├── 0000000063.pcd
        │       │   ├── 0000000064.pcd
        │       │   ├── 0000000065.pcd
        │       │   ├── 0000000066.pcd
        │       │   ├── 0000000067.pcd
        │       │   ├── 0000000068.pcd
        │       │   ├── 0000000069.pcd
        │       │   ├── 0000000070.pcd
        │       │   ├── 0000000071.pcd
        │       │   ├── 0000000072.pcd
        │       │   ├── 0000000073.pcd
        │       │   ├── 0000000074.pcd
        │       │   ├── 0000000075.pcd
        │       │   ├── 0000000076.pcd
        │       │   ├── 0000000077.pcd
        │       │   ├── 0000000078.pcd
        │       │   ├── 0000000079.pcd
        │       │   ├── 0000000080.pcd
        │       │   ├── 0000000081.pcd
        │       │   ├── 0000000082.pcd
        │       │   ├── 0000000083.pcd
        │       │   ├── 0000000084.pcd
        │       │   ├── 0000000085.pcd
        │       │   ├── 0000000086.pcd
        │       │   ├── 0000000087.pcd
        │       │   ├── 0000000088.pcd
        │       │   ├── 0000000089.pcd
        │       │   ├── 0000000090.pcd
        │       │   ├── 0000000091.pcd
        │       │   ├── 0000000092.pcd
        │       │   ├── 0000000093.pcd
        │       │   ├── 0000000094.pcd
        │       │   ├── 0000000095.pcd
        │       │   ├── 0000000096.pcd
        │       │   ├── 0000000097.pcd
        │       │   ├── 0000000098.pcd
        │       │   ├── 0000000099.pcd
        │       │   ├── 0000000100.pcd
        │       │   ├── 0000000101.pcd
        │       │   ├── 0000000102.pcd
        │       │   ├── 0000000103.pcd
        │       │   ├── 0000000104.pcd
        │       │   ├── 0000000105.pcd
        │       │   ├── 0000000106.pcd
        │       │   ├── 0000000107.pcd
        │       │   ├── 0000000108.pcd
        │       │   ├── 0000000109.pcd
        │       │   ├── 0000000110.pcd
        │       │   ├── 0000000111.pcd
        │       │   ├── 0000000112.pcd
        │       │   ├── 0000000113.pcd
        │       │   ├── 0000000114.pcd
        │       │   ├── 0000000115.pcd
        │       │   ├── 0000000116.pcd
        │       │   ├── 0000000117.pcd
        │       │   ├── 0000000118.pcd
        │       │   ├── 0000000119.pcd
        │       │   ├── 0000000120.pcd
        │       │   ├── 0000000121.pcd
        │       │   ├── 0000000122.pcd
        │       │   ├── 0000000123.pcd
        │       │   ├── 0000000124.pcd
        │       │   ├── 0000000125.pcd
        │       │   ├── 0000000126.pcd
        │       │   ├── 0000000127.pcd
        │       │   ├── 0000000128.pcd
        │       │   ├── 0000000129.pcd
        │       │   ├── 0000000130.pcd
        │       │   ├── 0000000131.pcd
        │       │   ├── 0000000132.pcd
        │       │   ├── 0000000133.pcd
        │       │   ├── 0000000134.pcd
        │       │   ├── 0000000135.pcd
        │       │   ├── 0000000136.pcd
        │       │   ├── 0000000137.pcd
        │       │   ├── 0000000138.pcd
        │       │   ├── 0000000139.pcd
        │       │   ├── 0000000140.pcd
        │       │   ├── 0000000141.pcd
        │       │   ├── 0000000142.pcd
        │       │   ├── 0000000143.pcd
        │       │   ├── 0000000144.pcd
        │       │   ├── 0000000145.pcd
        │       │   ├── 0000000146.pcd
        │       │   ├── 0000000147.pcd
        │       │   ├── 0000000148.pcd
        │       │   ├── 0000000149.pcd
        │       │   ├── 0000000150.pcd
        │       │   ├── 0000000151.pcd
        │       │   ├── 0000000152.pcd
        │       │   └── 0000000153.pcd
        │       └── simpleHighway.pcd
        └── lidar.h                                     # Lidar sensor definition, header file
```

- [CMakeLists.txt](/src/CMakeLists.txt): File to link the C++ code to libraries.  
- [environment.cpp](/src/environment.cpp): C++ script, render car's surrouding environment for visualization  
- [processPointClouds.cpp](/src/processPointClouds.cpp): C++ script, process Lidar data for visualization  
- [processPointClouds.h](/src/processPointClouds.h): Header file, define libraries and functions for processPointClouds.cpp  
- [cluster.cpp](/src/quiz/cluster/cluster.cpp): C++ script, practice your skill on clustering the given point clouds into groups  
- [kdtree.h](/src/quiz/cluster/kdtree.h): Header file, define libraries and functions for KD tree  
- [ransac2d.cpp](/src/quiz/ransac/ransac2d.cpp): C++ script, practice your skill to compute random sample consensus on point clouds on a 2D plane  
- [box.h](/src/render/box.h): Header file, define libraries and functions for drawing 3D box in the environment  
- [render.cpp](/src/render/render.cpp): C++ script, define functions that rendering point clouds and other objects  
- [render.h](/src/render/render.h): Header file, define libraries and functions for render.cpp  
- [lidar.h](/src/sensors/lidar.h): Header file, define libraries and functions for given Lidar sensor  

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