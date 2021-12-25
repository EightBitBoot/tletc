from collections import namedtuple
import sys
import math

Vertex = namedtuple("Vertex", "x y z")

def gs(value):
    return " " if value >= 0 else ""


def makeCylinder(factor):
    vertices = []
    indices = []

    step = (2 * math.pi) / factor

    currentAngle = 0
    for i in range(factor):
        x = 0.5 *   math.cos(currentAngle)
        z = 0.5 * (-math.sin(currentAngle))

        baseIndex = 2 * i

        vertices.append(Vertex(x, -0.5, z))
        vertices.append(Vertex(x,  0.5, z))

        indices.extend([baseIndex, (baseIndex + 3) % (2 * factor), (baseIndex + 1) % (2 * factor), baseIndex, (baseIndex + 2) % (2 * factor), (baseIndex + 3) % (2 * factor)])

        currentAngle += step

    return vertices, indices


def main():
    factor = 10
    if len(sys.argv) > 1:
        factor = int(sys.argv[1])

    vertices, indices = makeCylinder(factor)

    print("Vertices:")
    for vertex in vertices:
        print("{{{{{}{:.06f}f, {}{:.06f}f, {}{:.06f}f, 1.0f}}, {{{}{:.06f}f, {}{:.06f}f, {}{:.06f}f}}}},".format(gs(vertex.x), vertex.x, gs(vertex.y), vertex.y, gs(vertex.z), vertex.z, gs(vertex.x), vertex.x, " ", 0.0, gs(vertex.z), vertex.z))

    print()

    print("Indices:")
    for i in range(len(indices)):
        if(i % 6 == 0):
            print()

        print("{}, ".format(indices[i]), end="")


if __name__ == "__main__":
    main()