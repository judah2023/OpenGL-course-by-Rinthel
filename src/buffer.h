#pragma once

#include "common.h"

CLASS_PTR(Buffer)
class Buffer 
{
private:
    Buffer() = default;

public:
    ~Buffer();

public:
    static BufferUPtr CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize);

    uint32_t Get() const { return m_buffer; }
    void Bind() const;

private:
    bool Init(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize);

private:
    uint32_t m_buffer{0};
    uint32_t m_bufferType{0};
    uint32_t m_usage{0};

};