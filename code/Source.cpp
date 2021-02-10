///////////////////////////  Required Libraries  /////////////////////////////////////

#include <iostream> //required for input output stream
#include <string>   //required to stream stings
#include <chrono>   //required for time measurement
#include <stack>    //reuiqred library for creating stack
#include <set>      //required library for making sets
#include "tree.h"
#include "List.h"   //library for creating single linked list
#include "opencv2/highgui/highgui.hpp" //library for using gui functions of opencv
#include "opencv2/imgproc/imgproc.hpp" //image processing functions opencv
using namespace cv;
using namespace std;
using namespace chrono;



////////////////////////////  Recursion Method  ///////////////////////////////////////

Linkedlist p1; //list to store x cordinates of path
Linkedlist p2; //list to store y cordinates of path

int f = 0;
int maze[10][13]; //2D matrix to store maze
int maze2[10][13];
String printS[2] = { "Left click mouse on start point\nand press enter.", "Left click mouse on end point\nand press enter." };// some strings to be printed

int pathCount = 0; //Variable to store number of cordinates in final path
bool ifpath = false; //boolean to store state if path is found or not
Mat HSV; //mat image to store HSV converted image
Mat thresh; //mat image store thresholded image from values of slidebars
Mat src; //mat image to store source image of maze
Mat dummy; //mat to store a dummy image used in printing
Mat d; //mat image to be used in shallow copy function
Rect rect[2]; //rectangle object array to store point of start and end

void printPath(Mat s) //function to print path on image
{
	src.copyTo(s); //copy from source image to d
	for (int i = 0; i < pathCount; i++) // loop to print line path on image
	{
		if ((i + 1) >= pathCount) break; //condition to check end of list.
		line(s, Point((p1.getData(i)) * 48 + 48 / 2, p2.getData(i) * 48 + 48 / 2), Point((p1.getData(i + 1)) * 48 + 48 / 2, p2.getData(i + 1) * 48 + 48 / 2), Scalar(0, 255, 0), 5); // line print function
	}
	imshow("Original", s); //show path on image
}
void printPoints() //print points to console
{
	for (int i = 0; i < pathCount; i++)
		cout << i+1 << " : "<< "(" << p2.getData(i) << "," << p1.getData(i) << ")" << endl;
}


bool findPath(int x, int y, bool animate) //main recursive function
{

	if (x > 12 || y > 9 || x < 0 || y < 0) return false; //reutrn false if point is out of range
	if (maze[y][x] == 3) //if end point, store end point in path list and break.
	{
		p1.appendNodeEnd(x);
		p2.appendNodeEnd(y);
		pathCount++;
		return true;
	}
	if (maze[y][x] != 1 && maze[y][x] != 2) return false; //if path is blocked or not equal to starting point break.

	maze[y][x] = 7; //make traversed path 7
	p1.appendNodeEnd(x); //append traversed point to lists
	p2.appendNodeEnd(y);
	pathCount++; //update path count
	if (animate) //if true function prints every move
	{
		printPath(d);
		cout << "Press enter to continue" << endl;
		f++;
		while (waitKey(30) != 13);
	}

	if (findPath(x, y - 1, animate) == true) return true; //check north
	if (findPath(x + 1, y, animate) == true) return true; //check east
	if (findPath(x, y + 1, animate) == true) return true;//check south
	if (findPath(x - 1, y, animate) == true) return true;//check west
		
	maze[y][x] = 8; //if dead end make that point 8
	p1.deleteNodeAt(pathCount); //delete that point from traversed path
	p2.deleteNodeAt(pathCount);
	pathCount--;	//update count
	if (animate) {
		printPath(d);
		cout << "Press enter to continue" << endl;
		f++;
	}
	while (waitKey(30) != 13);
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////  Using Astar method  ////////////////////////////////
#define ROW 10 //number of rows for storing reduced maze
#define COL 13 //number of columns for reduced maze

int checks[4][2] = { //conditions for checking paths in north, east, west, south
	{ -1,0 },
	{ 0,1 },
	{ 0,-1 },
	{ 1,0 }
};

typedef pair<int, int>Pnt; //pair for storing cordinates
typedef pair<int, pair<int, int>> olist;//pair data structure for storing fcost, cordinates in open list
struct block //structure for a single block
{
	int parentI, parentJ; //stores its parent's cordinates
	double f, g, h; //sotres f,g,h values
};

bool isInRange(int row, int col) //function to check if cordinates entered are in range
{
	return (row >= 0 && row < ROW) && (col >= 0 && col < COL);
}

bool isOpen(int grid[][COL], int row, int col)//returns true if block is open for given cordinates
{
	if (grid[row][col] == 1 || grid[row][col] == 2 || grid[row][col] == 3)
		return true;
	else
		return false;
}

bool isEnd(int row, int col, Pnt end) //returns true if destination is reached
{
	return (row == end.first && col == end.second);
}

int geth(int row, int col, Pnt end) //returns heuristic value: pythagoras from current to end point
{
	return abs(row - end.first) + abs(col - end.second); //manhatten distance
	//return sqrt(abs(row - end.first)*abs(row - end.first) + abs(col - end.second)*abs(col - end.second));
}


void Path(block b[][COL], Pnt p)//function to print path
{
	int row = p.first;//get row of end
	int col = p.second;//get column of end

	stack<Pnt> Path;//create a stack

	while (!(b[row][col].parentI == row //run while endpoint is not reached
		&& b[row][col].parentJ == col))
	{
		Path.push(make_pair(row, col)); //insert a pair of cordinates into path stack
		int temp_row = b[row][col].parentI;//make a temporary variable to store a cells parent cell so that row and col values are not disturbed
		int temp_col = b[row][col].parentJ;
		row = temp_row;//update row and col values
		col = temp_col;
	}

	Path.push(make_pair(row, col)); //push final value as it is left by while loop
	pair<int, int> po = Path.top(); //get frist value from stack
	Path.pop(); //remove it
	int c = 1;
	cout << c << " : " << "(" << po.first << "," << po.second << ")" << endl; //print it
	int tr = po.first; //store in a variable
	int tc = po.second;
	
	while (!Path.empty()) //while path is not empty
	{
		++c;
		po = Path.top(); //get value
		Path.pop(); //pop it
		cout << c << " : "<< "(" << po.first << "," << po.second << ")" << endl;//print it
		maze[po.first][po.second] = 7;//mark it as 7
		line(d, Point(tc * 48 + 48 / 2, tr * 48 + 48 / 2), Point(po.second * 48 + 48 / 2, po.first * 48 + 48 / 2), Scalar(0, 255, 0), 5);
		tr = po.first;//update values
		tc = po.second;	
	}
	return;
}



bool applyAstar(int grid[][COL], Pnt start, Pnt end)
{
	if (isInRange(start.first, start.second) == false || isInRange(end.first, end.second) == false)
	{
		cout << "Points Invalid." << endl;
		return false;
	}
	if (isOpen(maze, start.first, start.second) == false || isOpen(maze, end.first, end.second) == false)
	{
		cout << "Points blocked." << endl;
		return false;
	}
	if (isEnd(start.first, start.second, end) == true)
	{
		cout << "Destination reached." << endl;
		return false;
	}

	bool clist[ROW][COL] = { false };

	block blocks[ROW][COL];
	int i, j;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
		{
			blocks[i][j].f = 1000;
			blocks[i][j].g = 1000;
			blocks[i][j].h = 1000;
			blocks[i][j].parentI = -1;
			blocks[i][j].parentJ = -1;
		}

	i = start.first;
	j = start.second;
	blocks[i][j].f = 0.0;
	blocks[i][j].g = 0.0;
	blocks[i][j].h = 0.0;
	blocks[i][j].parentI = i;
	blocks[i][j].parentJ = j;

    Tree openlist(make_pair(0, make_pair(i, j)));
	bool fpath = false;
	int k = start.first;
	int l = start.second;
	while (!openlist.empty())
	{
	
		olist Pt = openlist.erase();
		i = Pt.second.first; 
		j = Pt.second.second;
		clist[i][j] = true;

		src.copyTo(d); //copy from source image to d
		line(d, Point(l * 48 + 48 / 2, k * 48 + 48 / 2), Point(blocks[i][j].parentJ * 48 + 48 / 2, blocks[i][j].parentI * 48 + 48 / 2), Scalar(0, 255, 0), 5);
		circle(d, Point(blocks[i][j].parentJ * 48 + 48 / 2, blocks[i][j].parentI * 48 + 48 / 2), 10,Scalar(0, 0, 255), 5);
		imshow("Original", d); //show path on image
		cout << "Press enter to continue" << endl;
		f++;
		while (waitKey(30) != 13);
		k = blocks[i][j].parentI;
		l = blocks[i][j].parentJ;


		for (int z = 0; z < 4; z++)
		{
			int newG, newH, newF;
			if (isInRange(i + checks[z][0], j + checks[z][1]) == true)
			{

				if (isEnd(i + checks[z][0], j + checks[z][1], end) == true)
				{
					blocks[i + checks[z][0]][j + checks[z][1]].parentI = i;
					blocks[i + checks[z][0]][j + checks[z][1]].parentJ = j;
		

					src.copyTo(d); //copy from source image to d
					line(d, Point(l * 48 + 48 / 2, k * 48 + 48 / 2), Point(blocks[i + checks[z][0]][j + checks[z][1]].parentJ * 48 + 48 / 2, blocks[i + checks[z][0]][j + checks[z][1]].parentI * 48 + 48 / 2), Scalar(0, 255, 0), 5);
					circle(d, Point(blocks[i + checks[z][0]][j + checks[z][1]].parentJ * 48 + 48 / 2, blocks[i + checks[z][0]][j + checks[z][1]].parentI * 48 + 48 / 2),10, Scalar(0, 0, 255), 5);
					imshow("Original", d); //show path on image
					cout << "Press enter to continue" << endl;
					f++;
					while (waitKey(30) != 13); 

					cout << "\nFound in " << f << " steps." << endl;
					Path(blocks, end);
					//while (waitKey(30) != 13);
					fpath = true;
					return fpath;
				}
				else if (clist[i + checks[z][0]][j + checks[z][1]] == false && isOpen(grid, i + checks[z][0], j + checks[z][1]) == true)
				{
					newG = blocks[i + checks[z][0]][j + checks[z][1]].g + 1.0;
					newH = geth(i + checks[z][0], j + checks[z][1], end);
					newF = newG + newH;
					if (blocks[i + checks[z][0]][j + checks[z][1]].f == 1000 || newF < blocks[i + checks[z][0]][j + checks[z][1]].f)
					{
						openlist.recursiveInsert(make_pair(newF, make_pair(i + checks[z][0], j + checks[z][1])));
						blocks[i + checks[z][0]][j + checks[z][1]].f = newF;
						blocks[i + checks[z][0]][j + checks[z][1]].g = newG;
						blocks[i + checks[z][0]][j + checks[z][1]].h = newH;
						blocks[i + checks[z][0]][j + checks[z][1]].parentI = i;
						blocks[i + checks[z][0]][j + checks[z][1]].parentJ = j;
					}
				}
			}
		}

	}
	return fpath;
}
/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////mouse Detect//////////////////////////////////////////
Pnt mouse;
void click(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		mouse = make_pair(x, y);
	}
}


int main()
{

	int count = 0;
	namedWindow("Original", 1);
	setMouseCallback("Original", click, NULL);

	/////////////Initiate Camera///////////////////////////////////////
	VideoCapture cam(0); //capture the video from web cam

	if (!cam.isOpened()) // if not success, exit program
	{
		cout << "Unable to open Webcam" << endl;
		return -1;
	}
	////////////////////////////////////////////////////////////////////


	/////////////Create window for control bars/////////////////////////
	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	int Low_H = 0;     //Hue range
	int High_H = 179;

	int Low_S = 0;     //Saturation range
	int High_S = 255;

	int Low_V = 0;     //Value range
	int High_V = 255;

	cvCreateTrackbar("LowH", "Control", &Low_H, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &High_H, 179);
	cvCreateTrackbar("LowS", "Control", &Low_S, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &High_S, 255);
	cvCreateTrackbar("LowV", "Control", &Low_V, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &High_V, 255);
	/////////////////////////////////////////////////////////////////////


    ///////////////////////Enter maze////////////////////////////////////
	cout << "Place maze properly and press enter..." << endl;
	while (true) {
		
		bool bSuccess = cam.read(dummy); // read a frame from video
		if (!bSuccess) //if not break;
		{
			cout << "Unable to read a frame from video stream" << endl;

		}
	
		////////////////////////Crop image to fit maze////////////////////
		/*Mat img(src);
		Rect roi(10, 0, 630, 480);
		src = img(roi);*/
		//////////////////////////////////////////////////////////////////

		///////////////////////////Draw Boxes/////////////////////////////
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 13; j++)
				rectangle(dummy, Point(j * 48, i * 48), Point((j + 1) * 48, (i + 1) * 48), Scalar(0, 0, 0), 5);
		/////////////////////////////////////////////////////////////////
		imshow("Original", dummy); //show the original image
		if (waitKey(30) == 13)
		{
			src = imread("../../image.jpg");
			//src = dummy;
			//cam.read(src);
			cam.release();
			break;		
		}
	}
	imshow("Original", src);
	////////////////////////////////////////////////////////////////////////


	/////////////////////////////////get paths//////////////////////////////
	cout << "Set maze to extract paths." << endl;
	while (true)
	{

		///////////////////////Threshold image to extract colour/////////
		cvtColor(src, HSV, COLOR_BGR2HSV); //src BGR to HSV		
		inRange(HSV, Scalar(Low_H, Low_S, Low_V), Scalar(High_H, High_S, High_V), thresh);
		/////////////////////////////////////////////////////////////////


		///////////////////////Smooth image to remove noise//////////////
		GaussianBlur(thresh, thresh, Size(9, 9), 2, 2);
		erode(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		imshow("Thresh", thresh);
		///////////////////////////////////////////////////////////////////	
		imshow("Original", src);
		if (waitKey(30) == 13) break;		

	}


	////////////////////////////make a maze matrix//////////////////////////////
	cout << "Solution Maze" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			Scalar intensity = thresh.at<uchar>(Point((j * 48 + (j + 1) * 48) / 2, (i * 48 + (i + 1) * 48) / 2));
			maze2[i][j] = maze[i][j] = (intensity.val[0] != 255);
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	cout << "########################################" << endl;
	////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////Get start and end/////////////////////////////////////
	cout << printS[0] << endl;
	while (count < 2)
	{

		if (waitKey(30) == 13)
		{
			if(count != 1)
			cout << printS[1] << endl;
			if (count == 0)
			{
				Rect r1( (int)(mouse.first/48)*48 ,  (int)(mouse.second/48)*48 , 48,48);
				rect[count] = r1;
				rectangle(src, rect[count], Scalar(0, 0, 255), 5);
			}
			if (count == 1)
			{
				Rect r2((int)(mouse.first / 48) * 48, (int)(mouse.second / 48) * 48, 48, 48);
				rect[count] = r2;
				rectangle(src, rect[count], Scalar(0, 255,0), 5);
			}
			count++;
		}
		imshow("Original", src);

	}
	cout<< "Start: " <<  (int)(rect[0].x+ (rect[0].width)/2) / 48  << "," <<    (int)(rect[0].y+(rect[0].height)/2)/48  << endl;
	cout<< "End: " <<    (int)(rect[1].x + (rect[1].width) / 2)/ 48  << "," << (int)(rect[1].y + (rect[1].height) / 2)/48 << endl;
	
	maze[(int)(rect[0].y + (rect[0].height) / 2) / 48][(int)(rect[0].x + (rect[0].width) / 2) / 48] = 2;
	maze2[(int)(rect[0].y + (rect[0].height) / 2) / 48][(int)(rect[0].x + (rect[0].width) / 2) / 48] = 2;
	maze[(int)(rect[1].y + (rect[1].height) / 2) / 48][(int)(rect[1].x + (rect[1].width) / 2) / 48] = 3;
	maze2[(int)(rect[1].y + (rect[1].height) / 2) / 48][(int)(rect[1].x + (rect[1].width) / 2) / 48] = 3;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	

	///////////////////////////////////////Print maze///////////////////////////////////////////////////////
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 13; j++)
			cout << maze[i][j] << " ";
		cout << endl;
	}
	cout << "#############################################" << endl;
	///////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////Solve maze//////////////////////////////////////////////////////////
	while (true)
	{

		src.copyTo(d);
		cout << "Select method to solve." << endl;
		cout << "(Press 'r'). Recursive" << endl;
		cout << "(Press 'a'). A star method" << endl;
		cout << "(Press 'ESC'). Quit" << endl;
		int t = 0;
		t = waitKey(0);
		if (t == 114)
		{
			f = 0;
			imshow("Original", d);
			int startx = 0, starty = 0;
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 13; j++)
				{
					if (maze[i][j] == 2)
					{
						startx = j;
						starty = i;
						break;
					}
				}
			ifpath = findPath(startx, starty, true);
			maze[starty][startx] = 2;

			if (ifpath)
			{
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 13; j++)
						cout << maze[i][j] << " ";
					cout << endl;
				}
				cout << "Found in " << f << " steps." << endl;
			}
			else
				cout << "\nNo path found" << endl;
			cout << "################################################" << endl;
			
			printPoints();
			printPath(d);
			for (int p = 0; p < pathCount; p++)
			{
				p1.deleteNodeAt(pathCount-p);
				p2.deleteNodeAt(pathCount-p);
			}
			pathCount = 0;
			/////////////////////////////////////////////////////////////////////////////////////////
		}
		else if (t == 97)
		{
			f = 0;
			imshow("Original", d);
			Pnt sr = make_pair((int)(rect[0].y + (rect[0].height) / 2) / 48, (int)(rect[0].x + (rect[0].width) / 2) / 48);
			Pnt dest = make_pair((int)(rect[1].y + (rect[1].height) / 2) / 48, (int)(rect[1].x + (rect[1].width) / 2) / 48);
			if (applyAstar(maze, sr, dest))
			{
				cout << endl;
				for (int i = 0; i < ROW; i++)
				{
					for (int j = 0; j < COL; j++)
						cout << maze[i][j] << " ";
					cout << endl;
				}
			}
			else
				cout << "\nNo path found" << endl;
		}
		else if (t == 27) break;

		imshow("Original", d);
		for (int q = 0; q < ROW; q++)
			for (int w = 0; w < COL; w++)
				maze[q][w] = maze2[q][w];	
		cout << "\n#################################################\n";
	}

	/*	cout << "Press Escape to exit." << endl;
		while (waitKey(30) != 27);
	//	imwrite("../../image.jpg", src);*/
		return 0;
}