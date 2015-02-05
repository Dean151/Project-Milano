#include "opencv2/core/core.hpp"       // Mat, Point2f
#include "opencv2/highgui/highgui.hpp" // imwrite, VideoCapture
#include "opencv2/imgproc/imgproc.hpp" // cvtColor, CV_BGR2GRAY
#include "opencv2/calib3d/calib3d.hpp" // (find|draw)ChessboardCorners
#include <string>                      // to_string
#include <iostream>                    // cout, cerr

using namespace cv;
using namespace std;

void padTo(string &str, const size_t num, const char paddingChar='0');

int main( int argc, const char** argv )
{
	if (argc != 2) {
		cerr << "This program takes two parameters\n";
		cerr << "The path of the source video file\n";
		return 1;
	}

	VideoCapture cap = VideoCapture(string(argv[1]));

	if (!cap.isOpened()) {
		cerr << "The specified video file is not valid\n";
		return 1;
	}

	int i = 0, width = 9, height = 6;
	Mat image, gray;
	bool ret;
	Size patternSize(width, height);
	vector<Point2f> corners;

	while (true) {
		ret = cap.read(image);
		if (!ret) {
			break;
		}
		cvtColor(image, gray, CV_BGR2GRAY );
		bool patternfound = findChessboardCorners(gray, patternSize, corners,0);
		string name = to_string(i++);
		padTo(name,4);
		if (patternfound) {
			drawChessboardCorners(image, patternSize, Mat(corners), patternfound);
			imwrite("jpg/"+name+".jpg", image);
		}
	}
	return 0;
}

void padTo(string &str, const size_t num, const char paddingChar/* = '0' */)
{
	if(num > str.size())
		str.insert(0, num - str.size(), paddingChar);
}
