#ifndef IMAGE_H
#define IMAGE_H

#include "Structs.h"

class Image
{
    public:
        Image(const char*, Structs::TRectangulo);
        ~Image();
        void draw(int,int);

    protected:

    private:
        TDraw2D* image;
};

#endif // IMAGE_H
