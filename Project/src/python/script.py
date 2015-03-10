import bpy
import yaml


# CvMatrix (class to open YAML !!opencv-matrix data)
class CvMatrix(yaml.YAMLObject):
    # tag:yaml.org,2002: <=> !!
    yaml_tag = u'tag:yaml.org,2002:opencv-matrix'
    def __init__(self, n, m, r,arr):
        self.rows = n
        self.cols = m
        self.data = arr
    def __repr__(self):
        return "%s(rows=%r, cols=%r, data=%r)" % (
            self.__class__.__name__, self.rows, self.cols, self.data)

# Open the YAML file
fileStream = open('/vagrant/Project/out/solveCamera/out.yaml')
# Read the first line : %YAML:1.0 as yaml load does not like this line
fileStream.readline()

# parse yaml
yamlData = yaml.load(fileStream)

# Deleting All
bpy.ops.object.select_all(action="SELECT")
bpy.ops.object.delete()

# Importing STL - FIXME should be a parameter
bpy.ops.import_mesh.stl(filepath="/vagrant/Project/data/GarRep.stl")

# Alias for scene, needed for enabling camera and sun 
# FIXME resolution should be a parameter
scn = bpy.context.scene
scn.render.resolution_x = 720
scn.render.resolution_y = 576
scn.render.resolution_percentage = 100

# fix non square pixels
scn.render.pixel_aspect_x = 1 # Unsure of correct value here FIXME
scn.render.pixel_aspect_y = 1


# Creating camera
cam = bpy.data.cameras.new("My camera")
camObj = bpy.data.objects.new("My camera", cam)
scn.objects.link(camObj)
scn.camera = camObj

# FIXME should camera intrinsic data be hardcoded ?
cam.lens = 7.5
cam.sensor_width = 6.54
cam.sensor_height = 4.89

cam.clip_end = 500

# Creating sun, at our back
sun = bpy.data.lamps.new("sunshine", type="SUN")
sunObj = bpy.data.objects.new("sunshine", sun)
scn.objects.link(sunObj)

# FIXME Sun data should be given by yaml parse, or set to be constant,
# or different kind of render should be used


for frame in data["framedata"]:
    # get blenderCameraRotationAngle
    blenderCameraRotationAngle = frame["blenderCameraRotationAngle"]
    # get blenderCameraRotationVector
    blenderCameraRotationVector = frame["blenderCameraRotationVector"].data
    # get cameraRotationVector
    cameraTranslationVector = frame["cameraTranslationVector"].data
    # FIXME Camera data should be given by yaml parse
    camObj.rotation_mode = 'AXIS_ANGLE'
    camObj.rotation_axis_angle[0] = blenderCameraRotationAngle
    camObj.rotation_axis_angle[1] = blenderCameraRotationVector[0]
    camObj.rotation_axis_angle[2] = blenderCameraRotationVector[1]
    camObj.rotation_axis_angle[3] = blenderCameraRotationVector[2]
    camObj.location.x = cameraTranslationVector[0]
    camObj.location.y = cameraTranslationVector[1]
    camObj.location.z = cameraTranslationVector[2]
    #Output Render - FIXME path should be a parameter
    bpy.ops.render.render()
    bpy.data.images[0].save_render("/vagrant/Project/out/blenderFrames/frame"+str(frame["frame"])+".png")
