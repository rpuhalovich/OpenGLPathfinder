#pragma once

class IBuffer {
public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
};