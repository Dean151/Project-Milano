import bpy

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
scn.render.pixel_aspect_x = 1 # Unsure of correct value here FIXME
scn.render.pixel_aspect_x = 1


# Creating camera
cam = bpy.data.cameras.new("My camera")
obj = bpy.data.objects.new("My camera", cam)
scn.objects.link(obj)
scn.camera = obj

# FIXME Camera data should be given by yaml parse
obj.rotation_mode = 'AXIS_ANGLE'
obj.rotation_axis_angle[0] = 1.6775949647875288e+00
obj.rotation_axis_angle[1] = 1.6394247253724927e+00
obj.rotation_axis_angle[2] =-2.7313663567392477e-01
obj.rotation_axis_angle[3] =-2.2805221764000944e-01
obj.location.x = -2.7112076513151294e+02
obj.location.y = -3.7260196389150241e+02
obj.location.z = -9.3188488777097902e+00

# FIXME should camera intrinsic data be hardcoded ?
cam.lens = 7.5
cam.sensor_width = 6.54
cam.sensor_height = 4.89

cam.clip_end = 500

# Creating sun, at our back
sun = bpy.data.lamps.new("sunshine", type="SUN")
obj = bpy.data.objects.new("sunshine", sun)
scn.objects.link(obj)

# FIXME Sun data should be given by yaml parse, or set to be constant,
# or different kind of render should be used
obj.rotation_mode = 'AXIS_ANGLE'
obj.rotation_axis_angle[0] = 1.6775949647875288e+00
obj.rotation_axis_angle[1] = 1.6394247253724927e+00
obj.rotation_axis_angle[2] =-2.7313663567392477e-01
obj.rotation_axis_angle[3] =-2.2805221764000944e-01

#Output Render - FIXME path should be a parameter
bpy.ops.render.render()
bpy.data.images[0].save_render("/vagrant/Project/out/blenderFrames/frame.png")
