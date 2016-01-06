#ifndef __HEIGHTMAP_MODIFIER_H__
#define __HEIGHTMAP_MODIFIER_H__

#include "heightmap.h"

// Interface for classes that perform modifications on heightmaps.
class Modifier 
{
    public:
        virtual ~Modifier() {};

        virtual void modify(Heightmap& heightmap) const = 0;
};

#endif
