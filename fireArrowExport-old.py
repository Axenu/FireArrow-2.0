bl_info = {
    "name":         "FireArrowExport",
    "author":       "Simon Nilsson",
    "blender":      (2,7,1),
    "version":      (0,0,1),
    "location":     "File > Import-Export",
    "description":  "Export custom data format",
    "category":     "Import-Export"
}
        
import bpy
import math
from bpy_extras.io_utils import ExportHelper

parameters = {}
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
    self.layout.operator(ExportMyFormat.bl_idname, text="FireArrow(.fa)")

def register():
    bpy.utils.register_module(__name__);
    bpy.types.INFO_MT_file_export.append(menu_func);
    
def unregister():
    bpy.utils.unregister_module(__name__);
    bpy.types.INFO_MT_file_export.remove(menu_func);

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
    global parameters

    if not filepath.endswith(".fa"):
        filepath += ".fa"

    out_file = open( filepath, 'w' )
    objList = [object for object in bpy.data.objects if object.type == 'MESH']
    for obj in objList:
        mesh = obj.data
        mesh.calc_tessface()
        out_file.write('v ')
        out_file.write('%i ' % (len(mesh.vertices)))
        #vertices
        for vert in mesh.vertices:
            out_file.write('%f %f %f ' % (vert.co.x, vert.co.z, vert.co.y))

        #normals
        if parameters.get("Normals"):
            out_file.write('n ')
            out_file.write('%i ' % (len(mesh.tessfaces)))
            for face in mesh.tessfaces:
                out_file.write('%f %f %f ' % (face.normal.x, face.normal.z, face.normal.y))

        #colors
        if parameters.get("Colors"):
            out_file.write('c ')
            out_file.write('%i ' % (len(mesh.tessfaces)))
            for face in mesh.tessfaces:
                out_file.write('%i ' % face.material_index)
            out_file.write('m ')
            out_file.write('%i ' % (len(mesh.materials)))
            for material in mesh.materials:
                out_file.write('%f %f %f ' % (material.diffuse_color.r, material.diffuse_color.g, material.diffuse_color.b))

        
        #weight  groupnumber, weight. 2 for each vertex
        if parameters.get("Armature"):
            out_file.write('w ')
            out_file.write('%i ' % (len(mesh.vertices)))
            for vert in mesh.vertices:
                weight1 = 0.00
                weight2 = 0.00
                group1 = 0
                group2 = 0
                for group in vert.groups:
                    weightT = group.weight
                    if weightT > weight2:
                        if weightT > weight1:
                            temp = weight1
                            weight1 = weightT
                            weight2 = temp
                            i = group1
                            group1 = group.group
                            group2 = i
                        else:
                            weight2 = weightT
                            group2 = group.group
                length = weight1+weight2
                weight1 = weight1/length
                weight2 = weight2/length
                out_file.write('%i %f %i %f ' % (group1, weight1, group2, weight2))

        #indices
        out_file.write('i ')
        i = 0
        tris = 0
        indices = ""
        for face in mesh.tessfaces:
            if len(face.vertices) == 3:
                indices += '%i %i %i %i ' % (face.vertices[0], face.vertices[1], face.vertices[2], i)
                tris += 1
            else:
                indices += '%i %i %i %i ' % (face.vertices[0], face.vertices[1], face.vertices[2], i)
                indices += '%i %i %i %i ' % (face.vertices[0], face.vertices[2], face.vertices[3], i)
                tris += 2
            i += 1
        out_file.write('%i ' % (tris))
        out_file.write(indices)

    #bones
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

    out_file.close()

if __name__ == "__main__":
    register()
