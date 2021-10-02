#include <opencv2/opencv2.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("/home/pi/Desktop/1.jpg");
	imshow("1",img);
	waitKey(0);
	}
