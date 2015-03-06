/***************************************
Solve Camera algorithm
Programmed in 2015

USAGE :
$ solveCamera calibration.yaml inputPoints.txt out.yaml
$ solveCamera ../../out/calibrationResults/30_02.yaml inputPoints.txt out.yaml
*/

#include "opencv2/core/core.hpp"       // Mat, Point2f
#include "opencv2/highgui/highgui.hpp" // imwrite, VideoCapture
#include "opencv2/imgproc/imgproc.hpp" // cvtColor, CV_BGR2GRAY
#include "opencv2/calib3d/calib3d.hpp" // (find|draw)ChessboardCorners
#include <string>                      // to_string
#include <iostream>                    // cout, cerr

using namespace cv;
using namespace std;

int main( int argc, const char** argv )
{
	if (argc != 4)
	{
		cerr << "This program takes three parameters" << endl;
		cerr << "The path of the input calibration file"   << endl;
		cerr << "The path of the input points file"    << endl;
		cerr << "The path of output yaml file"   << endl;
		return 1;
	}

	string calibrationFile(argv[1]);

	// FIXME use an input file for points
	string inputPoints(argv[2]); // NOT USED YET
	
	string outYamlFile(argv[3]);

	FileStorage fs(calibrationFile, FileStorage::READ);
	if (!fs.isOpened()) {
		cerr << "The specified calibration file is not valid" << endl;
		return 1;
	}

	FileStorage out(outYamlFile, FileStorage::WRITE);
	if (!out.isOpened()) {
		cerr << "The specified calibration file is not valid" << endl;
		return 1;
	}

	vector<Point2f> imagePoints;
	vector<Point3f> objectPoints;

	// Getting camera matrix from calibration file
	Mat cameraMatrix;
	fs["cameraMatrix"] >> cameraMatrix;

	// Getting distCoeffs matrix from calibration file
	Mat distCoeffs(4,1,cv::DataType<double>::type);
	fs["distCoeffs"] >> distCoeffs;

	// Creating output matrix
	Mat rvec(3,1,cv::DataType<double>::type);
	Mat tvec(3,1,cv::DataType<double>::type);

	// FIXME initial position shouldn't be written in "hard" in the code
	rvec.at<double>(0) = 200;
	rvec.at<double>(1) = 200;
	rvec.at<double>(2) = 0;

	// FIXME read points from input file, this is dirty
	 imagePoints.push_back(Point2f(456,352));
	objectPoints.push_back(Point3f(-225.7404,-230,0));
	 imagePoints.push_back(Point2f(456,87));
	objectPoints.push_back(Point3f(-225.7404,-230.5175,15.98));
	//  imagePoints.push_back(Point2f(352,335));
	// objectPoints.push_back(Point3f(-225.69119,-205.60655,0));
	//  imagePoints.push_back(Point2f(350,178));
	// objectPoints.push_back(Point3f(-225.69119,-205.60655,19.317));
	 imagePoints.push_back(Point2f(222,355));
	objectPoints.push_back(Point3f(-245.4893,-226.48495,0));
	 imagePoints.push_back(Point2f(224,76));
	objectPoints.push_back(Point3f(-245.4893,-226.48495,16.99));


	// Calculating solution
	solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec, false, CV_P3P);

	// Writing solution
	out << "rvec" << rvec;
	out << "tvec" << tvec;

	return 0;
}