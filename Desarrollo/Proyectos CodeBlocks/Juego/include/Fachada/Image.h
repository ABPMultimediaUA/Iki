#ifndef IMAGE_H
#define IMAGE_H

#include "Structs.h"

class Image
{
    public:
        Image(const char*);
        ~Image();
        void draw(int,int, Structs::TRectangulo, Structs::TColor);

    protected:

    private:
        ITexture* image;
};

#endif // IMAGE_H
