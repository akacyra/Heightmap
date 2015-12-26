#ifndef __HEIGHTMAP_H__
#define __HEIGHTMAP_H__

#include <vector>

// Represents the height of a surface at evenly-spaced points on a 2D grid.
//
// Example usage:
//
class Heightmap
{
    public:
        // Constructs a flat heightmap of height 0.0 with the specified detail level.
        Heightmap(unsigned int detailLevel);

        // Returns the elevation at position (x, y).
        double at(unsigned int x, unsigned int y) const;
        double& at(unsigned int x, unsigned int y);

        unsigned int getSize() const;

        unsigned int levelOfDetail() const;

        // Sets the elevation of the entire heightmap to 0;
        void clear();

        // Clears and resizes the heightmap to the specified level of detail.
        void resize(unsigned int detailLevel);

        // Returns the elevation data as grayscale pixel data.
        const std::vector< unsigned char >& asImage();

    private:
        // The level of detail and size of each side of the heightmap. 
        // Size = 2^DetailLevel + 1.
        unsigned int detailLevel;
        unsigned int size;

        // The elevation at each point of the 2D heightmap grid.
        // The 2D grid is stored in a 1D vector, and Idx = X + Y * Size;
        std::vector< double > elevation;
        // Stores the elevation data as a grayscale image.
        std::vector< unsigned char > channel;
};

#endif
