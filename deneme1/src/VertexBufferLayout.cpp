#include "VertexBufferLayout.h"

template<>
void VertexBufferLayout::Push<float>(unsigned int count){
    m_Elements.push_back({GL_FLOAT, count, false});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count){
    m_Elements.push_back({GL_UNSIGNED_INT, count, false});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}      

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count){
    m_Elements.push_back({GL_UNSIGNED_BYTE, count, true});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;

}