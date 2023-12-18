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

    glUseProgram(m_program->Get());
    glDrawArrays(GL_POINTS, 0, 1);
}

bool Context::Init()
{
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

    uint32_t vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return true;
}
