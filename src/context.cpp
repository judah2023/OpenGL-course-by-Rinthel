#include "context.h"

ContextUPtr Context::Create()
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    
    return std::move(context);
}

void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool Context::Init()
{
    float vertices[][3] = {
         1.0f,  0.0f,  0.0f, 
         0.0f, -1.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
    };

    uint32_t indices[][3] = {
        0, 1, 3,
        1, 2, 3,
    };

    m_vertexArrayObject = VertexLayout::Create();
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(vertices));

    m_vertexArrayObject->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);

    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(indices));

    ShaderPtr vertexShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragmentShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if (!vertexShader || !fragmentShader)
        return false;
    SPDLOG_INFO("vertex shader id : {}", vertexShader->Get());
    SPDLOG_INFO("fragment shader id : {}", fragmentShader->Get());

    m_program = Program::Create({fragmentShader, vertexShader});
    if (!m_program)
        return false;
    SPDLOG_INFO("program id : {}", m_program->Get());
    
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

    return true;
}
