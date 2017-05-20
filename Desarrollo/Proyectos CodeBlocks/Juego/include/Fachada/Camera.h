#ifndef CAMERA_H
#define CAMERA_H

//#include "GraphicsFacade.h"
#include "Structs.h"
#include "TCamara.h"


class Camera
{
    public:
        Camera(Structs::TPosicion position);
        ~Camera();
        void render(Structs::TPosicion positionPlayer);
        TNodo* getCamera(){return camera;};

    protected:

    private:
        Structs::TPosicion positionInitial;
        TNodo* camera;
};

#endif // CAMERA_H
