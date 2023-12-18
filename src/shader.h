#pragma once

#include "common.h"

// ... 본문은 여기에

CLASS_PTR(Shader);
class Shader
{
private:
    Shader() = default;

public:
    ~Shader();

public:
    static ShaderUPtr CreateFromFile(const std::string& filename, GLenum shaderType);

    uint32_t Get() const { return m_shader; }

private:
    bool LoadFile(const std::string& filename, GLenum shaderType);

private:
    uint32_t m_shader{0};

};
