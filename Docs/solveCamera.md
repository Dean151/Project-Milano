# solveCamera
SolveCamera script is provided to calculate the position of the camera in model.

## Usage
First, you need to compile it with the provided makefile :

    $ make
Then, you can use it.

You have to provide at least 3 parameters :
* The path of the input calibration file
* The path of the input points files
* The path of the output result file
* Any flag if you want to ignore distorsion from calibration yaml file (If you want to use distorsion, don't use the 4th parameter)

For example :

    $ ./solveCamera.out calibration.yaml points.txt results.yaml ignoreDistorsion

## Input data point format
The input file you need to provide for the calculation is in a very strict format.

Example :

	frame: 
	0
	cam: 
	314 314
	361 319
	251 190
	229 119
	418 136
	250 324
	449 96
	obj:
	-19648.9141 -15537.2480 99.8146
	-19338.3809 -17606.6992 111.0
	-21274.3789 -17254.6543 1815.0
	-22170.3789 -21574.6543 2055.0
	-20442.3848 -23277.3145 1588.0
	-21274.3789 -17254.6543 115.0
	-20714.3809 -24646.6543 1588.0
	end

	frame:
	25
	cam:

	......

You can provide as much as frames and points you want. But you must have at least 4 points for one frame.

Cam points are the coordonates in the frame and Obj points are the 3D coords for the same point in the 3D model.
Moreover, the cam points must be in the same order with obj points.

## Output interpretation
The output file is in yaml and contains an array of frame data.

For each frame witch the calculation ended properly, you have :
 * _frame_ : the number of the current frame.
 * _rvec_ : brut output position of the model in the camera referential
 * _tvec_ : brut output rotation matrix of the model in the camera referential
 * _cameraTranslationVector_ : Vector for the position of the camera in model.
 * _cameraRotationMatrix_ : Matrix of the rotation of the camera in model.
 * _cameraRotationVector_ : Vector of the rotation of the camera after Rodriges transform
 * _cameraRotationAngle_ : Angle of the rotation of the camera after Rodrigues transform

As Blender and OpenCV cameras doesn't follow the same rules, we also provide for each frames : 
 * _blenderCameraRotationVector_ : Blender vector of the rotation of the Blender camera.
 * _blenderCameraRotationAngle_ : Blender Angle of the rotation of the Blender camera.

 The output yaml can be used in our provided python script to generate the camera view in the model.