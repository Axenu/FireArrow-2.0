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

class ExportMyFormat(bpy.types.Operator, ExportHelper):
    bl_idname       = "export_my_format.fa";
    bl_label        = "FireArrow export";
    bl_options      = {'PRESET'};
    
    filename_ext    = ".fa";
    
    def execute(self, context):
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

index = 0

def printBone(bone, parent):
    global index
    bindex = index
    pos = bone.matrix_local.to_translation()
    string = bone.name
    string += ' %i' % parent
    string += ' %f' % pos.x + ' %f' % pos.z + ' %f' % pos.y
    for b in bone.children:
        string += ' '
        index += 1
        string += printBone(b, bindex)
    return string

def export(filepath):

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
        out_file.write('n ')
        out_file.write('%i ' % (len(mesh.tessfaces)))
        for face in mesh.tessfaces:
            out_file.write('%f %f %f ' % (face.normal.x, face.normal.z, face.normal.y))
        
        #weight  groupnumber, weight. 2 for each vertex
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
    out_file.write('b ')
    armature = [object for object in bpy.data.objects if object.type == 'ARMATURE']
    for arm in armature:
        out_file.write('%i ' % len(arm.data.bones))
        if len(arm.data.bones) > 0:
            rootBone = arm.data.bones[0]
            out_file.write('%s' % (printBone(rootBone, -1)))

    out_file.close()

if __name__ == "__main__":
    register()
