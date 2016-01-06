#include "heightmap.h"
#include <cmath>
#include <algorithm>

using std::vector;
using std::max_element;
using std::min_element;
using std::transform;
using std::fill;
using std::pow;
using std::round;

Heightmap::Heightmap(unsigned int detailLevel) 
    : detailLevel(detailLevel), size(pow(2.0, detailLevel) + 1),
      elevation(size, size, 0), channel(size * size, 0)
{
} // Constructor

double Heightmap::at(unsigned int x, unsigned int y) const
{
    // Bounds checking?
    return elevation[y][x];
} // at()

double& Heightmap::at(unsigned int x, unsigned int y)
{
    // Bounds checking?
    return elevation[y][x];
} // at()

unsigned int Heightmap::getSize() const
{
    return size;
} // getSize();

unsigned int Heightmap::levelOfDetail() const
{
    return detailLevel;
} // levelOfDetail()

void Heightmap::clear()
{
    fill(elevation.begin(), elevation.end(), 0);
} // clear()

const vector< unsigned char >& Heightmap::asImage()
{
    double max_elev = *(max_element(elevation.begin(), elevation.end()));
    double min_elev = *(min_element(elevation.begin(), elevation.end()));
    double range = max_elev - min_elev;
    transform(elevation.begin(), elevation.end(), channel.begin(),
            [min_elev, range](double elevation) -> unsigned char {
                return round(255 * (elevation - min_elev) / range);
            });
    return channel;
} // asImage()

void Heightmap::normalize() 
{
    double max = *(max_element(elevation.begin(), elevation.end()));
    double min = *(min_element(elevation.begin(), elevation.end()));
    double range = max - min;
    std::transform(elevation.begin(), elevation.end(), elevation.begin(),
            [min, range](double diff) -> double{
                return (diff - min) / range;
            });
} // normalize()
