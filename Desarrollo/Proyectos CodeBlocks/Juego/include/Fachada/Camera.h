#ifndef CAMERA_H
#define CAMERA_H

//#include "GraphicsFacade.h"
#include "Structs.h"


class Camera
{
    public:
        Camera(Structs::TPosicion position, Structs::TPosicion lookAt);
        ~Camera();
        void render(Structs::TPosicion positionPlayer);
        TCamara* getCamera(){return camera;};

    protected:

    private:
        Structs::TPosicion positionInitial;
        TCamara* camera;
};

#endif // CAMERA_H
