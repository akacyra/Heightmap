#ifndef __MESH_H__
#define __MESH_H__

#include <vector>

class Mesh
{
    public:
        unsigned int insertVertex(const float position[4], 
                                  const float color[4]);
        bool makeFace(unsigned int vertexIds[3]);

        bool vertexExists(unsigned int index) const;

        void clear();

        unsigned int vertexCount() const;
        unsigned int faceCount() const;

        static unsigned int vertexSize();

        const float* getVertexData() const;
        const unsigned int* getIndexData() const;

        void print() const;

    private:
        std::vector< float > vertices;
        std::vector< unsigned int > indices;
};

bool loadObjMesh(const char* filename, Mesh& out);

#endif
