#ifndef __GL_RENDERER_H__
#define __GL_RENDERER_H__

#include <GL/glew.h>
#include <math.h>

#include <windows.h>
#include <wingdi.h>

#include "../utils/Logging.h"
#include "../utils/FileIO.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "ShaderProgram.h"
#include "Renderable2D.h"
#include "GL2DRenderer.h"

#include <deque>

class GL2DRenderer 
{
private:
    std::deque<const Renderable2D*> RenderQueue;

public:
    void submit(const Renderable2D* rederable);
    void draw();
};

void Win32Render(HDC windowHDC, GL2DRenderer* renderer);

#endif