#pragma once

#include "common.h"

#include "buffer.h"
#include "program.h"
#include "shader.h"
#include "vertex_layout.h"

CLASS_PTR(Context)
class Context
{
private:
    Context() = default;

public:
    static ContextUPtr Create();
    void Render();

private:
    bool Init();

private:
    ProgramUPtr m_program;

    VertexLayoutUPtr m_vertexLayout;
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;

};