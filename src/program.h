#pragma once

#include "common.h"
#include "shader.h"

CLASS_PTR(Program)
class Program
{
private:
    Program() = default;

public:
    ~Program();

public:
    static ProgramUPtr Create(const std::vector<ShaderPtr>& shaders);

    uint32_t Get() const { return m_program; }

private:
    bool Link(const std::vector<ShaderPtr>& shaders);

private:
    uint32_t m_program;

};