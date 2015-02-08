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
	if (argc != 3 && argc != 4) {
		cerr << "This program takes two or three parameters" << endl
			 << "The path of the source video file"          << endl
			 << "The path of the calibration file"           << endl
			 << "The number of calibration frames (def: 30)" << endl;
		return 1;
	}
	string videoFile(argv[1]);
	string calibrationFile(argv[2]);
	uint nFrames = argc == 4 ? atoi(argv[3]) : 30;

	// Ouverture du fichier video
	VideoCapture cap(videoFile);
	if (!cap.isOpened()) {
		cerr << "The specified video file is not valid" << endl;
		return 1;
	}

	// Ouverture du fichier de calibration
	FileStorage fs(calibrationFile,FileStorage::WRITE);
	if (!fs.isOpened()) {
		cerr << "The specified calibration file path is not valid" << endl;
		return 1;
	}
	// Proprietes de l'echiquier
	int width = 9, height = 6;
	float squareSize = 25.5;
	Size patternSize(width, height);
	vector<Point3f> objects;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			objects.push_back(Point3f(float( j*squareSize ), float( i*squareSize ),0));
		}
	}

	// Objets contenant l'image et sa copie en noir et blanc
	Mat image, gray;

	Size imageSize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	bool ret;

	// Matrice camera initiale
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);

	// Matrice distortion initiale
	Mat distCoeffs = Mat::zeros(8, 1, CV_64F);

	// Vecteurs de positions de l'echiquier par rapport a la camera
	vector<Mat> rvecs, tvecs;
	// Creation de l'echiquier dans l'espace

	// Critere de fin de la fonction cornerSubpix
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, 30, 0.001);

	// Vecteurs de points image et du repere
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
	double error;
	error = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs);
	fs << "cameraMatrix" << cameraMatrix;
	fs << "distCoeffs" << distCoeffs;
	fs << "error" << error;
	fs.release();

	return 0;
}
