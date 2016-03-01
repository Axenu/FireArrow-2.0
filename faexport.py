bl_info = {
    "name":         "FireArrow Export",
    "author":       "Simon Nilsson",
    "blender":      (2,7,1),
    "version":      (0,1,0),
    "location":     "File > Import-Export",
    "description":  "Export custom data format",
    "category":     "Import-Export"
}
        
import bpy
import math
from bpy_extras.io_utils import ExportHelper

parameters = {}
finalNormals = []
index = -1

class ExportMyFormat(bpy.types.Operator, ExportHelper):
    bl_idname       = "export_my_format.fa";
    bl_label        = "FireArrow export";
    bl_options      = {'PRESET'};

    vnormals = bpy.props.BoolProperty(name="Export Vertex Normals", default=True)
    vcolors  = bpy.props.BoolProperty(name="Export Vertex Colors", default=True)
    armature  = bpy.props.BoolProperty(name="Export Armature", default=False)
    
    filename_ext    = ".fa";
    
    def execute(self, context):
        global parameters
        parameters["Normals"] = self.vnormals
        parameters["Colors"] = self.vcolors
        parameters["Armature"] = self.armature

        export(self.filepath)
        return {'FINISHED'}

def menu_func(self, context):
    self.layout.operator(ExportMyFormat.bl_idname, text="FireArrow(.fa)");

def register():
    bpy.utils.register_module(__name__);
    bpy.types.INFO_MT_file_export.append(menu_func);
    
def unregister():
    bpy.utils.unregister_module(__name__);
    bpy.types.INFO_MT_file_export.remove(menu_func);

def addNormal(normal):
    global finalNormals
    index = 0
    for n in finalNormals:
        if n == normal:
            return index
        index+=1
    finalNormals.append(normal)
    return index

def printBone(bone, parent):
    global index
    index += 1
    bindex = index
    pos = bone.matrix_local.to_translation()
    string = bone.name
    if bone.parent is not None:
        string += '%s ' % bone.parent.name
    else:
        string += ' None'
    string += '%i ' % parent
    string += '%f ' % pos.x + '%f ' % pos.z + '%f ' % pos.y
    for b in bone.children:
        string += printBone(b, bindex)
    return string

class FABone:
    def __init__(self, name, pos, parent, index):
        self.name = name
        self.pos = pos
        self.parent = parent
        self.index = index

def export(filepath):
    global finalNormals

    out_file = open( filepath, 'w' )
    objList = [object for object in bpy.data.objects if object.type == 'MESH']
    for obj in objList:
        mesh = obj.data
        mesh.calc_tessface()

        vertices = []
        smoothNormals = []
        normalIndex = 0
        weights = [] #4 per vertex
        indices = []

        #vertices
        # out_file.write('v ')
        # out_file.write('%i ' % (len(mesh.vertices)))
        for vert in mesh.vertices:
            # out_file.write('%f %f %f ' % (vert.co.x, vert.co.z, vert.co.y))
            vertices.append(vert.co)

            #normals
            if parameters.get("Normals"):
            # out_file.write('n ')
            # out_file.write('%i ' % (len(mesh.tessfaces)))
            # for face in mesh.tessfaces:
            #     out_file.write('%f %f %f ' % (face.normal.x, face.normal.z, face.normal.y))
                smoothNormals.append(vert.normal)
        
            #weight  groupnumber, weight. 4 for each vertex
            if parameters.get("Armature"):
                length = 0.0;
                for group in vert.groups:
                    weights.append(group.group)
                    weights.append(group.weight)
                    length += group.weight

                for i in range(len(vert.groups), 4):
                    weights.append(0)
                    weights.append(0)
                elements = len(weights) - 1
                weights[elements] = weights[elements]/length
                elements -= 2
                weights[elements] = weights[elements]/length
                elements -= 2
                weights[elements] = weights[elements]/length
                elements -= 2
                weights[elements] = weights[elements]/length

        indiceCount = 0
        for face in mesh.tessfaces:
            for i in range(2,len(face.vertices)):
                indiceCount += 3
                indices.append(face.vertices[0])
                indices.append(face.vertices[i-1])
                indices.append(face.vertices[i])

                if parameters.get("Normals"):
                    if face.use_smooth:
                        index = addNormal(smoothNormals[face.vertices[0]])
                        indices.append(index)
                        index = addNormal(smoothNormals[face.vertices[i-1]])
                        indices.append(index)
                        index = addNormal(smoothNormals[face.vertices[i]])
                        indices.append(index)
                    else:
                        index = addNormal(face.normal)
                        indices.append(index)
                        indices.append(index)
                        indices.append(index)
                if parameters.get("Colors"):
                    indices.append(face.material_index)

        #store in file
        out_file.write('v ')
        out_file.write('%i ' % (len(vertices)))
        for vert in vertices:
            out_file.write('%f %f %f ' % (vert.y, vert.z, vert.x))

        #normals
        if parameters.get("Normals"):
            out_file.write('n ')
            out_file.write('%i ' % (len(finalNormals)))
            for norm in finalNormals:
                out_file.write('%f %f %f ' % (norm.y, norm.z, norm.x))

        #materials
        if parameters.get("Colors"):
            out_file.write('c ')
            out_file.write('%i ' % (len(mesh.materials)))
            for material in mesh.materials:
                out_file.write('%f %f %f ' % (material.diffuse_color.r, material.diffuse_color.g, material.diffuse_color.b))



        #indices
        out_file.write('i ')
        out_file.write('%i ' % (indiceCount))
        for index in indices:
            out_file.write('%i ' % (index))


        #armature
        if parameters.get("Armature"):
            out_file.write('b ')
            armature = [object for object in bpy.data.objects if object.type == 'ARMATURE']
            for arm in armature:
                out_file.write('%i ' % len(arm.data.bones))
                # for bone in arm.data.bones:
                #     b = Bone()
                #     b.name = bone.name
                #     b.pos = bone.matrix_local.to_translation()
                # if len(arm.data.bones) > 0:
                #     rootBone = arm.data.bones[0]
                #     out_file.write('%s' % (printBone(rootBone, -1)))
                boneList = {}
                i = 0
                for bone in arm.data.bones:
                    pos = bone.matrix_local.to_translation()
                    if bone.parent is not None:
                        b = FABone(bone.name, pos, bone.parent.name, i)
                    else:
                        b = FABone(bone.name, pos, 'None', i)
                    i += 1
                    boneList[bone.name] = b
                for bone in arm.data.bones:
                    out_file.write('%s ' % bone.name)
                    if bone.parent is not None:
                        out_file.write('%i ' % boneList[bone.parent.name].index)
                    else:
                        out_file.write('-1 ')
                    pos = bone.matrix_local.to_translation()
                    out_file.write('%f %f %f ' % (pos.x, pos.z, pos.y))

                #animations
                out_file.write('a ')
                out_file.write('%i ' % len(arm.animation_data.nla_tracks))
                for track in arm.animation_data.nla_tracks:
                    #name?
                    for strip in track.strips:
                        out_file.write('%i ' % len(strip.action.fcurves[0].keyframe_points))
                        for keyframe in strip.action.fcurves[0].keyframe_points:
                            bpy.context.scene.frame_set(keyframe.co.x)
                            for bone in arm.pose.bones:
                                out_file.write('%f %f %f %f ' % (bone.rotation_quaternion.x, bone.rotation_quaternion.y, bone.rotation_quaternion.z, bone.rotation_quaternion.w))



    out_file.close()

if __name__ == "__main__":
    register()
