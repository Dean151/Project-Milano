/***************************************
Solve Camera algorithm
Programmed in 2015

USAGE :
$ ./solveCamera.out calibration.yaml inputPoints.txt out.yaml
$ ./solveCamera.out ../../out/calibrationResults/30_02.yaml ../../data/frames.txt ../../out/solveCamera/out.yaml
*/

#include "opencv2/core/core.hpp"       // Mat, Point2f
#include "opencv2/highgui/highgui.hpp" // imwrite, VideoCapture
#include "opencv2/imgproc/imgproc.hpp" // cvtColor, CV_BGR2GRAY
#include "opencv2/calib3d/calib3d.hpp" // (find|draw)ChessboardCorners
#include <string>                      // to_string
#include <iostream>                    // cout, cerr
#include <fstream>					   // Read files
#include <vector>
#include <sstream>
#include <utility>

std::vector<std::string> explode(std::string const & s, char delim);

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

	// Getting args
	string calibrationFile(argv[1]);
	string inputPointsFile(argv[2]);
	string outYamlFile(argv[3]);

	FileStorage fs(calibrationFile, FileStorage::READ);
	if (!fs.isOpened()) {
		cerr << "The specified calibration file is not valid" << endl;
		return 1;
	}

	ifstream pointFile(inputPointsFile);  // read only opening
	if (!pointFile) {
		cerr << "The specified input point file could not be opened" << endl;
		return 1;
	}

	FileStorage out(outYamlFile, FileStorage::WRITE);
	if (!out.isOpened()) {
		cerr << "The specified out file could not be opened or created" << endl;
		return 1;
	}

	// Getting camera matrix from calibration file
	Mat cameraMatrix;
	fs["cameraMatrix"] >> cameraMatrix;

	// Getting distCoeffs matrix from calibration file
	Mat distCoeffs(4,1,cv::DataType<double>::type);
	distCoeffs.at<double>(0) = 0;
	distCoeffs.at<double>(1) = 0;
	distCoeffs.at<double>(2) = 0;
	distCoeffs.at<double>(3) = 0;

	// Creating output matrix
	Mat rvec(3,1,cv::DataType<double>::type);
	Mat tvec(3,1,cv::DataType<double>::type);

	// FIXME initial position shouldn't be written in "hard" in the code
	rvec.at<double>(0) = 200;
	rvec.at<double>(1) = 200;
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
			continue;
		}

		switch (mode) {
			case 0:
				currentFrame = std::stoi(line);
				mode = -1;
				break;
			case 1:
				coords = explode(line, ' ');
				imagePoints.push_back(Point2f(std::stod(coords[0]), std::stod(coords[1])));
				break;
			case 2:
				coords = explode(line, ' ');
				objectPoints.push_back(Point3f(std::stod(coords[0]), std::stod(coords[1]), std::stod(coords[2])));
				break;
			case 3:
				if (imagePoints.size() == objectPoints.size() && objectPoints.size() >= 4) {
					// Calculating solution
					solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec, false, CV_EPNP);

					// Writing solution
					out << "frame" << currentFrame;
					out << "rvec" << rvec; // FIXME need to use Rodrigues(src, dst, jacobian);
					out << "tvec" << tvec;
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

	return 0;
}

// Explode function
std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}
