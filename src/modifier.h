#ifndef __HEIGHTMAP_MODIFIER_H__
#define __HEIGHTMAP_MODIFIER_H__

// Interface for classes that perform modifications on heightmaps.
class Modifier 
{
    public:
        virtual ~Modifier() {};

        void modifiy(Heightmap& heightmap) const = 0;
};

#endif
