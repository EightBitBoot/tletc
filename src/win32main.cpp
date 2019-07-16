#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "math/math.h"

#include <windows.h>
#include <wingdi.h>

#include <GL/glew.h>
#include <GL/wglew.h>

#define WINDOW_CLASS_NAME "TLETCTestWindowClass"

/*
  OpenGL Reference Wiki:
  https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
*/

// TODO(Adin): Switch to CreateWindowEx

int loadGLExtensions(HINSTANCE hInstance) {
    const char DummyWindowClassName[] = "TLETCDummyWinClass";
    
    WNDCLASS dummyWindowClass = {};
    dummyWindowClass.style = CS_OWNDC;
    dummyWindowClass.lpfnWndProc = DefWindowProc;
    dummyWindowClass.hInstance = hInstance;
    dummyWindowClass.lpszClassName = DummyWindowClassName;
    
    RegisterClass(&dummyWindowClass);
    
    HWND dummyWindow = CreateWindow(DummyWindowClassName, "Dummy Thicc", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    
    if(dummyWindow == NULL) {
        printf("Failed to create dummy window!\n");
        return 1;
    }
    
    // Default dummy descriptor values copied from opengl wiki
    PIXELFORMATDESCRIPTOR dummyDescriptor = {};
    dummyDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    dummyDescriptor.nVersion = 1;
    dummyDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    dummyDescriptor.iPixelType = PFD_TYPE_RGBA;
    dummyDescriptor.cColorBits = 32;
    dummyDescriptor.cDepthBits = 24;
    dummyDescriptor.cStencilBits = 8;
    dummyDescriptor.iLayerType = PFD_MAIN_PLANE;
    
    HDC dummyDC =  GetDC(dummyWindow);
    if(dummyDC == NULL) {
        printf("Failed to get dummy window HDC!\n");
        DestroyWindow(dummyWindow);
        return 1;
    }
    
    int dummyPixelFormat = ChoosePixelFormat(dummyDC, &dummyDescriptor);
    SetPixelFormat(dummyDC, dummyPixelFormat, &dummyDescriptor);
    
    HGLRC dummyWGLHandle = wglCreateContext(dummyDC);
    wglMakeCurrent(dummyDC, dummyWGLHandle);
    
    // Don't need this anymore
    ReleaseDC(dummyWindow, dummyDC);
    
    GLenum glewInitResult = glewInit();
    if(glewInitResult != GLEW_OK) {
        printf("GLEW failed to init: %s\n", glewGetErrorString(glewInitResult));
        
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(dummyWGLHandle);
        
        DestroyWindow(dummyWindow);
        
        return 1;
    }
    
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(dummyWGLHandle);
    
    DestroyWindow(dummyWindow);
    
    UnregisterClass(DummyWindowClassName, hInstance);
    
    return 0;
}

HGLRC createGLContext(HDC windowHDC) {
    HGLRC result = NULL;
    
    // Default attributes copied from opengl wiki
    const int pfAttributeList[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0 // Null terminator
    };
    
    int pixelFormatIndex = 0;
    UINT numPixelFormats = 0;
    
    // Needed for the set pixel format call but not actually important or used
    PIXELFORMATDESCRIPTOR blankPFD = {};
    blankPFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    blankPFD.nVersion = 1;
    
    wglChoosePixelFormatARB(windowHDC, pfAttributeList, NULL, 1, &pixelFormatIndex, &numPixelFormats);
    
    SetPixelFormat(windowHDC, pixelFormatIndex, &blankPFD);
    
    // GL 3.2 debug context
    const int contextAttributeList[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 2,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
        0 // Null terminator
    };
    
    result = wglCreateContextAttribsARB(windowHDC, NULL, contextAttributeList);
    
    return result;
}

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	//Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Grab vertex shader info from file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ifstream::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Could not open vertex shader file. Are you in the right dir?\n");
		getchar();
		return 0;
	}

	//Grab fragment shader info from file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ifstream::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else {
		printf("Could not open fragment shader file. Are you in the right dir?\n");
		getchar();
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//Compile vertex shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexShaderPointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexShaderPointer, NULL);
	glCompileShader(VertexShaderID);

	//Check the Compile
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	//Compile fragment shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentShaderPointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentShaderPointer, NULL);
	glCompileShader(FragmentShaderID);

	//Check the Compile
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	printf("Linking program!\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	//Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void render(HDC windowHDC, GLuint ShaderProgramID,  GLuint vertexBuffer, GLenum mode, int dimensions) {
	
	//Draw background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Get VAA ready for draw
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Bind to the given shader state
	glUseProgram(ShaderProgramID);
	//Draw a triangle
	glDrawArrays(mode, 0, dimensions);
	
	glDisableVertexAttribArray(0);
    SwapBuffers(windowHDC);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
            
        } break;
        
        case WM_SIZE: {
            // Also call render function here
            
            HDC tempHDC = GetDC(hwnd);
            render(tempHDC, 0, 0, 0, 3);
            ReleaseDC(hwnd, tempHDC);
            return 0;
        } break;
    }
    
    return DefWindowProc(hwnd, message, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    (void) hPrevInstance;
    (void) lpCmdLine;
    (void) nShowCmd;
    
    const int timerForBreakpoint = WM_TIMER;
    
    WNDCLASS wc = {};
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    
    RegisterClass(&wc);
    
    // GLEW is initalized in here
    loadGLExtensions(hInstance);
    
    HWND window = CreateWindow(WINDOW_CLASS_NAME, "TLETC Test Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    HDC windowHDC = GetDC(window);
    
    HGLRC glContext = createGLContext(windowHDC);
    
    wglMakeCurrent(windowHDC, glContext);
    
    // Cast to make compiler happy
    const GLubyte *glVersionString = glGetString(GL_VERSION);
    MessageBox(NULL, (const char *) glVersionString, "OpenGL Version", MB_OK);
    
    ShowWindow(window, SW_SHOW);
    
    // #BADA55
    glClearColor(0.729f, 0.854f, 0.333f, 1.0f);
	GLuint programID = loadShaders("shaders/SimpleVertexShader.glsl", "shaders/SimpleFragShader.glsl");

	GLfloat vertices[]{
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f, 1.0f,  0.0f
	};

	//Create Vertex Array Object and bind to it
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	//Bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//Turn our vbo into an array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    
	tletc::Mat4 matrix = { {1, 2, 3, 4},
					{5, 6, 7, 8},
					{9, 10, 11, 12},
					{13, 14, 15, 16} };

	tletc::Vec4 transf = { 1, 2, 3, 4 };

	tletc::Vec4 = matrix.Transform(transf);

	LOG_INF

    // Main loop
    MSG message = {};
    BOOL running = TRUE;
    while(running) {
        while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            if(message.message == WM_QUIT) {
                // Quit when it's quittin time
                running = false;
            }
            
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        
		

        // Sample render function to show where to put rendering code
        render(windowHDC, programID, vbo, GL_TRIANGLES, 3);
    }
    
    // These are probably unnecessary because the window is already destroyed
    ReleaseDC(window, windowHDC);
    
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(glContext);
    
    return 0;
}