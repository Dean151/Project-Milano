/***************************************
Calibration algorithm
Programmed in 2015

USAGE :
$ ./calibration.out inputVideo.xxx calibrationFile.yaml
$ ./calibration.out inputVideo.xxx calibrationFile.yaml 30 9 6 25.5
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
	if (argc < 3 || argc > 7) {
		cerr << "This program takes at least 2 parameters :" 		      << endl
			 << "The path of the source video file"          			  << endl
			 << "The path of the calibration file"           			  << endl
			 << "The number of calibration frames (def: 30)" 			  << endl
			 << "The number of squares of the chessboard width (def: 9)"  << endl
			 << "The number of squares of the chessboard height (def: 6)" << endl
			 << "The square size of the chessboard (def: 25.5)"           << endl;
			
		return 1;
	}
	string videoFile(argv[1]);
	string calibrationFile(argv[2]);

	// Creating chessboard properties from args
	int width = argc >= 5 ? atoi(argv[4]) : 9;
	int height = argc >= 6 ? atoi(argv[5]) : 6;
	float squareSize = argc >= 7 ? atof(argv[6]) : 25.5;

	// number of frames for calibration
	uint nFrames = argc >= 4 ? atoi(argv[3]) : 30;

	// Opening video file
	VideoCapture cap(videoFile);
	if (!cap.isOpened()) {
		cerr << "The specified video file is not valid" << endl;
		return 1;
	}

	// Opening calibration file
	FileStorage fs(calibrationFile,FileStorage::WRITE);
	if (!fs.isOpened()) {
		cerr << "The specified calibration file path is not valid" << endl;
		return 1;
	}

	// Chessboard properties
	Size patternSize(width, height);
	vector<Point3f> objects;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			objects.push_back(Point3f(float( j*squareSize ), float( i*squareSize ),0));
		}
	}

	// Those objects contains the image and a black & white copy
	Mat image, gray;

	Size imageSize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	bool ret;

	// Initial camera matrix
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);

	// Initial distort matrix
	Mat distCoeffs = Mat::zeros(8, 1, CV_64F);

	// Vectors positions of the chessboard relative to the camera
	vector<Mat> rvecs, tvecs;
	// Creation of the chessboard in space

	// Criterion of the end of the function cornerSubpix
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, 30, 0.001);

	// Vectors of image points and coordinate
	vector<vector<Point2f>> imagePoints;
	vector<vector<Point3f>> objectPoints;
	while (imagePoints.size() < nFrames) {
		vector<Point2f> corners;
		ret = cap.read(image);
		if (!ret) {
			break;
		}
		cvtColor(image, gray, CV_BGR2GRAY );
		bool patternfound = findChessboardCorners(gray, patternSize, corners,0);
		if (patternfound) {
			cornerSubPix(gray, corners, Size(11,11), Size(-1,-1), criteria);
			imagePoints.push_back(corners);
			objectPoints.push_back(objects);
			drawChessboardCorners(image, patternSize, Mat(corners), patternfound);
		}
	}
	// Function: calibrateCamera 
	// Finds the camera intrinsic and extrinsic parameters from several views of a calibration pattern
	double error;
	error = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs);
	double fovx, fovy, focalLength, aspectRatio;
	Point2d principalPoint;
	calibrationMatrixValues(cameraMatrix, imageSize, 6.54, 4.89, fovx, fovy, focalLength, principalPoint, aspectRatio);
	fs << "cameraMatrix" << cameraMatrix;
	fs << "distCoeffs" << distCoeffs;
	fs << "error" << error;
	fs << "focalLength" << focalLength;
	fs << "aspectRatio" << aspectRatio;
	fs << "principalPoint" << principalPoint;
	fs.release();

	return 0;
}
