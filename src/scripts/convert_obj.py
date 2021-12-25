
vertices = []
normals = []
numFaces = 0
resultVertices = []
resultIndices = []
with open("in.obj") as objFile:
    for line in objFile:
        splitline = line.split(" ")
        if splitline[0] == "v":
            vertices.append((float(splitline[1]), float(splitline[2]), float(splitline[3])))
        if splitline[0] == "vn":
            normals.append((float(splitline[1]), float(splitline[2]), float(splitline[3])))
        if splitline[0] == "f":
            for i in range(1, 4):
                splitIndex = splitline[i].split("/")
                currentVertex = (vertices[int(splitIndex[0]) - 1], normals[int(splitIndex[2]) - 1])
                if not currentVertex in resultVertices:
                    resultIndices.append(len(resultVertices))
                    resultVertices.append(currentVertex)
                else:
                    resultIndices.append(resultVertices.index(currentVertex))

def tupleToStr(tup):
    result = "{"
    for i in range(len(tup)):
        result += "{}{:.06f}f".format(" " if tup[i] >= 0 else "", tup[i])
        if i != len(tup) - 1:
            result += ", "

    result += "}"

    return result

def printVertices():
    for v in resultVertices:
        pos = (v[0][0], v[0][1], v[0][2], 1.0)
        print("{{{}, {}}},".format(tupleToStr(pos), tupleToStr(v[1])))

def printIndices():
    for i in range(len(resultIndices)):
        if i % 16 == 0:
            print()

        print("{}, ".format(resultIndices[i]), end="")

printVertices()
# printIndices(); print()

# print(len(vertices))
# print(len(normals))
print(len(resultVertices))
# print(len(resultIndices))

