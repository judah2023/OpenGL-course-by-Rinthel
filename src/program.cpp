#include "program.h"

Program::~Program()
{
    if (m_program)
        glDeleteProgram(m_program);
}

ProgramUPtr Program::Create(const std::vector<ShaderPtr> &shaders)
{
    auto program = ProgramUPtr(new Program());
    if (!program->Link(shaders))
        return nullptr;

    return std::move(program);
}

void Program::Use() const
{
    glUseProgram(m_program);
}

bool Program::Link(const std::vector<ShaderPtr> &shaders)
{
    m_program = glCreateProgram();
    for (auto& shader : shaders)
        glAttachShader(m_program, shader->Get());

    glLinkProgram(m_program);

    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[LOG_SIZE];
        glGetProgramInfoLog(m_program, LOG_SIZE, nullptr, infoLog);
        SPDLOG_ERROR("Failed to link program : {}", infoLog);
        return false;
    }

    return true;
}
