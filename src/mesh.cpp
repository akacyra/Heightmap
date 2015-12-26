#include "mesh.h"
#include <iostream>

using std::copy;
using std::back_inserter;

using std::cout;
using std::endl;

void Mesh::print() const
{
    cout << "Vertices:" << endl << "[" << endl;
    for(int i = 0; i < vertexCount() * 8; i += 8) {
        cout << "  " << i / 8 << " : pos( " << vertices[i] << ", " 
             << vertices[i + 1] << ", " << vertices[i + 2] << ", "
             << vertices[i + 3] << " ), col( " << vertices[i + 4] << ", "
             << vertices[i + 5] << ", " << vertices[i + 6] << ", "
             << vertices[i + 7] << ")" << endl;
    }
    cout << "]" << endl;

    cout << "Faces:" << endl << "[" << endl;
    for(int i = 0; i < faceCount(); i++) {
        cout << "  " << i << " : face( " << indices[i * 3 + 0] << ", " 
             << indices[i * 3 + 1] << ", " << indices[i * 3 + 2] << " )"
             << endl;
    }
    cout << "]" << endl;
} // print()

unsigned int Mesh::insertVertex(const float position[4],
                                const float color[4])
{
    unsigned int index = vertexCount();
    copy(position, position + 4, back_inserter(vertices));
    copy(color, color + 4, back_inserter(vertices));
    return index;
} // insertVertex()

bool Mesh::makeFace(unsigned int vertexIds[3])
{
    if(vertexExists(vertexIds[0]) && vertexExists(vertexIds[1]) &&
       vertexExists(vertexIds[2])) {
        copy(vertexIds, vertexIds + 3, back_inserter(indices));
        return true;
    }
    return false;
} // makeFace()

void Mesh::clear()
{
    vertices.clear();
    indices.clear();
} // clear()

bool Mesh::vertexExists(unsigned int index) const
{
    return index < vertexCount();
} // vertexExists()

unsigned int Mesh::vertexCount() const
{
    return vertices.size() / 8;
} // vertexCount()

unsigned int Mesh::faceCount() const
{
    return indices.size() / 3;
} // faceCount()

unsigned int Mesh::vertexSize()
{
    return 8 * sizeof(float);
} // vertexSize()

const float* Mesh::getVertexData() const
{
    return vertices.data();
} // getVertexData()

const unsigned int* Mesh::getIndexData() const
{
    return indices.data();
} // getIndexData()

bool loadObjMesh(const char* filename, Mesh& out)
{
    return false;
} // loadObjMesh()
