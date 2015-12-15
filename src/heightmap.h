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

        // Returns the height at position (x, y).
        double at(unsigned int x, unsigned int y) const;
        double& at(unsigned int x, unsigned int y);

        // Returns the size of the heightmap.
        unsigned int getSize() const;
        // Returns the detail level of the heightmap.
        unsigned int getDetailLevel() const;

        // Returns a copy of the heightmap heights converted to 8bit grayscale values.
        std::vector< unsigned char > toGrayscale() const;

    private:
        // Determines the resolution of the heightmap. Size = 2^DetialLevel + 1.
        unsigned int detailLevel;
        // Side length of the square heightmap. Size = 2^DetailLevel + 1.
        unsigned int size;
        // Stores the heights of the heightmap in a 1D vector.
        // The number of height points is Size^2.
        std::vector< double > heights;
};

#endif
