#include "Image.h"
#include "GraphicsFacade.h"

Image::Image(const char* cadena)
{
    image = GraphicsFacade::getInstance().getDriver()->getTexture(cadena);
}

Image::~Image()
{
    //dtor
}

void Image::draw(int posicionX, int posicionY, Structs::TRectangulo rec, Structs::TColor color){
    GraphicsFacade::getInstance().getDriver()->draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(rec.X_inicio, rec.Y_inicio, rec.X_final, rec.Y_final), 0, SColor(color.opacity, color.r, color.g, color.b), true);
}
