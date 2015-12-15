#include "heightmap.h"
#include <cmath>
#include <algorithm>

using std::vector;

Heightmap::Heightmap(unsigned int detailLevel) 
    : detailLevel(detailLevel), size(std::pow(2.0, detailLevel) + 1),
      heights(size * size, 0)
{
} // Constructor

double Heightmap::at(unsigned int x, unsigned int y) const
{
    // Bounds checking?
    return heights[y * size + x];
} // at()

double & Heightmap::at(unsigned int x, unsigned int y)
{
    // Bounds checking?
    return heights[y * size + x];
} // at()

unsigned int Heightmap::getSize() const
{
    return size;
} // getSize();

unsigned int Heightmap::getDetailLevel() const
{
    return detailLevel;
} // getDetailLevel()

vector< unsigned char > Heightmap::toGrayscale() const
{
    double max_height = *(std::max_element(heights.begin(), heights.end()));
    double min_height = *(std::min_element(heights.begin(), heights.end()));
    double range = max_height - min_height;
    vector< unsigned char > grayscale(heights.size());
    auto src = heights.begin();
    auto dst = grayscale.begin();
    for(; src != heights.end(); src++, dst++) {
        *dst = std::round(255 * (*src - min_height) / range);
    }
    return grayscale;
} // toGrayscale()
