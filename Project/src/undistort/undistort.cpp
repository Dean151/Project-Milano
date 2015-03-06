/***************************************
Undistort algorithm
Programmed in 2015

USAGE :
$ undistort.out inputVideo.xxx calibrationFile.yaml outputVideo.xxx
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
		cerr << "The path of the source video file"   << endl;
		cerr << "The path of the calibration file"    << endl;
		cerr << "The path of the output video file"   << endl;
		return 1;
	}

	string inputVideoFile(argv[1]);
	string calibrationFile(argv[2]);
	string outputVideoFile(argv[3]);

	// Opening the input video
	VideoCapture cap(inputVideoFile);
	if (!cap.isOpened()) {
		cerr << "The specified video file is not valid" << endl;
		return 1;
	}

	// Opening the calibration file
	FileStorage fs(calibrationFile, FileStorage::READ);
	if (!fs.isOpened()) {
		cerr << "The specified calibration file is not valid" << endl;
		return 1;
	}

	int fourcc = cap.get(CV_CAP_PROP_FOURCC);//CV_FOURCC('X','V','I','D');
	int fps = cap.get(CV_CAP_PROP_FPS);
	Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH),
	               cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	// Initializing the video writer
	VideoWriter vid(outputVideoFile, fourcc, fps, frameSize);
	if (!vid.isOpened()) {
		cerr << "The specified output file is not valid" << endl;
		return 1;
	}

	// Getting camera informations
	Mat cameraMatrix, distCoeffs;
	fs["cameraMatrix"] >> cameraMatrix;
	fs["distCoeffs"] >> distCoeffs;

	Mat image, undist;
	bool ret;
	int i = 0;
	while (true) {
		ret = cap.read(image);
		if (!ret) {
			break;
		}
		undistort(image, undist, cameraMatrix, distCoeffs);
		if (i % 25 == 0) { // We record the first frame of each seconds
			imwrite("../../out/jpg/" + to_string(i) + ".jpg",undist);
		}
		i++;
		vid << undist;
	}
	vid.release();
	cap.release();
	return 0;
}
