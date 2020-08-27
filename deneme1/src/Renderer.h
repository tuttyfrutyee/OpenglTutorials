#pragma once

#include <iostream>
#include <glad/glad.h>
#include <cassert>


#define GLCall(x) GLClearError();\
    x;\
    assert(GLLogCall());

void GLClearError();
bool GLLogCall(void);