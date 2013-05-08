#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace glow {

class ArrayData
{
public:
	virtual void* rawData() = 0;
	virtual GLenum type() = 0;
	virtual GLint elementSize() = 0;
	virtual GLint byteSize() = 0;
};

template <typename T, GLenum Type, GLint ElementSize = 1>
class Array : public ArrayData, public std::vector<T>
{
public:
	virtual void* rawData() {return (void*)std::vector<T>::data();}
	virtual GLenum type() {return Type;}
	virtual GLint elementSize() {return ElementSize;}
	virtual GLint byteSize() { return std::vector<T>::size()*sizeof(T);}

	Array& operator<<(const T& element) {std::vector<T>::push_back(element); return *this;}
};

typedef Array<float, GL_FLOAT, 1> FloatArray;
typedef Array<int, GL_INT, 1> IntArray;
typedef Array<unsigned int, GL_UNSIGNED_INT, 1> UIntArray;
typedef Array<char, GL_BYTE, 1> ByteArray;
typedef Array<unsigned char, GL_UNSIGNED_BYTE, 1> UByteArray;

typedef Array<glm::vec2, GL_FLOAT, 2> Vec2Array;
typedef Array<glm::vec3, GL_FLOAT, 3> Vec3Array;
typedef Array<glm::vec4, GL_FLOAT, 4> Vec4Array;

} // namespace glow