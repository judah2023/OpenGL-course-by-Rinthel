#pragma once

#include "common.h"

CLASS_PTR(VertexLayout)
class VertexLayout
{
private:
    VertexLayout() = default;

public:
    ~VertexLayout();

public:
    static VertexLayoutUPtr Create();

    uint32_t Get() const { return m_vertexArrayObject; }
    void Bind() const;
    void SetAttrib(
        uint32_t attribIndex, int count, 
        uint32_t type, bool normalized, 
        size_t stride, uint64_t offset);
    void DisableAttrib(int attribIndex);

private:
    void Init();

private:
    uint32_t m_vertexArrayObject{0};



};