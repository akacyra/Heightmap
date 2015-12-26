#ifndef __HEIGHTMAP_VIEWER_H__
#define __HEIGHTMAP_VIEWER_H__

#include <vector>

class Viewer
{
    public:
        void run();

        void setHeightmap(const std::vector< unsigned char >& heightmap,
                          unsigned int size);

    private:
        std::vector< unsigned char > heightmap;
        unsigned int size;
};

#endif
