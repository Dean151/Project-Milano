import bpy

# Deleting All
bpy.ops.object.select_all(action="SELECT")
bpy.ops.object.delete()

# Importing STL
bpy.ops.import_mesh.stl(filepath="/vagrant/Project/data/GarRep.stl")

# Alias for scene, needed for enabling camera and sun
scn = bpy.context.scene

# Creating camera
cam = bpy.data.cameras.new("magic")
obj = bpy.data.objects.new("magic", cam)
scn.objects.link(obj)
scn.camera = obj

# Camera data should be given by yaml parse
obj.rotation_mode = 'AXIS_ANGLE'
obj.rotation_axis_angle[0] = 1.6775949647875288e+00
obj.rotation_axis_angle[1] = 1.6394247253724927e+00
obj.rotation_axis_angle[2] =-2.7313663567392477e-01
obj.rotation_axis_angle[3] =-2.2805221764000944e-01
obj.location.x = -2.7112076513151294e+02
obj.location.y = -3.7260196389150241e+02
obj.location.z = -9.3188488777097902e+00
cam.clip_end = 500

# Creating sun, at our back
sun = bpy.data.lamps.new("sun", type="SUN")
obj = bpy.data.objects.new("sun", sun)
scn.objects.link(obj)

# Sun data should be given by yaml parse, or set to be constant,
# or different kind of render should be used
obj.rotation_mode = 'AXIS_ANGLE'
obj.rotation_axis_angle[0] = 1.6775949647875288e+00
obj.rotation_axis_angle[1] = 1.6394247253724927e+00
obj.rotation_axis_angle[2] =-2.7313663567392477e-01
obj.rotation_axis_angle[3] =-2.2805221764000944e-01

#Output Render
bpy.ops.render.render()
bpy.data.images[0].save_render("/vagrant/Project/out/blenderFrames/frame.png")
