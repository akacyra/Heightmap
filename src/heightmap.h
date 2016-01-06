#ifndef __HEIGHTMAP_H__
#define __HEIGHTMAP_H__

#include "array2d.h"

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

        // Returns the elevation data as grayscale pixel data.
        const std::vector< unsigned char >& asImage();

        // Normalizes the range of elevation values to be between 0 and 1.
        void normalize();

    private:
        // The level of detail and size of each side of the heightmap. 
        // Size = 2^DetailLevel + 1.
        unsigned int detailLevel;
        unsigned int size;

        // The elevation at each point of the 2D heightmap grid.
        // The 2D grid is stored in a 1D vector, and Idx = X + Y * Size;
        Array2D< double > elevation;
        // Stores the elevation data as a grayscale image.
        std::vector< unsigned char > channel;
};

#endif
