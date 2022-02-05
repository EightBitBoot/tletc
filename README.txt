
NOTE: The lag on startup is loading a bunch of textures in a single thread that are probably too big for practicality

Dependencies:
    - GLFW https://www.glfw.org/
    - GLEW http://glew.sourceforge.net/
    - GLM  https://glm.g-truc.net/0.9.9/index.html

Building:
    1) Run the premake5 generator for target system (ex. linux: premake5 gmake2)
    2) Build using the generated build files (ex. linux: make)

Running:
    - Run the executable generated in bin/<premake_config>/tletc

    NOTE: The vfs handles resource file path resolution, however the usage in main.c
          currently mounts paths relative to the location of the executable.  This
          means that the executable can be run from any working directory, but the
          resource directories can't be moved relative to the executable.
          Additionally, the system used to find the executable directory uses procfs
          and the linux layout of that fs.  This shouldn't be an issue in 99% of use
          cases, but is important to note for the very few cases where it will fail.

Controls:
    - Scroll wheel adjusts fov

    - w: move camera forward
    - a: move camera left
    - s: move camera backward
    - d: move camera right

    - up: move camera up
    - down: move camera down
    - left: tilt camera up
    - right: tilt camera down

    - i: move light forward
    - j: move light left
    - k: move light backward
    - l: move light right
    - u: move camera down
    - o: move camera up

    - p: print camera and light data

    - r: reset camera position and fov
    - alt-r: reloate shaders

    - q: quit the program
    - esc quit the program
