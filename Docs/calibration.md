# Calibration
Calibration script is provided to calculate the calibration data from the camera.

## Usage
First, you need to compile it with the provided makefile :

    $ make
Then, you can use it.

You have to provide at least 2 parameters :
* The calibration video, with a chessboard (We used a 6x9 chessboard with a size of 25.5mm)
* The output yaml file path

For example :

    $ ./calibration.out input.avi calibration.yaml

If the chessboard from the calibration video is not 6x9 with a 25.5mm square size, you can change it with the 4 others facultative parameters :
* The number of calibration frames to be used for calculation (30 by default)
* Width of chessboard in number of squares (9 by default)
* Height of chessboard in number of squares (6 by default)
* Size of the side of a square, in millimeters (25.5 by default)

## Output interpretation
The output yaml file contains 2 matrix and the error quantification.

### cameraMatrix
cameraMatrix is a 3x3 matrix with camera coefficients

|     |     |     |
|:---:|:---:|:---:|
|  Fx |  0  | Cx  |
|  0  |  Fy | Cy  |
|  0  |  0  | 1   |

Fx is the x focal length. Fy is the y focal length.

Cx and Cy are the optical center position in pixel

### distCoeffs
distCoeffs is a 1x5 matrix containing the distortion properties of the camera.

|     |     |     |     |     |
|:---:|:---:|:---:|:---:|:---:|
| K1  | K2  | p1  | p2  | K3  |

That are the 5 distortion parameters used by openCV to undistort images.

### error
The error is quantified and stored in the yaml output file
