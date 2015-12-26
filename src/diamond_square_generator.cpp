#include "diamond_square_generator.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>

void DiamondSquareGenerator::generate(Heightmap& out) const
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);;
    std::uniform_real_distribution< double > distribution(-0.1, 0.1);
    unsigned int size = out.getSize(), sqSize = size - 1;
    unsigned int detailLevel = out.levelOfDetail();
    out.at(0, 0) = out.at(0, size - 1) = out.at(size - 1, 0) =
        out.at(size - 1, size - 1) = cornerSeed;
    double scale = 1.0;
    for(unsigned int i = 0; i < detailLevel; i++) {
        for(unsigned int sqX = 0; sqX < size - 1; sqX += sqSize) {
            for(unsigned int sqY = 0; sqY < size - 1; sqY += sqSize) {
                // Diamond step
                double sum = out.at(sqX, sqY) + out.at(sqX + sqSize, sqY) 
                    + out.at(sqX, sqY + sqSize) 
                    + out.at(sqX + sqSize, sqY + sqSize);
                double offset = distribution(generator) * scale;
                unsigned int midX = sqX + sqSize / 2, midY = sqY + sqSize / 2;
                out.at(midX, midY) = sum / 4 + offset;
            }
        }
        for(unsigned int sqX = 0; sqX < size - 1; sqX += sqSize) {
            for(unsigned int sqY = 0; sqY < size - 1; sqY += sqSize) {
                unsigned int midX = sqX + sqSize / 2, midY = sqY + sqSize / 2;
                // Square step
                // For each square, two different diamond centers will be set.
                // Diamond 1 (top-middle of square).
                double sum = out.at(sqX, sqY) + out.at(sqX + sqSize, sqY)
                    + out.at(midX, midY);
                double offset = distribution(generator) * scale;
                // Top diamond corner idx may have to be wrapped.
                // Tiled out, so opposite points on edge equal.
                if(sqY == 0) {
                    sum += out.at(midX, size - (sqSize / 2 + 1));
                    out.at(midX, sqY) = out.at(midX, size - 1) = sum / 4 + offset;
                } else {
                    sum += out.at(midX, sqY - sqSize / 2);
                    out.at(midX, sqY) = sum / 4 + offset;
                }
                // Diamond 2 (left-middle of square).
                sum = out.at(sqX, sqY) + out.at(sqX, sqY + sqSize)
                    + out.at(midX, midY);
                offset = distribution(generator) * scale;
                // Left diamond corner idx may have to be wrapped.
                // Tiled out, so opposite points on edge equal.
                if(sqX == 0) {
                    sum += out.at(size - (sqSize / 2 + 1), midY);
                    out.at(sqX, midY) = out.at(size - 1, midY) = sum / 4 + offset;
                } else {
                    sum += out.at(sqX - sqSize / 2, midY);
                    out.at(sqX, midY) = sum / 4 + offset;
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
