/***************************************
Solve Camera algorithm
Programmed in 2015

USAGE :
$ ./solveCamera.out calibration.yaml inputPoints.txt out.yaml
$ ./solveCamera.out ../../out/calibrationResults/30_02.yaml ../../data/frames.txt ../../out/solveCamera/out.yaml ignoreDistorsion
*/

#include "opencv2/core/core.hpp"       // Mat, Point2f
#include "opencv2/highgui/highgui.hpp" // imwrite, VideoCapture
#include "opencv2/imgproc/imgproc.hpp" // cvtColor, CV_BGR2GRAY
#include "opencv2/calib3d/calib3d.hpp" // (find|draw)ChessboardCorners
#include "math.h"
#include <string>                      // to_string
#include <iostream>                    // cout, cerr
#include <fstream>					   // Read files
#include <vector>
#include <sstream>
#include <utility>

using namespace cv;
using namespace std;

vector<string> explode(string const & s, char delim);

int main( int argc, const char** argv )
{
	//Show errors with respect to input parameters
	if (argc < 4 || argc > 5)
	{
		cerr << "This program takes at least three parameters" << endl;
		cerr << "The path of the input calibration file"   << endl;
		cerr << "The path of the input points file"    << endl;
		cerr << "The path of output yaml file"   << endl;
		cerr << "(optional) ignoreDistorsion flag, to ignore distorsion from yaml calibration file." << endl;
		return 1;
	}

	// If there is the fourth argument... (Ugly solution. It should have been an option like --ignore-distorsion, but too complicated for my tiny mind)
	bool ignoreDistorsion = false;
	if (argc == 5) {
		ignoreDistorsion = true;
	}

	// Getting args
	string calibrationFile(argv[1]);
	string inputPointsFile(argv[2]);
	string outYamlFile(argv[3]);

	// Opening calibration file
	FileStorage fs(calibrationFile, FileStorage::READ);
	if (!fs.isOpened()) {
		cerr << "The specified calibration file is not valid" << endl;
		return 1;
	}

	// Read only opening
	ifstream pointFile(inputPointsFile);  
	if (!pointFile) {
		cerr << "The specified input point file could not be opened" << endl;
		return 1;
	}

	// Opening out file
	FileStorage out(outYamlFile, FileStorage::WRITE);
	if (!out.isOpened()) {
		cerr << "The specified out file could not be opened or created" << endl;
		return 1;
	}
	out << "framedata" << "[";

	// Getting camera matrix from calibration file
	Mat cameraMatrix;
	fs["cameraMatrix"] >> cameraMatrix;

	// Getting distCoeffs matrix from calibration file
	Mat distCoeffs(4,1,cv::DataType<double>::type);

	if (ignoreDistorsion) {
		distCoeffs.at<double>(0) = 0;
		distCoeffs.at<double>(1) = 0;
		distCoeffs.at<double>(2) = 0;
		distCoeffs.at<double>(3) = 0;
	} else {
		fs["distCoeffs"] >> distCoeffs; 
	}

	// Creating output matrix
	Mat rvec(3,1,DataType<double>::type);
	Mat tvec(3,1,DataType<double>::type);

	// Declaring the different transformation matrices (and vector representations,
	// via Rodriguez)
	// objectRotationMatrix, cameraRotationMatrix and cameraTranslationVector
	// 
	// blender uses a unit vector, with different axis conventions for the rotation.
	// defining the opencv to blender conversion matrice = halfTurnAroundX_V
	Mat objectRotationMatrix(3,3,DataType<double>::type);
	Mat cameraRotationMatrix(3,3,DataType<double>::type);
	Mat cameraRotationVector(3,1,DataType<double>::type);
	Mat cameraTranslationVector;

	Mat blenderCameraRotationVector(3,1,DataType<double>::type);

	Mat halfTurnAroundX_V(3,1,DataType<double>::type);
	halfTurnAroundX_V.at<double>(0) = M_PI;
	halfTurnAroundX_V.at<double>(1) = 0;
	halfTurnAroundX_V.at<double>(2) = 0;
	Mat halfTurnAroundX_M(3,3,DataType<double>::type);
	Rodrigues(halfTurnAroundX_V, halfTurnAroundX_M);
	
	// Initial position for iterative calculation
	rvec.at<double>(0) = 0;
	rvec.at<double>(1) = 0;
	rvec.at<double>(2) = 0;

	// Read corresponding points for solvePnp calculation
	vector<Point2f> imagePoints;
	vector<Point3f> objectPoints;

	vector<string> coords;
	int currentFrame = -1;
	string line;
	int mode = -1; // 0 for new frame, 1 for cam points, 2 for obj points

	while(getline(pointFile, line)) {
		if (line.compare(0, 5, "frame") == 0) {
			mode = 0;
			continue;
		}
		if (line.compare(0, 3, "cam") == 0) {
			mode = 1;
			continue;
		}
		if (line.compare(0, 3, "obj") == 0) {
			mode = 2;
			continue;
		}
		if (line.compare(0, 3, "end") == 0) {
			mode = 3;
			getline(pointFile, line);
		}

		switch (mode) {
			case 0:
				currentFrame = stoi(line);
				mode = -1;
				break;
			case 1:
				coords = explode(line, ' ');
				imagePoints.push_back(Point2f(stod(coords[0]), stod(coords[1])));
				break;
			case 2:
				coords = explode(line, ' ');
				objectPoints.push_back(Point3f(stod(coords[0]), stod(coords[1]), stod(coords[2])));
				break;
			case 3:
				if (imagePoints.size() == objectPoints.size() && objectPoints.size() >= 4) {
					// Calculating solution
					solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec, false, CV_EPNP);
					
					// Switching to matrix representation
					Rodrigues(rvec,objectRotationMatrix);

					// Transposing to get camera rotation instead of object rotation
					transpose(objectRotationMatrix, cameraRotationMatrix);

					// Switching back to vector representation, openCV and blender
					Rodrigues(cameraRotationMatrix, cameraRotationVector);
					Rodrigues(cameraRotationMatrix * halfTurnAroundX_M, blenderCameraRotationVector);

					// Getting camera translation vector: cv = -cm * objv 
					cameraTranslationVector = -cameraRotationMatrix * tvec;
					
					// Output solution
					out << "{";
					out << "frame" << currentFrame;
					out << "rvec" << rvec;
					out << "cameraRotationMatrix" << cameraRotationMatrix;
					out << "blenderCameraRotationVector" << blenderCameraRotationVector;
					out << "blenderCameraRotationAngle"  << norm(blenderCameraRotationVector);
					out << "cameraRotationVector" << cameraRotationVector;
					out << "cameraRotationAngle" << norm(cameraRotationVector);
					out << "cameraTranslationVector" << cameraTranslationVector;
					out << "tvec" << tvec;
					out << "}";
				} else {
					cerr << "Frame number " << currentFrame << " was ignored" << endl;
				}

				imagePoints.clear();
				objectPoints.clear();

				mode = -1;
				currentFrame = -1;
				break;
		}
	}
	out << "]";
	return 0;
}

// Explode function
vector<string> explode(string const & s, char delim)
{
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }

    return result;
}
