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
        DiamondSquareGenerator();
        DiamondSquareGenerator(unsigned int seed);

        // Generates a new heightmap using the current generator settings .
        void generate(Heightmap& out) const;

        // Sets the value that will be used for the 4 heightmap corners.
        void setCornerValue(double value);

        // Generates a random seed for the RNG.
        void generateRandomSeed();

        // Sets the seed that will be used for the RNG.
        void setRandomSeed(unsigned int seed);

    private:
        // Initial value of the 4 corners of the generated heightmaps.
        double cornerValue;
        // Seed for the RNG.
        unsigned int seed;

};

#endif
