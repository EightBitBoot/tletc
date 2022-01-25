
NOTE: The lag on startup is loading a bunch of textures in a single thread that are probably too big for practicality

Dependencies:
    - GLFW https://www.glfw.org/
    - GLEW http://glew.sourceforge.net/
    - GLM  https://glm.g-truc.net/0.9.9/index.html

Building:
    1) Run the premake5 generator for target system (ex. linux: premake5 gmake2)
    2) Build using the generated build files (ex. linux: make)

Running:
    - Run "bin/<premake_config>/tletc resources" from the root directory of the project

    NOTE: the shader paths are hardcoded to the src/ directory so the current directory
          of the executable must be the root.  Additionally resources is passed as an
          argument to select the location of the resources directory.  I know this is
          hacky and will be fixed with a virtual file system for loading from disk.

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
