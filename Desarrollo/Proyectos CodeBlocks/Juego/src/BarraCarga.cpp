/*#include "BarraCarga.h"


BarraCarga::BarraCarga()
{
}
BarraCarga::~BarraCarga()
{
}
void BarraCarga::Inicia( BITMAP* _imagen, int _x, int _y, int _total_partes )
{
     imagen = create_bitmap(_imagen->w, _imagen->h);
     blit ( _imagen, imagen, 0,0,0,0, _imagen->w, _imagen->h );
     x = _x;
     y = _y;
     total_partes = _total_partes;
};

void BarraCarga::Progreso( int c )
{
       int actual = ( c * 396 ) / total_partes;

       rectfill(imagen, x, y, x+actual, y+21, 0x0c2e50 );
       rectfill(imagen, x, y, x+actual, y+3,  0x306783 );

       blit ( imagen, screen , 0,0,0,0, imagen->w, imagen->h );

};
*/
