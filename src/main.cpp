#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <vector>
#include <string>
#include <filesystem>

#include <unistd.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "error.h"
#include "program.h"
#include "buffer.h"
#include "cube.h"
#include "teapot.h"
#include "material.h"
#include "materialregistry.h"
#include "quad.h"
#include "pie.h"
#include "basket.h"
#include "icosphere.h"
#include "cylinder.h"
#include "vfs.h"

using namespace glm;

typedef struct Camera_s {
    vec3 pos;
    float theta;
    float fov;
} Camera;

Camera defaultCamera = {
    vec3(0.0f, 2.0f, -1.7f),
    24.0f,
    49.0f
};
Camera camera = defaultCamera;
vec4 lightPos(1.4f, 3.3f, -2.299f, 1.0f);

std::string resourcesPath;
bool reloadShaders = true;

void glfwErrorCallback(int errorCode, char *errorMessage) {
    fprintf(stderr, "GLFW Error: %d: %s\n", errorCode, errorMessage);
    exit(1);
}

void glfwWindowSizeCallback(GLFWwindow *window, int width, int height) {
    GL_CALL(glViewport(0, 0, width, height));
}

void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(action == GLFW_RELEASE) {
        return;
    }

    switch(key) {
        case GLFW_KEY_ESCAPE:
        case GLFW_KEY_Q:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;

        // Camera controls
        case GLFW_KEY_W:
            camera.pos.z -= 0.1f;
            break;

        case GLFW_KEY_S:
            camera.pos.z += 0.1f;
            break;

        case GLFW_KEY_DOWN:
            camera.pos.y -= 0.1f;
            break;

        case GLFW_KEY_UP:
            camera.pos.y += 0.1f;
            break;

        case GLFW_KEY_A:
            camera.pos.x -= 0.1f;
            break;

        case GLFW_KEY_D:
            camera.pos.x += 0.1f;
            break;

        case GLFW_KEY_LEFT:
            camera.theta -= 1.0f;
            break;

        case GLFW_KEY_RIGHT:
            camera.theta += 1.0f;
            break;

        case GLFW_KEY_P:
            // Print camera data
            printf("camPos: %s camTheta: %.03f fov: %.03f\n", to_string(camera.pos).c_str(), camera.theta, camera.fov);
            printf("lightPos: %s\n\n", glm::to_string(lightPos).c_str());
            break;

        case GLFW_KEY_R:
            // Reset camera or reload shaders
            if(mods & GLFW_MOD_ALT) {
                reloadShaders = true;
            }
            else {
                camera = defaultCamera;
            }
            break;

        // Light Controls
        case GLFW_KEY_J:
            lightPos.x -= 0.1f;
            break;

        case GLFW_KEY_L:
            lightPos.x += 0.1f;
            break;

        case GLFW_KEY_K:
            lightPos.z += 0.1f;
            break;

        case GLFW_KEY_I:
            lightPos.z -= 0.1f;
            break;

        case GLFW_KEY_U:
            lightPos.y -= 0.1f;
            break;

        case GLFW_KEY_O:
            lightPos.y += 0.1f;
            break;

        default:
            break;
    }
}

void glfwScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    camera.fov -= yOffset;

    if(camera.fov < 30.0f) {
        camera.fov = 30.0f;
    }
    if(camera.fov > 140.0f) {
        camera.fov = 140.0f;
    }
}

GLFWwindow *init() {
    glfwSetErrorCallback((GLFWerrorfun) glfwErrorCallback);

    if(glfwInit() != GLFW_TRUE) {
        fprintf(stderr, "Failed to initalize GLFW!\n");
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(600, 400, "Project 2", NULL, NULL);
    glfwSetWindowAspectRatio(window, 4, 3);

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initalize GLEW!\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    glfwSetWindowSizeCallback(window, (GLFWwindowsizefun) glfwWindowSizeCallback);
    glfwSetKeyCallback(window, (GLFWkeyfun) glfwKeyCallback);
    glfwSetScrollCallback(window, (GLFWscrollfun) glfwScrollCallback);

    int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    printf("GL Context Version: %d.%d\n", major, minor);

    GL_CALL(glEnable(GL_CULL_FACE));
    GL_CALL(glCullFace(GL_BACK));
    GL_CALL(glFrontFace(GL_CCW));
    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    return window;
}

void makeScene(std::vector<Entity> &phongEntities, std::vector<Entity> &textureEntities, std::vector<Entity> &mugMug) {
    MaterialRegistry *matRegistry = MaterialRegistry::getRegistry();
    tletc::VFS *vfs = tletc::VFS::getVFS();

    printf("Loading textures\n");
    
    TexMaterial *tableMaterial = new TexMaterial(vfs->resolvePath("resources/textures/table.jpg"), 3, 0.3, 0.7, 0.5, 10.0f);
    matRegistry->registerMaterial(tableMaterial);

    TexMaterial *boxMaterial = new TexMaterial(vfs->resolvePath("resources/textures/box.jpg"), 3, 0.3f, 0.7f, 0.5f, 10.0f);
    matRegistry->registerMaterial(boxMaterial);

    TexMaterial *backdropMaterial = new TexMaterial(vfs->resolvePath("resources/textures/backdrop.jpg"), 3, 0.3, 0.7, 0.5, 10.0f);
    matRegistry->registerMaterial(backdropMaterial);

    TexMaterial *mugMaterial = new TexMaterial(vfs->resolvePath("resources/textures/mug.jpg"), 3, 0.3f, 0.7f, 0.5f, 10.0f);
    matRegistry->registerMaterial(mugMaterial);

    TexMaterial *mugHandleMaterial = new TexMaterial(vfs->resolvePath("resources/textures/handle.png"), 4, 0.3f, 0.7f, 0.5f, 10.0f);
    matRegistry->registerMaterial(mugHandleMaterial);

    TexMaterial *napkinMaterial = new TexMaterial(vfs->resolvePath("resources/textures/napkin.jpg"), 3, 0.3f, 0.7f, 0.5f, 10.0f);
    matRegistry->registerMaterial(napkinMaterial);
    
    TexMaterial *forkMaterial = new TexMaterial(vfs->resolvePath("resources/textures/fork.png"), 4, 0.3f, 0.7f, 0.5f, 10.0f);
    matRegistry->registerMaterial(forkMaterial);

    TexMaterial *teaMaterial = new TexMaterial(vfs->resolvePath("resources/textures/tea.png"), 4, 0.3f, 0.7f, 0.5f, 10.0f);
    matRegistry->registerMaterial(teaMaterial);

    TexMaterial *plateMaterial = new TexMaterial(vfs->resolvePath("resources/textures/plate.png"), 4, 0.3f, 0.7f, 0.5f, 10.0f);
    matRegistry->registerMaterial(plateMaterial);

    TexMaterial *lemonSquareMaterial = new TexMaterial(vfs->resolvePath("resources/textures/lemonsquare.jpg"), 3, 0.3f, 0.7f, 0.5f, 10.0f);
    matRegistry->registerMaterial(lemonSquareMaterial);

    printf("Done\n");

    PhongMaterial *teapotMaterial = new PhongMaterial({0.396078f, 0.839216f, 0.631373f, 1.0f}, 0.3f,
                                                      {0.396078f, 0.839216f, 0.631373f, 1.0f}, 0.7f,
                                                      {1.0f,      1.0f,      1.0f,      1.0f}, 0.5f, 50.0f);
    matRegistry->registerMaterial(teapotMaterial);

    PhongMaterial *lemonMaterial = new PhongMaterial({0.819608f, 0.709804f, 0.141176f, 1.0f}, 0.3f,
                                                     {0.819608f, 0.709804f, 0.141176f, 1.0f}, 0.7f,
                                                     {1.0f,      1.0f,      1.0f,      1.0f}, 0.3f, 2.0f);
    matRegistry->registerMaterial(lemonMaterial);

    PhongMaterial *basketMaterial = new PhongMaterial({0.219608f, 0.133333f, 0.031373f, 1.0f}, 0.3f,
                                                      {0.219608f, 0.133333f, 0.031373f, 1.0f}, 0.7f,
                                                      {1.0f,      1.0f,      1.0f,      1.0f}, 0.2f, 5.0f);
    matRegistry->registerMaterial(basketMaterial);

    Cube table(tableMaterial->getId());
    table.setTextureCoords(cubeDefaultTexCoords);
    table.setScale({20.0f, 1.0f, 10.0f});
    textureEntities.push_back(table);

    Quad backdrop(backdropMaterial->getId());
    backdrop.translateZ(-5.0f);
    backdrop.setScale({20.0f, 10.0f, 1.0f});
    textureEntities.push_back(backdrop);

    Cube centerBox(boxMaterial->getId());
    centerBox.setTextureCoords(cubeDefaultTexCoords);
    centerBox.translateZ(-4.5f);
    centerBox.translateY(0.75f);
    centerBox.setScale({2.50f, 0.65f, 0.90f});
    textureEntities.push_back(centerBox);

    Teapot teapot(teapotMaterial->getId());
    teapot.setCoords({-0.6f, 1.075f, -4.5f});
    teapot.setScale({1.7f, 1.7f, 1.7f});
    teapot.setRotationY(26.0f);
    phongEntities.push_back(teapot);

    PieSlice napkin(napkinMaterial->getId());
    napkin.setTextureCoords(napkinTexCoords);
    napkin.setCoords({-0.55f, 0.55f, -3.53f});
    napkin.setScale({1.3f, 1.0f, 1.3f});
    napkin.rotateY(33.0f);
    textureEntities.push_back(napkin);

    Quad plate(plateMaterial->getId());
    plate.setCoords({0.1f, 0.59f, -3.35f});
    plate.setRotation({-90.0f, 30.0f, 0.0f});
    plate.scaleY(1.5f);
    textureEntities.push_back(plate);

    Cube lemonSquare1(lemonSquareMaterial->getId());
    lemonSquare1.setTextureCoords(cubeLemonSquareTexCoords);
    lemonSquare1.setCoords({0.18f, 0.65f, -3.04f});
    lemonSquare1.setRotationY(13.0f);
    lemonSquare1.setScale({0.32f, 0.1f, 0.58f});
    textureEntities.push_back(lemonSquare1);

    Cube lemonSquare2(lemonSquareMaterial->getId());
    lemonSquare2.setTextureCoords(cubeLemonSquareTexCoords);
    lemonSquare2.setCoords({-0.09f, 0.65f, -3.45f});
    lemonSquare2.setRotationY(-55.0f);
    lemonSquare2.setScale({0.256f, 0.1f, 0.384f});
    textureEntities.push_back(lemonSquare2);

    Cube lemonSquare3(lemonSquareMaterial->getId());
    lemonSquare3.setTextureCoords(cubeLemonSquareTexCoords);
    lemonSquare3.setCoords({-0.08f, 0.75f, -3.47f});
    lemonSquare3.setRotationY(-63.0f);
    lemonSquare3.setScale({0.256f, 0.1f, 0.384f});
    textureEntities.push_back(lemonSquare3);

    Quad fork(forkMaterial->getId());
    fork.setCoords({-0.60f, 0.7f, -3.22f});
    fork.setRotationX(-90.0f);
    fork.setRotationY(28.0f);
    fork.setScaleX(0.5);
    textureEntities.push_back(fork);

    Basket basket(basketMaterial->getId());
    basket.setCoords({0.75f, 1.4f, -4.3});
    basket.setScale({0.55f, 0.55f, 0.55f});
    basket.rotateY(-30.0f);
    phongEntities.push_back(basket);

    IcoSphere lemon1(lemonMaterial->getId());
    lemon1.setCoords({0.6f, 1.4f, -4.4f});
    lemon1.setRotation({-20.0f, -30.0f, 0.0f});
    lemon1.setScale({0.23f, 0.23f, 0.4f});
    phongEntities.push_back(lemon1);

    IcoSphere lemon2(lemonMaterial->getId());
    lemon2.setCoords({1.0f, 1.6f, -4.3f});
    lemon2.setRotation({13.0f, -25.0f, 0.0f});
    lemon2.setScale({0.22f, 0.22f, 0.4f});
    phongEntities.push_back(lemon2);

    IcoSphere lemon3(lemonMaterial->getId());
    lemon3.setCoords({0.63f, 1.65f, -4.5f});
    lemon3.setRotation({-15.0f, -85.0f, 0.0f});
    lemon3.setScale({0.23f, 0.23f, 0.33f});
    phongEntities.push_back(lemon3);

    Cylinder mug(mugMaterial->getId());
    mug.setCoords({0.84f, 0.75f, -3.6f});
    mug.setScale({0.5f, 0.5f, 0.5f});
    mugMug.push_back(mug);

    Quad mugHandle(mugHandleMaterial->getId());
    mugHandle.setCoords({0.90f + 0.41f, 0.75f, -3.55f});
    mugHandle.setScale({0.5f, 0.5f, 0.0f});
    textureEntities.push_back(mugHandle);

    Quad tea(teaMaterial->getId());
    tea.setCoords({0.865f, 0.90f, -3.65f});
    tea.rotateX(-90.0f);
    tea.setScale({0.52f, 0.52f, 1.0f});
    textureEntities.push_back(tea);
}

int main(int argc, char **argv) {
    // Get the executable path
    char buffer[4096];
    readlink("/proc/self/exe", buffer, 4096);
    std::filesystem::path executablePath(buffer);
    executablePath.remove_filename();

    tletc::VFS *vfs = tletc::VFS::getVFS();
    vfs->mountPath(std::string(executablePath) + "../../resources", "resources");
    vfs->mountPath(std::string(executablePath) + "../../src",       "shaders");
    vfs->dumpTree();

    GLFWwindow *window = init();

    std::vector<Entity> phongEntities;
    std::vector<Entity> textureEntities;
    std::vector<Entity> mugMug;
    makeScene(phongEntities, textureEntities, mugMug);

    Cube lightCube(3);
    lightCube.setScale({0.25f, 0.25f, 0.25f});
    phongEntities.push_back(lightCube);

    PhongShader phongShader("phongShader", vfs->resolvePath("shaders/common.vert"), vfs->resolvePath("shaders/phong.frag"));
    TexShader texShader("texShader", vfs->resolvePath("shaders/common.vert"), vfs->resolvePath("shaders/texture.frag"));
    TexShader mugShader("mugShader", vfs->resolvePath("shaders/common.vert"), vfs->resolvePath("shaders/mug.frag"));

    ArrayBuffer phongBuffer;
    phongBuffer.addEntities(phongEntities);
    phongBuffer.finalize();

    ArrayBuffer textureBuffer;
    textureBuffer.addEntities(textureEntities);
    textureBuffer.finalize();

    ArrayBuffer mugBuffer;
    mugBuffer.addEntities(mugMug);
    mugBuffer.finalize();

    int winWidth = 0;
    int winHeight = 0;
    vec3 camCenter(0.0f, 0.0f, 0.0f);
    mat4 camTiltMat(1.0f);
    mat4 camMat(1.0f);
    mat4 projMat(1.0f);
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if(reloadShaders) {
            if(!phongShader.load()) {
                fprintf(stderr, "Failed to load phongShader\n");
                exit(1); // TODO(Adin): Update this with real cleanup / exit code
            }

            if(!texShader.load()) {
                fprintf(stderr, "Failed to load texShader\n");
                exit(1); // TODO(Adin): Update this with real cleanup / exit code
            }

            if(!mugShader.load()) {
                fprintf(stderr, "Failed to load mugShader\n");
                exit(1); // TODO(Adin): Update this with real cleanup / exit code
            }

            reloadShaders = false;
        }

        // printf("fov: %.03f camHeight: %.03f camTheta: %.03f\n", fov, camHeight, camTheta);

        // Hacky fix
        phongEntities.back().setCoords(vec3(lightPos));

        phongShader.setEntityUniforms(phongEntities);
        texShader.setEntityUniforms(textureEntities);
        mugShader.setEntityUniforms(mugMug);

        phongShader.setUniform<vec4>("u_lightPos", lightPos);
        texShader.setUniform<vec4>("u_lightPos", lightPos);
        mugShader.setUniform<vec4>("u_lightPos", lightPos);

        camTiltMat = rotate(mat4(1.0f), -glm::radians(camera.theta), vec3(1.0f, 0.0f, 0.0f)); 
        camCenter  = vec3(camera.pos.x, camera.pos.y - (2.0f * glm::atan(glm::radians(camera.theta))), camera.pos.z - 2.0f);
        camMat     = lookAt(camera.pos, camCenter, normalize(mat3(camTiltMat) * vec3(0.0f, 1.0f, 0.0f)));

        phongShader.setUniform<vec4>("u_cameraPos", vec4(camera.pos, 1.0f));
        phongShader.setUniform<mat4>("u_cameraMat", camMat);
        texShader.setUniform<vec4>("u_cameraPos", vec4(camera.pos, 1.0f));
        texShader.setUniform<mat4>("u_cameraMat", camMat);
        mugShader.setUniform<vec4>("u_cameraPos", vec4(camera.pos, 1.0f));
        mugShader.setUniform<mat4>("u_cameraMat", camMat);
        
        glfwGetWindowSize(window, &winWidth, &winHeight);
        projMat = perspective(glm::radians(camera.fov), (float) winWidth / (float) winHeight, 1.0f, 100.0f);
        phongShader.setUniform<mat4>("u_projMat", projMat);
        texShader.setUniform<mat4>("u_projMat", projMat);
        mugShader.setUniform<mat4>("u_projMat", projMat);

        // Start draw
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        phongBuffer.bind();
        phongShader.use();
        GL_CALL(glDrawElements(GL_TRIANGLES, phongBuffer.getNumIndices(), GL_UNSIGNED_INT, (void *) 0));

        GL_CALL(glDisable(GL_CULL_FACE));
        mugBuffer.bind();
        mugShader.use();
        GL_CALL(glDrawElements(GL_TRIANGLES, mugBuffer.getNumIndices(), GL_UNSIGNED_INT, (void *) 0));
        GL_CALL(glEnable(GL_CULL_FACE));

        textureBuffer.bind();
        texShader.use();
        GL_CALL(glDrawElements(GL_TRIANGLES, textureBuffer.getNumIndices(), GL_UNSIGNED_INT, (void *) 0));

        glfwSwapBuffers(window);
        // End draw
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}