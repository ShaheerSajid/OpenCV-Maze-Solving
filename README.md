# OpenCV-Maze-Solving

## Abstract 

In this project a maze layout is placed under a camera. After taking the picture, the image is processed using OpenCV to extract the features of the maze which includes starting/ending points and open/closed paths. Then two separate algorithms: recursion and A* algorithm are applied and the efficiency of each algorithm is compared.

## Introduction

#### Problem Statement

**_“How might we implement and compare recursion with A* algorithm in solving a given maze layout? Moreover, how might we determine the credibility of both programs?”_**

#### Controls

Maze with single starting and ending point

Multiple paths to end point

Maze layout developed on a grid of 10 by 13 cells.

Similar layout for both algorithms

#### Scope of problem

The problem of solving a maze usually occurs in robot navigation where the starting and ending paths have hurdles in between. Moreover, if there are multiple paths present to the end point then finding the shortest path is essential considering cost and time. Other than robot navigation this problem is also identified in terrain where some paths are available while others are not.

## Implementation

The complete program was written in C++.

#### Toolchain
 - Visual Studio 2017
 - OpenCV libraries for visual studio
 

#### Our solution consists of 4 main steps
 - Taking a picture of maze
 - Extracting features (Start/End point, Open/Closed path)
 - Applying recursion
 - Applying A*

## Data structures used

**Singly Linked List:** This was used to store coordinates. As we required constant addition and removal of points, a linked list was used.

**Binary Search Tree:** This was used to store points for the A* algorithm while it traversed through the graph. We needed to extract the minimum cost value at every step for comparison hence, this was used. A minimum heap would have been a better solution to this. Since the balancing proved to be a problem, we dropped the implementation of a heap. The reason we used a tree was that we can locate the parent of each node easily.

**Stack:** It was used to store final points for A* algorithm. We used it because of the convenient functions of push and pop to add and delete and entry.

**A table of cells** was used to store the closed set of points in A* algorithm.

**Pair:** Used to pair up the two coordinates x and y into a single variable


## Summary of Operation

The picture was taken using a USB camera and then loaded into a type matrix variable for processing. The image was then converted to HSV colour space and the thresh-holds were set using slider bars for Hue, Saturation and Value. The resulting image was a binary image showing the blocked with white and open with black. This image was then read block by block and converted into a 10 by 13 matrix of 1’s and 0’s. 0 for blocked path and 1 for open path.

Ready for application of path finding algorithms the program asks user for the algorithm to be deployed. If recursion then the program first adds the starting point into a linked list. One for each x and y coordinate. The program then looks for open cells in all four directions of the point. The preference was set to North, East, West and South. If it finds an open cell, it adds that to the linked lists and flags that point. The program keeps adding open paths till it finds a dead end or it reaches the destination. If its a dead end then it back traverses while removing those points from the lists. It does so such that in the end only the path to destination remains. Recursion is brute force method, that is why we chose it because it will give maximum traversing time and path in most cases.

A* method is a special case of Dijkstra’s path finding algorithm. A shortest path tree is created while traversing through the cells using heuristics. Each cell is assigned a cost value (Weight). The minimum cost value in the vicinity of the current cell is added into the set of closed path. This is done till the end point is reached and the path is retrieved form the closed path list. This method was used as it is the best one to find shortest path.

The number of cells traversed is then displayed for both algorithms for comparison.


### Maze Picture:

![enter image description here](https://github.com/ShaheerSajid/OpenCV-Maze-Solving/blob/main/images/Picture1.png)

### Extracted Path:

![enter image description here](https://github.com/ShaheerSajid/OpenCV-Maze-Solving/blob/main/images/Picture2.png)

### Recursion:

![enter image description here](https://github.com/ShaheerSajid/OpenCV-Maze-Solving/blob/main/images/Picture3.png)

### A*:

![enter image description here](https://github.com/ShaheerSajid/OpenCV-Maze-Solving/blob/main/images/Picture4.png)


## Results

We found out that the A* algorithm is definitely more efficient than recursion for a number of reasons.

Recursion traverses a lot. It goes to places without measuring their distance from the destination.

Recursion does a lot of backtracking. Whenever a dead end is encountered it goes all the way back to the latest junction. Since its implemented on a linear data structure it has to do this. In A* when it comes to a dead end or a point further from the destination, it does not back tracks step wise. It simply jumps to the previous junction as it is implemented on a tree.

A* does not always find the shortest path, but it does so in the least time, due to jumps and heuristics. If we look at both the time and distance then A* performs better generally.

Recursion does this in much slower manner. The efficiency of recursion highly depends on the recursive sequence and the layout of maze considering the location of starting and ending points.

## Discussion and Conclusion

Implementing A* proved to be a problem. We first did it with dynamic arrays and implemented a stack instead of the binary tree. It gave unpredictable results.

Other problems and limitations listed below:

One major flaw with our program is that it can only detect mazes of equal width of walls and paths. However in real life the width is much smaller than the width of the path.

A maze of 10 by 13 cells and only 2-3 iterations of the maze is too small to test both algorithms effectively.

In real life the contrast of obstacles and path might be not so high.

In real life the height of obstacle might be different from height of path.

Additional functionality to program can be added to transmit the path coordinates to a robot.

Maze lighting conditions proved to be a major problem in extracting features

By adding features in negation to the above mentioned problems we can open multiple dimensions to our project. Further development especially in maze extraction is necessary to cater for lighting conditions. Better hardware can be used for the maze layout platform. A robot can be constructed to receive the coordinates wirelessly.

We didn’t include a method to measure time complexity. It is yet another feature we should have added to measure behavior of bot algorithms.

Testing on a bigger maze and a higher number of layout iterations is another thing which is due.

All in all this was an interesting project. Especially the OpenCV part. We learned a lot about image processing which can help us in the future.

<!--stackedit_data:
eyJoaXN0b3J5IjpbLTE0Mjg3NzA3OTcsMjAyNTQ0NTE1NywyMD
E1NTMyNzUxXX0=
-->