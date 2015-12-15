#include "diamond_square_generator.h"
#include <iostream>
#include <iomanip>
#include <random>

void DiamondSquareGenerator::generate(Heightmap& heightmap) const
{
    std::default_random_engine generator;
    std::uniform_real_distribution< double > distribution(-1.0, 1.0);
    unsigned int size = heightmap.getSize(), sqSize = size - 1;
    unsigned int detailLevel = heightmap.getDetailLevel();
    heightmap.at(0, 0) = heightmap.at(0, size - 1) = heightmap.at(size - 1, 0) =
        heightmap.at(size - 1, size - 1) = cornerSeed;
    double scale = 1.0;
    for(unsigned int i = 0; i < detailLevel; i++) {
        for(unsigned int sqX = 0; sqX < size - 1; sqX += sqSize) {
            for(unsigned int sqY = 0; sqY < size - 1; sqY += sqSize) {
                // Diamond step
                double sum = heightmap.at(sqX, sqY) + heightmap.at(sqX + sqSize, sqY) 
                    + heightmap.at(sqX, sqY + sqSize) 
                    + heightmap.at(sqX + sqSize, sqY + sqSize);
                double offset = distribution(generator) * scale;
                unsigned int midX = sqX + sqSize / 2, midY = sqY + sqSize / 2;
                heightmap.at(midX, midY) = sum / 4 + offset;
            }
        }
        for(unsigned int sqX = 0; sqX < size - 1; sqX += sqSize) {
            for(unsigned int sqY = 0; sqY < size - 1; sqY += sqSize) {
                unsigned int midX = sqX + sqSize / 2, midY = sqY + sqSize / 2;
                // Square step
                // For each square, two different diamond centers will be set.
                // Diamond 1 (top-middle of square).
                double sum = heightmap.at(sqX, sqY) + heightmap.at(sqX + sqSize, sqY)
                    + heightmap.at(midX, midY);
                double offset = distribution(generator) * scale;
                // Top diamond corner idx may have to be wrapped.
                // Tiled heightmap, so opposite points on edge equal.
                if(sqY == 0) {
                    sum += heightmap.at(midX, size - (sqSize / 2 + 1));
                    heightmap.at(midX, sqY) = heightmap.at(midX, size - 1) = sum / 4 + offset;
                } else {
                    sum += heightmap.at(midX, sqY - sqSize / 2);
                    heightmap.at(midX, sqY) = sum / 4 + offset;
                }
                // Diamond 2 (left-middle of square).
                sum = heightmap.at(sqX, sqY) + heightmap.at(sqX, sqY + sqSize)
                    + heightmap.at(midX, midY);
                offset = distribution(generator) * scale;
                // Left diamond corner idx may have to be wrapped.
                // Tiled heightmap, so opposite points on edge equal.
                if(sqX == 0) {
                    sum += heightmap.at(size - (sqSize / 2 + 1), midY);
                    heightmap.at(sqX, midY) = heightmap.at(size - 1, midY) = sum / 4 + offset;
                } else {
                    sum += heightmap.at(sqX - sqSize / 2, midY);
                    heightmap.at(sqX, midY) = sum / 4 + offset;
                }
            }
        } 
        sqSize /= 2;
        scale /= 2.0;
    }
} // generate()

void DiamondSquareGenerator::setCornerSeed(double cornerSeed)
{
    this->cornerSeed = cornerSeed;
} // setCornerSeed()
