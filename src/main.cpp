#include "heightmap.h"
#include "lodepng.h"
#include "diamond_square_generator.h"
#include <iostream>
#include <ctime>

void saveToPng(Heightmap& heightmap)
{
    unsigned int size = heightmap.getSize();
    std::vector< unsigned char > img = heightmap.toGrayscale();
    unsigned error = lodepng::encode("test.png", img, size, size, LCT_GREY);
    if(error)
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) 
                  << std::endl;
} // saveToPng()

int main(void)
{
    Heightmap h(9);
    DiamondSquareGenerator g;
    g.setCornerSeed(1.0);
    std::clock_t begin = std::clock();
    g.generate(h);
    std::clock_t end = std::clock();
    double ms = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Generation time (ms): " << ms << std::endl;
    saveToPng(h);
    return 0;
} // main()
