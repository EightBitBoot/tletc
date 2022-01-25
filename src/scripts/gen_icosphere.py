from copy import deepcopy
import sys
from math import sqrt
from dataclasses import dataclass
import numpy as np

class vec3:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def length(self):
        return sqrt(self.x**2 + self.y**2 + self.z**2)

    def normalize(self):
        self /= self.length()
        
    def __itruediv__(self, div):
        self.x /= div
        self.y /= div
        self.z /= div
        return self

    def __truediv__(self, div):
        result = deepcopy(self)
        result /= div
        return result

    def __iadd__(self, other):
        self.x += other.x
        self.y += other.y
        self.z += other.z
        return self

    def __add__(self, other):
        result = deepcopy(self)
        result += self
        return result

    def __repr__(self):
        return "Vertex(x={}, y={}, z={})".format(self.x, self.y, self.z)

    def __str__(self):
        return "{{{}{:.06f}f, {}{:.06f}f, {}{:.06f}f}}".format(" " if self.x >= 0 else "", self.x, " " if self.y >= 0 else "", self.y, " " if self.z >= 0 else "", self.z)


@dataclass
class Vertex:
    pos: vec3
    norm: vec3 

    def __str__(self):
        return "{{{{{}{:.06f}f, {}{}, {}{:.06f}f, {}{:.06f}f, 1.0f}}, {{{}}}}}".format(" " if self.pos.x >= 0 else "", self.pos.x, " " if self.pos.y >= 0 else "", self.pos.y, " " if self.pos.z >= 0 else "", self.pos.z, str(self.norm))


icoFaces = [(0, 1, 2),   (1, 0, 5),  (0, 2, 3),  (0, 3, 4),  (0, 4, 5),
            (1, 5, 10),  (2, 1, 6),  (3, 2, 7),  (4, 3, 8),  (5, 4, 9),
            (1, 10, 6),  (2, 6, 7),  (3, 7, 8),  (4, 8, 9),  (5, 9, 10),
            (6, 10, 11), (7, 6, 11), (8, 7, 11), (9, 8, 11), (10, 9, 11)]

icoVertices = [vec3(x= 0.000000, y=-1.000000, z= 0.000000), vec3(x= 0.723600, y=-0.447215, z= 0.525720),
               vec3(x=-0.276385, y=-0.447215, z= 0.850640), vec3(x=-0.894425, y=-0.447215, z= 0.000000),
               vec3(x=-0.276385, y=-0.447215, z=-0.850640), vec3(x= 0.723600, y=-0.447215, z=-0.525720),
               vec3(x= 0.276385, y= 0.447215, z= 0.850640), vec3(x=-0.723600, y= 0.447215, z= 0.525720),
               vec3(x=-0.723600, y= 0.447215, z=-0.525720), vec3(x= 0.276385, y= 0.447215, z=-0.850640),
               vec3(x= 0.894425, y= 0.447215, z= 0.000000), vec3(x= 0.000000, y= 1.000000, z= 0.000000)]


def getMidpoint(midpointCache, vertices, index0, index1):
    key = (0 ,0)
    if index0 > index1:
        key = (index1, index0)
    else:
        key = (index0, index1)

    if key in midpointCache:
        return midpointCache[key]

    v0 = vertices[index0]
    v1 = vertices[index1]
    midpoint = vec3((v0.x + v1.x) / 2, (v0.y + v1.y) / 2 ,(v0.z + v1.z) / 2)
    midpoint.normalize()
    midpointCache[key] = len(vertices)
    vertices.append(midpoint)

    return len(vertices) - 1


def subdivideSphere(vertices, faces):
    midpointCache = {}
    resFaces = []
    faceNormals = {}

    for face in faces:
        midpoints = []

        for i in range(3):
            midpoints.append(getMidpoint(midpointCache, vertices, face[i], face[(i + 1) % 3]))

        resFaces.append((face[0],      midpoints[0], midpoints[2]))
        resFaces.append((face[1],      midpoints[1], midpoints[0]))
        resFaces.append((face[2],      midpoints[2], midpoints[1]))
        resFaces.append((midpoints[0], midpoints[1], midpoints[2]))

    return resFaces


def generateSphere(numSubdivisions):
    vertices = deepcopy(icoVertices)
    faces = deepcopy(icoFaces)

    for _ in range(numSubdivisions):
        faces = subdivideSphere(vertices, faces)

    return vertices, faces


def main():
    # print(" ".join([str(v.length()) for v in icoVertices]))
    # return

    numSubdivisions = 4 # Default number of subdivisions
    if len(sys.argv) > 1:
        numSubdivisions = int(sys.argv[1])
    
    vertices, faces = generateSphere(numSubdivisions) 

    # with open("icosphere.txt", "w+") as outfile:
    #     outfile.write("Vertices:\n")
    #     outfile.write(",\n".join([str(v) for v in vertices])) 
    #     outfile.write("\n\n")
    #     outfile.write("Indices:\n")
    #     outfile.write(",\n".join(["{}, {}, {}".format(f[0], f[1], f[2]) for f in faces]))

    #     print("NumVertices: " + str(len(vertices)))
    #     print("NumFaces: " + str(len(faces)))
    #     print("Written to icosphere.txt")

    with open("i.obj", "w+") as outfile:
        for vertex in vertices:
            outfile.write("v {} {} {}\n".format(vertex.x, vertex.y, vertex.z))

        outfile.write("s off\n")

        for face in faces:
            outfile.write("f {} {} {}\n".format(face[0] + 1, face[1] + 1, face[2] + 1))


if __name__ == "__main__":
    main()