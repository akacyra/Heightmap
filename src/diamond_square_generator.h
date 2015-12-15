#ifndef __DIAMOND_SQUARE_GENERATOR__
#define __DIAMOND_SQUARE_GENERATOR__

#include "generator.h"

// Generates heightmaps using the diamond-square algorithm.
//
// Example usage:
//
class DiamondSquareGenerator : public Generator
{
    public:
        // Generates a new heightmap using the current generator settings to the input
        // heightmap.
        void generate(Heightmap& heightmap) const;

        // Sets the value that will be used for the 4 heightmap corners.
        void setCornerSeed(double cornerSeed);

    private:
        // Initial value of the 4 corners of the generated heightmaps.
        double cornerSeed;
};

#endif
