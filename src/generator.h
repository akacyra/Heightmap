#ifndef __HEIGHTMAP_GENERATOR_H__
#define __HEIGHTMAP_GENERATOR_H__

#include "heightmap.h"

// Interface for classes that generates heightmaps.
class Generator
{
    public:
        virtual ~Generator() {};

        // Generates a new heightmap using the current generator settings.
        virtual void generate(Heightmap& out) const = 0;
};

#endif
