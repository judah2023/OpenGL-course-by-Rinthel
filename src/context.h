#pragma once

#include "common.h"
#include "shader.h"
#include "program.h"

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

};